#include "Book.h"
#include <iostream>
#include <cstring>

int Book::totalBooks = 0;

Book::Book(const char* title, int year)
    : title(new char[std::strlen(title) + 1]), year(year) {
    std::strcpy(this->title, title);
    ++totalBooks;
}

Book::Book(const Book& other)
    : title(new char[std::strlen(other.title) + 1]), year(other.year) {
    std::strcpy(title, other.title);
    ++totalBooks;
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
    std::cout << title << " (" << year << ")" << std::endl;
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
