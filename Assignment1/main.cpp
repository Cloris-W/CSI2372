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

}

static void cmdAbove(int** m, int rows, int cols, std::istringstream& args) {
    // TODO: read a row and a threshold; print the count (stats::countAbove).

}

static void cmdSums(int** m, int rows, int cols, std::istringstream&) {
    // TODO: print each row sum (grid::rowSums). You own the returned array.

}

static void cmdTranspose(int** m, int rows, int cols, std::istringstream&) {
    // TODO: print the transpose, then free it. How many rows does it have?

}

static void cmdSort(int** m, int rows, int cols, std::istringstream& args) {
    // TODO: optional word asc|desc after the row; use the default argument for asc.

}

static void cmdApply(int** m, int rows, int cols, std::istringstream& args) {
    // TODO: look the function name up in two parallel arrays:
    //   const char* fnames[] = {"negate", "square", "abs"};
    //   int (*fns[])(int)   = {stats::negate, stats::square, stats::absolute};

}

static void cmdMax(int** m, int rows, int cols, std::istringstream&) {
    // TODO: largest value of the whole matrix: stats::findMax on each row, then
    //       its column is found by POINTER SUBTRACTION.

}

// ---------------------------------------------------------------- dispatch table
static const char* NAMES[] = {"print", "row", "col", "above", "sums",
                              "transpose", "sort", "apply", "max"};
// TODO: the array of function pointers, in the same order as NAMES.
static Handler HANDLERS[] = {cmdPrint, cmdRow /* , ... */};
static const int NUM_COMMANDS = sizeof(HANDLERS) / sizeof(HANDLERS[0]);

static Handler lookup(const string& name) {
    // TODO: return the handler whose name matches, or nullptr.
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
