#include "Book.h"
#include <iostream>
#include <cstring>

int Book::totalBooks = 0;

Book::Book(const char* title, int year, Genre genre) {
}

Book::Book(const Book& other) {
}

Book::~Book() {
    delete[] title;
    --totalBooks;
}

void Book::rename(const char* newTitle) {
    // newTitle must refer to a valid string outside this book's title buffer.
    delete[] title;
    title = nullptr;
    title = new char[std::strlen(newTitle) + 1];
    std::strcpy(title, newTitle);
}

void Book::setYear(int newYear) {
    year = newYear;
}

void Book::display() const {
}

const char* Book::getTitle() const {
    return title;
}

int Book::getYear() const {
    return year;
}

int Book::bookCount() {
    return totalBooks;
}

Book::Genre Book::getGenre() const {
}

