# DataGrid -- separate compilation: each .cpp is compiled to a .o, then the .o files are linked.
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
OBJS     = main.o stats.o grid.o report.o

datagrid: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o:   main.cpp stats.h grid.h report.h
stats.o:  stats.cpp stats.h
grid.o:   grid.cpp grid.h
report.o: report.cpp report.h

# Part A unit tests (does not need main.cpp)
stats_test: stats_test.o stats.o
	$(CXX) $(CXXFLAGS) -o $@ stats_test.o stats.o
stats_test.o: stats_test.cpp stats.h

# Build with AddressSanitizer to detect leaks, dangling pointers, double/wrong deletes
asan:
	$(CXX) -std=c++17 -Wall -g -fsanitize=address,undefined -o datagrid_asan main.cpp stats.cpp grid.cpp report.cpp

clean:
	rm -f *.o datagrid stats_test datagrid_asan
