CSI2372A Fall 2026 - Lab Assignment 1 (DataGrid) - starter kit

  stats.h  grid.h  report.h   specifications (complete - do not change the signatures)
  stats.cpp                   Part A  - complete the TODOs
  grid.cpp  report.cpp        Part B  - complete the TODOs
  main.cpp                    Part B  - dispatch table and command handlers (TODOs)
  stats_test.cpp              Part A unit tests (provided)
  Makefile                    separate compilation
  tests/                      input files b1-b6
  expected/                   expected outputs (b3 and b6 are held back)

Build and test (run from this folder):
  make stats_test && ./stats_test
  make datagrid
  ./datagrid tests/b1_basic.txt | diff - expected/b1_basic.out
  make asan && ./datagrid_asan tests/b3_mutations.txt
