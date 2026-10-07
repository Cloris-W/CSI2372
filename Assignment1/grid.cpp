// grid.cpp -- Part B.  Complete every function marked TODO.
#include "grid.h"
#include <iomanip>

namespace grid {

int** create(int rows, int cols) {
    // TODO: new int*[rows], then new int[cols]() for each row. nullptr if a dimension is <= 0.
    return nullptr;
}

void destroy(int**& m, int rows) {
    // TODO: delete[] every row, then delete[] m, then set m to nullptr.
    //       Why is the parameter a REFERENCE to a pointer? (see Question 5)
}

bool read(std::istream& in, int** m, int rows, int cols) {
    // TODO: read row by row; return false as soon as a read fails.
    return false;
}

void print(std::ostream& out, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            out << std::setw(5) << m[i][j];
        out << '\n';
    }
}

int* rowSums(int** m, int rows, int cols) {
    // TODO: allocate new int[rows]; the caller will delete[] it.
    return nullptr;
}

double columnMean(int** m, int rows, int col) {
    // TODO
    return 0.0;
}

int** transpose(int** m, int rows, int cols) {
    // TODO: create a cols x rows matrix and fill it.
    return nullptr;
}

} // namespace grid
