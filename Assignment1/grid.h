// grid.h -- Part B: a dynamic two-dimensional matrix (int**).
// CSI2372A Fall 2026 -- Lab Assignment 1 (DataGrid)
#ifndef GRID_H
#define GRID_H

#include <iostream>

namespace grid {

// Allocates a rows x cols matrix: an array of row pointers, then each row.
// Every element is initialized to 0. Returns nullptr if rows <= 0 or cols <= 0.
int** create(int rows, int cols);

// Frees every row, then the array of row pointers (reverse order of create),
// and sets the caller's pointer to nullptr. Does nothing if m is nullptr.
void destroy(int**& m, int rows);

// Reads rows*cols integers (row by row) from in. Returns false if input fails.
bool read(std::istream& in, int** m, int rows, int cols);

// Prints the matrix, one row per line, each value right-aligned in width 5.
void print(std::ostream& out, int** m, int rows, int cols);

// Returns a NEW array (new int[rows]) holding the sum of each row.
// The caller owns it and must release it with delete[].
int* rowSums(int** m, int rows, int cols);

// Mean of column col as a real number.
double columnMean(int** m, int rows, int col);

// Returns a NEW cols x rows matrix t with t[j][i] == m[i][j].
// The caller must release it with destroy(t, cols).
int** transpose(int** m, int rows, int cols);

} // namespace grid

#endif
