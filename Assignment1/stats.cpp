// stats.cpp -- Part A: pointer-based statistics.
// Rules: walk arrays with POINTERS where the comment says so; no std::sort, no loops in countAbove.
#include "stats.h"
#include <cstdlib>   // std::qsort

namespace stats {

// Compare the two borrowed int elements x and y for ascending qsort; return a sign without subtraction overflow.
static int cmpAscending(const void* x, const void* y) {
    const int lhs = *static_cast<const int*>(x);
    const int rhs = *static_cast<const int*>(y);
    return (lhs > rhs) - (lhs < rhs);
}

// Compare the two borrowed int elements x and y for descending qsort; return a sign without subtraction overflow.
static int cmpDescending(const void* x, const void* y) {
    const int lhs = *static_cast<const int*>(x);
    const int rhs = *static_cast<const int*>(y);
    return (lhs < rhs) - (lhs > rhs);
}

// Read n elements starting at borrowed pointer a; return their mean, or 0.0 for n <= 0. No ownership transfer.
double mean(const int* a, int n) {
    if (n <= 0) return 0.0;
    long long sum = 0;
    for (const int* p = a; p < a + n; ++p) {
        sum += *p;
    }
    return static_cast<double>(sum) / n;
}

// Read n >= 1 elements from borrowed a; write the minimum and maximum through caller-owned lo and hi.
void minMax(const int* a, int n, int* lo, int* hi) {
    if (n <= 0) return;
    *lo = *hi = *a;
    for (const int* p = a + 1; p < a + n; ++p) {
        if (*p < *lo) *lo = *p;
        if (*p > *hi) *hi = *p;
    }
}

// Read nonempty v without copying it; reuse the pointer overload to write results into reference parameters lo and hi.
void minMax(const std::vector<int>& v, int& lo, int& hi) {
    minMax(v.data(), static_cast<int>(v.size()), &lo, &hi);
}

// Recursively count values greater than threshold in n elements of borrowed a; return the count without modifying the array.
int countAbove(const int* a, int n, int threshold) {
    if (n <= 0) return 0;
    return (*a > threshold ? 1 : 0) + countAbove(a + 1, n - 1, threshold);
}

// Return a borrowed pointer to the first maximum among n elements of a, or nullptr for n <= 0; caller must not delete it.
int* findMax(int* a, int n) {
    if (n <= 0) return nullptr;
    int* best = a;
    for (int* p = a + 1; p < a + n; ++p) {
        if (*p > *best) best = p;
    }
    return best;
}

// Replace n elements of caller-owned a with f(element), walking with a pointer. f accepts and returns int; no allocation.
void apply(int* a, int n, int (*f)(int)) {
    for (int* p = a; p < a + n; ++p) {
        *p = f(*p);
    }
}

// Sort n elements of caller-owned a in place using qsort; ascending selects the comparator. No ownership transfer.
void sortValues(int* a, int n, bool ascending) {   // the default value appears ONLY in the header
    std::qsort(a, n, sizeof(int), ascending ? cmpAscending : cmpDescending);
}

// Return the negative of value x; the result must be representable as int.
int negate(int x) { return -x; }
// Return x squared; the result must be representable as int.
int square(int x) { return x * x; }
// Return the absolute value of x; the result must be representable as int.
int absolute(int x) { return x < 0 ? -x : x; }

} // namespace stats
