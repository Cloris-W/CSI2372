// grid.cpp -- Part B: dynamic matrix operations.
#include "grid.h"
#include <iomanip>

namespace grid {

// Allocate a zero-initialized rows x cols matrix, or return nullptr for invalid dimensions. Caller owns it and must call destroy.
int** create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return nullptr;
    int** m = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        m[i] = new int[cols]();
    }
    return m;
}

// Release each of the rows allocated for m, then its pointer array; reset the caller pointer by reference. Null m is harmless.
void destroy(int**& m, int rows) {
    if (m == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
    m = nullptr;
}

// Read rows x cols integers from borrowed in into caller-owned m; return false on the first failed extraction, true on success.
bool read(std::istream& in, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(in >> m[i][j])) return false;
        }
    }
    return true;
}

// Write borrowed rows x cols matrix m to out in width-5 fields. Returns no value and changes no matrix elements.
void print(std::ostream& out, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            out << std::setw(5) << m[i][j];
        out << '\n';
    }
}

// Read rows x cols matrix m and return a newly allocated array of row sums. Caller owns the result and must delete[] it.
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

// Read column col from rows rows of borrowed m; return its real mean, or 0.0 when rows <= 0.
double columnMean(int** m, int rows, int col) {
    if (rows <= 0) return 0.0;
    long long sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += m[i][col];
    }
    return static_cast<double>(sum) / rows;
}

// Read rows x cols matrix m and return a new cols x rows transpose. Caller owns it and must call destroy(result, cols).
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
