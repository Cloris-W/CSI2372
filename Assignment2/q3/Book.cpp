#include "Book.h"
#include <iostream>
#include <cstring>

int Book::totalBooks = 0;

Book::Book(const char* title, int year) {
}

Book::Book(const Book& other) {
}

Book::~Book() {
}

void Book::rename(const char* newTitle) {
}

void Book::setYear(int newYear) {
}

void Book::display() const {
}

const char* Book::getTitle() const {
}

int Book::getYear() const {
}

int Book::bookCount() {
}
