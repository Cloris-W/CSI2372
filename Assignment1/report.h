// report.h -- report headers, numbering and small shared helpers.
// CSI2372A Fall 2026 -- Lab Assignment 1 (DataGrid)
#ifndef REPORT_H
#define REPORT_H

#include <string>

namespace report {

// Prints   ==== Report #k: title ====   where k counts the calls (1, 2, 3, ...).
// The counter is a STATIC LOCAL variable of this function.
void header(const std::string& title);

// Overloads: print a labelled value on one line.
//   print("mean", 2.5)  ->  "  mean      : 2.50"
//   print("max",  7)    ->  "  max       : 7"
void print(const std::string& label, int value);
void print(const std::string& label, double value);

// Return whether i is between inclusive bounds lo and hi; all parameters are passed by value.
// Inline helper, defined in the header (Lecture 2, Part 8).
inline bool inRange(int i, int lo, int hi) { return lo <= i && i <= hi; }

} // namespace report

// Number of report headers printed so far. DEFINED in report.cpp;
// main.cpp reaches it with an extern declaration.
extern int reportsPrinted;

#endif
