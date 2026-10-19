// main.cpp -- DataGrid command interpreter.
//
// Usage:  ./datagrid data.txt        (or:  ./datagrid < data.txt)
// Input:  a line "rows cols", then rows*cols integers, then one command per line.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "stats.h"
#include "grid.h"
#include "report.h"

using std::cout;
using std::string;

extern int reportsPrinted;               // defined in report.cpp (also declared in report.h)

// Every command handler has the same signature, so they can be stored in an array
// of function pointers and selected by name (a "dispatch table").
typedef void (*Handler)(int** m, int rows, int cols, std::istringstream& args);

// ---------------------------------------------------------------- helpers
// Read one index from args; cmd and what label errors, limit gives the exclusive upper bound. Write through index; return validity.
static bool readIndex(std::istringstream& args, const char* cmd, const char* what,
                      int limit, int& index) {
    if (!(args >> index)) {
        cout << "error: missing " << what << " for '" << cmd << "'\n";
        return false;
    }
    if (!report::inRange(index, 0, limit - 1)) {
        cout << "error: " << what << ' ' << index << " out of range [0, " << limit - 1 << "]\n";
        return false;
    }
    return true;
}

// Print n elements from borrowed row pointer r; return no value and do not change or release the row.
static void printRow(const int* r, int n) {
    cout << "  values    :";
    for (const int* p = r; p != r + n; ++p) cout << ' ' << *p;
    cout << '\n';
}

// ---------------------------------------------------------------- handlers
// Print borrowed rows x cols matrix m; command arguments are unused. Handlers do not own m.
static void cmdPrint(int** m, int rows, int cols, std::istringstream&) {
    report::header("matrix " + std::to_string(rows) + " x " + std::to_string(cols));
    grid::print(cout, m, rows, cols);
}

// Read and validate a row from args against rows; print its cols values and statistics. Borrow m without freeing it.
static void cmdRow(int** m, int rows, int cols, std::istringstream& args) {
    int r;
    if (!readIndex(args, "row", "row", rows, r)) return;
    report::header("row " + std::to_string(r));
    int lo, hi;
    stats::minMax(m[r], cols, &lo, &hi);        // pass by address
    printRow(m[r], cols);
    report::print("mean", stats::mean(m[r], cols));
    report::print("min", lo);
    report::print("max", hi);
}

// Read and validate a column from args against cols; print its mean over rows. Borrow m without freeing it.
static void cmdCol(int** m, int rows, int cols, std::istringstream& args) {
    int c;
    if (!readIndex(args, "col", "column", cols, c)) return;
    report::header("column " + std::to_string(c));
    report::print("mean", grid::columnMean(m, rows, c));
}

// Read a row and integer threshold from args; print the recursive count over cols elements. Borrow the rows x cols matrix m.
static void cmdAbove(int** m, int rows, int cols, std::istringstream& args) {
    int r;
    int threshold;
    if (!readIndex(args, "above", "row", rows, r)) return;
    if (!(args >> threshold)) {
        cout << "error: missing threshold for 'above'\n";
        return;
    }
    report::header("row " + std::to_string(r) + " above " + std::to_string(threshold));
    report::print("count", stats::countAbove(m[r], cols, threshold));
}

// Print the sums of rows in borrowed rows x cols matrix m; own and delete[] the temporary sums. Arguments are unused.
static void cmdSums(int** m, int rows, int cols, std::istringstream&) {
    int* rowSums = grid::rowSums(m, rows, cols);
    report::header("row sums");
    for (int i = 0; i < rows; ++i) {
        report::print("row " + std::to_string(i), rowSums[i]);
    }
    delete[] rowSums;
}

// Print a new transpose of borrowed rows x cols matrix m, then destroy the temporary using cols rows. Arguments are unused.
static void cmdTranspose(int** m, int rows, int cols, std::istringstream&) {
    int** t = grid::transpose(m, rows, cols);
    report::header("transpose " + std::to_string(cols) + " x " + std::to_string(rows));
    grid::print(cout, t, cols, rows);
    grid::destroy(t, cols);
}

