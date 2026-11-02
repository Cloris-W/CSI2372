#include "Book.h"
#include <iostream>
#include <cstring>

int Book::totalBooks = 0;

Book::Book(const char* title, int year, Genre genre)
    : title(new char[std::strlen(title) + 1]), year(year), genre(genre) {
    std::strcpy(this->title, title);
    ++totalBooks;
}

Book::Book(const Book& other)
    : title(new char[std::strlen(other.title) + 1]),
      year(other.year), genre(other.genre) {
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
    std::cout << title << " (" << year << ") - ";

    // if (genre == 1) would not compile: enum class does not implicitly
    // convert to int, preventing accidental comparisons with unrelated numbers.
    switch (genre) {
        case Genre::NOVEL:
            std::cout << "Novel";
            break;
        case Genre::SCIENCE_FICTION:
            std::cout << "Science Fiction";
            break;
        case Genre::HISTORY:
            std::cout << "History";
            break;
        case Genre::CHILDRENS:
            std::cout << "Childrens";
            break;
        case Genre::OTHER:
            std::cout << "Other";
            break;
    }
    std::cout << std::endl;
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
    return genre;
}
