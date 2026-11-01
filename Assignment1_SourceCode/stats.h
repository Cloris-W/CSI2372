// stats.h -- Part A: statistics on one-dimensional int arrays, accessed through pointers.
// CSI2372A Fall 2026 -- Lab Assignment 1 (DataGrid)
#ifndef STATS_H
#define STATS_H

#include <vector>

namespace stats {

// Arithmetic mean of a[0..n-1] as a real number. Returns 0.0 when n <= 0.
double mean(const int* a, int n);

// Smallest and largest of a[0..n-1], returned through two POINTERS (pass by address).
// Precondition: n >= 1.
void minMax(const int* a, int n, int* lo, int* hi);

// Same result for a vector, returned through two REFERENCES (overload).
// Precondition: v is not empty.
void minMax(const std::vector<int>& v, int& lo, int& hi);

// RECURSIVE: number of elements of a[0..n-1] strictly greater than threshold.
// Must use pointer arithmetic (recurse on a + 1) -- no loop.
int countAbove(const int* a, int n, int threshold);

// Pointer to the (first) largest element of a[0..n-1], or nullptr when n <= 0.
int* findMax(int* a, int n);

// Replaces every element x of a[0..n-1] by f(x). Walks the array with a pointer.
void apply(int* a, int n, int (*f)(int));

// Sorts a[0..n-1] with std::qsort. Ascending by default (default parameter value).
void sortValues(int* a, int n, bool ascending = true);

// Transformations usable with apply().
int negate(int x);
int square(int x);
int absolute(int x);

} // namespace stats

#endif
