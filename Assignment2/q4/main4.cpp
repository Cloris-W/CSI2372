#include "Library.h"
#include <iostream>

// Demonstrates adding five books, displaying them, and searching for titles.
int main() {
    Library library;
    library.addBook("The Hobbit", 1937);
    library.addBook("Pride and Prejudice", 1813);
    library.addBook("Nineteen Eighty-Four", 1949);
    library.addBook("The Little Prince", 1943);
    library.addBook("A Brief History of Time", 1988);

    library.displayAll();

    const char* presentTitle = "The Hobbit";
    const char* absentTitle = "Dune";

    int index = library.findByTitle(presentTitle);
    std::cout << "Search for " << presentTitle << ": ";
    if (index == -1) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found at index " << index << std::endl;
    }

    index = library.findByTitle(absentTitle);
    std::cout << "Search for " << absentTitle << ": ";
    if (index == -1) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found at index " << index << std::endl;
    }

    // On leaving main, Library's implicit destructor destroys its members.
    // All 20 Book elements exist, including the 15 unused default books.
    // They are destroyed in reverse array order, from books[19] to books[0].
    // Each Book destructor deletes its own title and decrements totalBooks.
    // Library needs no custom destructor because its members clean themselves up.
    return 0;
}
