// report.cpp -- Part B: numbered and formatted reports.
#include "report.h"
#include <iostream>
#include <iomanip>

// The global counter is DEFINED here; report.h only DECLARES it (extern). See Question 6.
int reportsPrinted = 0;

static const int LABEL_WIDTH = 10;      // hidden global: internal linkage (this file only)

namespace report {

// Print title with a persistent report number; increment the local static counter and reportsPrinted. No ownership transfer.
void header(const std::string& title) {
    static int counter = 0;
    ++counter;
    ++reportsPrinted;
    std::cout << "==== Report #" << counter << ": " << title << " ====" << '\n';
}

// Print borrowed label and integer value in aligned fields; return no value.
void print(const std::string& label, int value) {
    std::cout << "  " << std::left << std::setw(LABEL_WIDTH) << label << std::right
              << ": " << value << '\n';
}

// Print borrowed label and real value with two decimals; remove fixed formatting afterwards. Returns no value.
void print(const std::string& label, double value) {
    std::cout << "  " << std::left << std::setw(LABEL_WIDTH) << label << std::right
              << ": " << std::fixed << std::setprecision(2) << value << '\n';
    std::cout.unsetf(std::ios::fixed);
}

} // namespace report
