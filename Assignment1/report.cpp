// report.cpp -- Part B.  Complete every part marked TODO.
#include "report.h"
#include <iostream>
#include <iomanip>

// The global counter is DEFINED here; report.h only DECLARES it (extern). See Question 6.
int reportsPrinted = 0;

static const int LABEL_WIDTH = 10;      // hidden global: internal linkage (this file only)

namespace report {

void header(const std::string& title) {
    static int counter = 0;
    ++counter;
    ++reportsPrinted;
    std::cout << "==== Report #" << counter << ": " << title << " ====" << '\n';
}

void print(const std::string& label, int value) {
    std::cout << "  " << std::left << std::setw(LABEL_WIDTH) << label << std::right
              << ": " << value << '\n';
}

void print(const std::string& label, double value) {
    std::cout << "  " << std::left << std::setw(LABEL_WIDTH) << label << std::right
              << ": " << std::fixed << std::setprecision(2) << value << '\n';
    std::cout.unsetf(std::ios::fixed);
}

} // namespace report
