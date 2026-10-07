// stats.cpp -- Part A.  Complete every function marked TODO.
// Rules: walk arrays with POINTERS where the comment says so; no std::sort, no loops in countAbove.
#include "stats.h"
#include <cstdlib>   // std::qsort

namespace stats {

double mean(const int* a, int n) {
    // TODO: pointer walk (for (const int* p = a; p < a + n; ++p)); beware integer division;
    //       return 0.0 when n <= 0.
    return 0.0;
}

void minMax(const int* a, int n, int* lo, int* hi) {
    // TODO: results are returned through the pointers lo and hi.
}

void minMax(const std::vector<int>& v, int& lo, int& hi) {
    // TODO: results are returned through the references lo and hi.
    //       Hint: you may reuse the pointer version (v.data() is a pointer to the first element).
}

int countAbove(const int* a, int n, int threshold) {
    // TODO: RECURSIVE. Base case first. Recurse on the rest of the array: a + 1, n - 1.
    return 0;
}

int* findMax(int* a, int n) {
    // TODO: return a pointer to the first largest element, or nullptr when n <= 0.
    return nullptr;
}

void apply(int* a, int n, int (*f)(int)) {
    // TODO: replace each element x by f(x), walking the array with a pointer.
}

// TODO: write two qsort comparators with the signature
//           static int cmpAscending(const void* x, const void* y);
//           static int cmpDescending(const void* x, const void* y);
//       Convert the generic pointers with static_cast<const int*>(...) before dereferencing.
//       Return a negative, zero or positive value -- WITHOUT computing a - b (it can overflow).

void sortValues(int* a, int n, bool ascending) {   // the default value appears ONLY in the header
    // TODO: call std::qsort(a, n, sizeof(int), <comparator>)
}

int negate(int x) { return -x; }
int square(int x) { return x * x; }
int absolute(int x) { return x < 0 ? -x : x; }

} // namespace stats
