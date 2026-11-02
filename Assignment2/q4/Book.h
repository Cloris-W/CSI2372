#ifndef BOOK_H
#define BOOK_H

// Owns a dynamically allocated title and tracks the number of live books.
class Book {
private:
    char* title;
    int year;

public:
    // Allocates exactly enough memory for the title and its null terminator.
    Book(const char* title = "Untitled", int year = 0);

    // Creates an independent copy of the other book's title.
    Book(const Book& other);

    // Releases the title and decrements the live-object count.
    ~Book();

    // Releases the old title and stores a dynamically allocated replacement.
    void rename(const char* newTitle);
    void setYear(int newYear);

    // Prints the title and year on one line.
    void display() const;
    const char* getTitle() const;
    int getYear() const;
    static int bookCount();

private:
    static int totalBooks;
};

// Takes a book by value to demonstrate the copy constructor.
void describe(Book aBook);

#endif
