#ifndef BOOK_H
#define BOOK_H

// Owns a title, records its genre, and tracks the number of live books.
class Book {
public:
    enum class Genre { NOVEL, SCIENCE_FICTION, HISTORY, CHILDRENS, OTHER };

    // Allocates the title and initializes the year and genre.
    Book(const char* title = "Untitled", int year = 0,
         Genre genre = Genre::OTHER);

    // Deep-copies the title and copies the year and genre.
    Book(const Book& other);
    ~Book();

    // Releases the old title and stores a dynamically allocated replacement.
    void rename(const char* newTitle);
    void setYear(int newYear);

    // Prints the title, year, and readable genre selected with switch.
    void display() const;
    const char* getTitle() const;
    int getYear() const;
    Genre getGenre() const;
    static int bookCount();

private:
    char* title;
    int year;
    Genre genre;
    static int totalBooks;
};

// Takes a book by value to demonstrate copying and genre display.
void describe(Book aBook);

#endif
