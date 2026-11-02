#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"

const int MAX_BOOKS = 20;

// Stores books in a fixed-size array and tracks the number of occupied slots.
class Library {
private:
    Book books[MAX_BOOKS];
    int currentCount;

public:
    // Initializes an empty library; all array elements are default-constructed.
    Library();

    // Updates the next available Book using rename and setYear; false if full.
    bool addBook(const char* title, int year);

    // Uses strcmp to find the first exact title match; returns -1 if absent.
    int findByTitle(const char* title) const;

    // Prints each occupied entry as index: title (year).
    void displayAll() const;
    int getCurrentCount() const;
};

#endif
