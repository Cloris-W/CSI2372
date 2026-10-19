// grid.cpp -- Part B.  Complete every function marked TODO.
#include "grid.h"
#include "stats.h"
#include <iomanip>

namespace grid {

int** create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return nullptr;
    int** m = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        m[i] = new int[cols]();
    }
    return m;
}

void destroy(int**& m, int rows) {
    if (m == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
    m = nullptr;
}

bool read(std::istream& in, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(in >> m[i][j])) return false;
        }
    }
    return true;
}

void print(std::ostream& out, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            out << std::setw(5) << m[i][j];
        out << '\n';
    }
}

int* rowSums(int** m, int rows, int cols) {
    int* sums = new int[rows];
    for (int i = 0; i < rows; ++i) {
        int total = 0;
        for (int j = 0; j < cols; ++j) {
            total += m[i][j];
        }
        sums[i] = total;
    }
    return sums;
}

double columnMean(int** m, int rows, int col) {
    if (rows <= 0) return 0.0;
    long long sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += m[i][col];
    }
    return static_cast<double>(sum) / rows;
}

void sort(int* a, int n, bool descending) {
    stats::sortValues(a, n, !descending);
}

int** transpose(int** m, int rows, int cols) {
    int** t = create(cols, rows);
    if (t == nullptr) return nullptr;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            t[j][i] = m[i][j];
        }
    }
    return t;
}

} // namespace grid
