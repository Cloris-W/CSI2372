// stats.cpp -- Part A.  Complete every function marked TODO.
// Rules: walk arrays with POINTERS where the comment says so; no std::sort, no loops in countAbove.
#include "stats.h"
#include <cstdlib>   // std::qsort

namespace stats {

static int cmpAscending(const void* x, const void* y) {
    const int lhs = *static_cast<const int*>(x);
    const int rhs = *static_cast<const int*>(y);
    return (lhs > rhs) - (lhs < rhs);
}

static int cmpDescending(const void* x, const void* y) {
    const int lhs = *static_cast<const int*>(x);
    const int rhs = *static_cast<const int*>(y);
    return (lhs < rhs) - (lhs > rhs);
}

double mean(const int* a, int n) {
    if (n <= 0) return 0.0;
    long long sum = 0;
    for (const int* p = a; p < a + n; ++p) {
        sum += *p;
    }
    return static_cast<double>(sum) / n;
}

void minMax(const int* a, int n, int* lo, int* hi) {
    if (n <= 0) return;
    *lo = *hi = *a;
    for (const int* p = a + 1; p < a + n; ++p) {
        if (*p < *lo) *lo = *p;
        if (*p > *hi) *hi = *p;
    }
}

void minMax(const std::vector<int>& v, int& lo, int& hi) {
    minMax(v.data(), static_cast<int>(v.size()), &lo, &hi);
}

int countAbove(const int* a, int n, int threshold) {
    if (n <= 0) return 0;
    return (*a > threshold ? 1 : 0) + countAbove(a + 1, n - 1, threshold);
}

int* findMax(int* a, int n) {
    if (n <= 0) return nullptr;
    int* best = a;
    for (int* p = a + 1; p < a + n; ++p) {
        if (*p > *best) best = p;
    }
    return best;
}

void apply(int* a, int n, int (*f)(int)) {
    for (int* p = a; p < a + n; ++p) {
        *p = f(*p);
    }
}

void sortValues(int* a, int n, bool ascending) {   // the default value appears ONLY in the header
    std::qsort(a, n, sizeof(int), ascending ? cmpAscending : cmpDescending);
}

int negate(int x) { return -x; }
int square(int x) { return x * x; }
int absolute(int x) { return x < 0 ? -x : x; }

} // namespace stats
