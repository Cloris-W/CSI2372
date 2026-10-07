// report.cpp -- Part B.  Complete every part marked TODO.
#include "report.h"
#include <iostream>
#include <iomanip>

// The global counter is DEFINED here; report.h only DECLARES it (extern). See Question 6.
int reportsPrinted = 0;

static const int LABEL_WIDTH = 10;      // hidden global: internal linkage (this file only)

namespace report {

void header(const std::string& title) {
    // TODO: use a STATIC LOCAL counter to number the reports 1, 2, 3, ...
    //       and increment the global reportsPrinted.
    //       Output format:   ==== Report #3: row 0 ====
}

void print(const std::string& label, int value) {
    std::cout << "  " << std::left << std::setw(LABEL_WIDTH) << label << std::right
              << ": " << value << '\n';
}

void print(const std::string& label, double value) {
    // TODO: same layout as the int version, with exactly 2 decimals (std::fixed, std::setprecision).
    //       Restore the stream afterwards: std::cout.unsetf(std::ios::fixed);
}

} // namespace report
