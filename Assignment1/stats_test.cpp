// stats_test.cpp -- Part A unit tests (PROVIDED, do not modify).
// Build and run:   make stats_test && ./stats_test
#include <iostream>
#include <cmath>
#include <vector>
#include "stats.h"

static int passed = 0, failed = 0;

static void check(bool ok, const char* what) {
    std::cout << (ok ? "  PASS  " : "  FAIL  ") << what << '\n';
    (ok ? passed : failed)++;
}
static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }
static int twice(int x) { return 2 * x; }

int main() {
    int a[] = {4, -2, 9, 7, 9, 0};
    const int n = sizeof(a) / sizeof(a[0]);

    std::cout << "mean\n";
    check(near(stats::mean(a, n), 27.0 / 6), "mean of {4,-2,9,7,9,0} is 4.5 (no integer division)");
    int odd[] = {1, 2};
    check(near(stats::mean(odd, 2), 1.5), "mean of {1,2} is 1.5");
    check(near(stats::mean(a, 0), 0.0), "mean of an empty range is 0.0");
    check(near(stats::mean(a + 2, 3), 25.0 / 3), "mean of the sub-array a+2 (3 elements)");

    std::cout << "minMax (pointers)\n";
    int lo = 0, hi = 0;
    stats::minMax(a, n, &lo, &hi);
    check(lo == -2 && hi == 9, "minMax(a, 6) gives -2 and 9");
    stats::minMax(a + 3, 1, &lo, &hi);
    check(lo == 7 && hi == 7, "minMax on one element");

    std::cout << "minMax (references, overload)\n";
    std::vector<int> v = {12, 5, 30, -8};
    int vlo = 0, vhi = 0;
    stats::minMax(v, vlo, vhi);
    check(vlo == -8 && vhi == 30, "minMax(vector) gives -8 and 30");

    std::cout << "countAbove (recursive)\n";
    check(stats::countAbove(a, n, 4) == 3, "3 elements above 4");
    check(stats::countAbove(a, n, 9) == 0, "0 elements above 9");
    check(stats::countAbove(a, 0, -100) == 0, "empty range gives 0");
    check(stats::countAbove(a + 1, 2, -5) == 2, "sub-array a+1 of length 2");

    std::cout << "findMax\n";
    int* p = stats::findMax(a, n);
    check(p == a + 2, "findMax returns a pointer to the FIRST 9 (index 2)");
    check(p != nullptr && p - a == 2, "pointer subtraction gives index 2");
    check(stats::findMax(a, 0) == nullptr, "findMax on an empty range is nullptr");

    std::cout << "apply (function pointers)\n";
    int b[] = {1, -2, 3};
    stats::apply(b, 3, stats::square);
    check(b[0] == 1 && b[1] == 4 && b[2] == 9, "apply square");
    stats::apply(b, 3, stats::negate);
    check(b[0] == -1 && b[1] == -4 && b[2] == -9, "apply negate");
    stats::apply(b, 3, stats::absolute);
    check(b[0] == 1 && b[1] == 4 && b[2] == 9, "apply absolute");
    stats::apply(b, 2, twice);
    check(b[0] == 2 && b[1] == 8 && b[2] == 9, "apply a user function to the first 2 elements only");

    std::cout << "sortValues (qsort, default argument)\n";
    int c[] = {5, -1, 12, 0, 5, 3};
    stats::sortValues(c, 6);
    check(c[0] == -1 && c[1] == 0 && c[2] == 3 && c[3] == 5 && c[4] == 5 && c[5] == 12, "ascending by default");
    stats::sortValues(c, 6, false);
    check(c[0] == 12 && c[1] == 5 && c[5] == -1, "descending when ascending == false");
    int big[] = {2000000000, -2000000000, 0};
    stats::sortValues(big, 3);
    check(big[0] == -2000000000 && big[2] == 2000000000, "comparator does not overflow");

    std::cout << "----\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
