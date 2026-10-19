// main.cpp -- DataGrid command interpreter.  STARTER CODE -- complete the parts marked TODO
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

static void printRow(const int* r, int n) {
    cout << "  values    :";
    for (const int* p = r; p != r + n; ++p) cout << ' ' << *p;
    cout << '\n';
}

// ---------------------------------------------------------------- handlers
static void cmdPrint(int** m, int rows, int cols, std::istringstream&) {
    report::header("matrix " + std::to_string(rows) + " x " + std::to_string(cols));
    grid::print(cout, m, rows, cols);
}

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

static void cmdCol(int** m, int rows, int cols, std::istringstream& args) {
    // TODO: read a column index with readIndex, then print its mean (grid::columnMean).
    int c;
    if (!readIndex(args, "col", "column", cols, c)) return;
    report::header("column " + std::to_string(c));
    report::print("mean", grid::columnMean(m, rows, c));
}

static void cmdAbove(int** m, int rows, int cols, std::istringstream& args) {
    int r;
    double threshold;
    if (!readIndex(args, "above", "row", rows, r)) return;
    if (!(args >> threshold)) {
        cout << "error: missing threshold for 'above'\n";
        return;
    }
    report::header("row " + std::to_string(r) + " above " + std::to_string((int)threshold));
    report::print("count", stats::countAbove(m[r], cols, static_cast<int>(threshold)));
}

static void cmdSums(int** m, int rows, int cols, std::istringstream&) {
    int* rowSums = grid::rowSums(m, rows, cols);
    report::header("row sums");
    for (int i = 0; i < rows; ++i) {
        report::print("row " + std::to_string(i), rowSums[i]);
    }
    delete[] rowSums;
}

static void cmdTranspose(int** m, int rows, int cols, std::istringstream&) {
    int** t = grid::transpose(m, rows, cols);
    report::header("transpose " + std::to_string(cols) + " x " + std::to_string(rows));
    grid::print(cout, t, cols, rows);
    grid::destroy(t, cols);
}

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
    grid::sort(m[r], cols, order == "desc");
    printRow(m[r], cols);
}

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

static Handler lookup(const string& name) {
    for (int i = 0; i < NUM_COMMANDS; ++i) {
        if (name == NAMES[i]) return HANDLERS[i];
    }
    return nullptr;
}

// ---------------------------------------------------------------- main
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