// Read a row and optional order from args, validate using rows, then sort its cols elements in caller-owned m and print them.
static void cmdSort(int** m, int rows, int cols, std::istringstream& args) {
    int r;
    std::string order;
    if (!readIndex(args, "sort", "row", rows, r)) return;
    if (!(args >> order)) {
        order = "asc";
    }
    if (order != "asc" && order != "desc") {
        cout << "error: unknown order '" << order << "' (use asc or desc)\n";
        return;
    }
    report::header("row " + std::to_string(r) + " sorted " + order);
    if (order == "asc") stats::sortValues(m[r], cols);
    else stats::sortValues(m[r], cols, false);
    printRow(m[r], cols);
}

// Read a row and function name from args; use parallel tables to transform cols elements of caller-owned m after validating rows.
static void cmdApply(int** m, int rows, int cols, std::istringstream& args) {
    int r;
    std::string fname;
    if (!readIndex(args, "apply", "row", rows, r)) return;
    if (!(args >> fname)) {
        cout << "error: missing function for 'apply'\n";
        return;
    }
    const char* fnames[] = {"negate", "square", "abs"};
    int (*fns[])(int) = {stats::negate, stats::square, stats::absolute};
    for (int i = 0; i < 3; ++i) {
        if (fname == fnames[i]) {
            stats::apply(m[r], cols, fns[i]);
            report::header("row " + std::to_string(r) + " after " + fname);
            printRow(m[r], cols);
            return;
        }
    }
    cout << "error: unknown function '" << fname
         << "' (use negate, square or abs)\n";
}

// Search borrowed rows x cols matrix m in row order; print the first maximum and its indices. Arguments are unused.
static void cmdMax(int** m, int rows, int cols, std::istringstream&) {
    int bestRow = -1;
    int bestCol = 0;
    int bestValue = 0;
    bool found = false;
    for (int r = 0; r < rows; ++r) {
        int* rowMaxPtr = stats::findMax(m[r], cols);
        if (rowMaxPtr == nullptr) continue;
        if (!found || *rowMaxPtr > bestValue) {
            found = true;
            bestValue = *rowMaxPtr;
            bestRow = r;
            bestCol = static_cast<int>(rowMaxPtr - m[r]);
        }
    }
    if (!found) return;
    report::header("maximum");
    report::print("value", bestValue);
    report::print("row", bestRow);
    report::print("column", bestCol);
}

// ---------------------------------------------------------------- dispatch table
static const char* NAMES[] = {"print", "row", "col", "above", "sums",
                              "transpose", "sort", "apply", "max"};
static Handler HANDLERS[] = {cmdPrint, cmdRow, cmdCol, cmdAbove, cmdSums,
                            cmdTranspose, cmdSort, cmdApply, cmdMax};
static const int NUM_COMMANDS = sizeof(HANDLERS) / sizeof(HANDLERS[0]);

// Look up borrowed command name in parallel tables; return a function pointer, or nullptr if unknown. No allocation.
static Handler lookup(const string& name) {
    for (int i = 0; i < NUM_COMMANDS; ++i) {
        if (name == NAMES[i]) return HANDLERS[i];
    }
    return nullptr;
}

// ---------------------------------------------------------------- main
// Use argc/argv to select file input or stdin, own the matrix, dispatch commands and release it; return 1 for input errors, otherwise 0.
int main(int argc, char* argv[]) {
    std::ifstream file;
    if (argc > 1) {
        file.open(argv[1]);
        if (!file) { cout << "error: cannot open '" << argv[1] << "'\n"; return 1; }
    }
    std::istream& in = (argc > 1) ? static_cast<std::istream&>(file) : std::cin;

    int rows, cols;
    if (!(in >> rows >> cols) || rows <= 0 || cols <= 0) {
        cout << "error: the first line must give two positive dimensions\n";
        return 1;
    }
    int** m = grid::create(rows, cols);
    if (!grid::read(in, m, rows, cols)) {
        cout << "error: could not read a " << rows << " x " << cols << " matrix\n";
        grid::destroy(m, rows);
        return 1;
    }

    string line;
    std::getline(in, line);                          // rest of the last data line
    while (std::getline(in, line)) {
        std::istringstream args(line);
        string cmd;
        if (!(args >> cmd) || cmd[0] == '#') continue;   // blank line or comment
        if (cmd == "quit") break;
        Handler h = lookup(cmd);
        if (h == nullptr) cout << "error: unknown command '" << cmd << "'\n";
        else h(m, rows, cols, args);                   // call through the function pointer
    }

    cout << "---- " << reportsPrinted << " report(s) printed ----\n";
    grid::destroy(m, rows);
    return 0;
}
