#include "Library.h"
#include <iostream>
#include <cstring>

Library::Library() : currentCount(0) {
}

bool Library::addBook(const char* title, int year) {
    if (currentCount >= MAX_BOOKS) {
        return false;
    }

    books[currentCount].rename(title);
    books[currentCount].setYear(year);
    ++currentCount;
    return true;
}

int Library::findByTitle(const char* title) const {
    for (int i = 0; i < getCurrentCount(); ++i) {
        if (std::strcmp(books[i].getTitle(), title) == 0) {
            return i;
        }
    }
    return -1;
}

void Library::displayAll() const {
    for (int i = 0; i < getCurrentCount(); ++i) {
        std::cout << i << ": ";
        books[i].display();
    }
}

int Library::getCurrentCount() const {
    return currentCount;
}
