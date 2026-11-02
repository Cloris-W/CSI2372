#include "Book.h"
#include <iostream>

// Displays a by-value copy, including its readable genre.
void describe(Book aBook) {
    std::cout << "Describing: ";
    aBook.display();
    std::cout << "Books inside describe: " << Book::bookCount() << std::endl;
}

// Demonstrates all five genres and preserves the deep-copy demonstration.
int main() {
    {
        Book b1("The Hobbit", 1937, Book::Genre::NOVEL);
        std::cout << "Books after creating b1: " << Book::bookCount() << std::endl;

        std::cout << "Books before describe: " << Book::bookCount() << std::endl;
        describe(b1);
        std::cout << "Books after describe: " << Book::bookCount() << std::endl;

        b1.rename("The Hobbit (Revised Edition)");
        std::cout << "b1 after rename: ";
        b1.display();

        Book b2 = b1;
        std::cout << "b1 after copying: ";
        b1.display();
        std::cout << "b2 after copying: ";
        b2.display();
        std::cout << "Separate title buffers: "
                  << (b1.getTitle() != b2.getTitle() ? "yes" : "no") << std::endl;
        std::cout << "Genre copied: "
                  << (b1.getGenre() == b2.getGenre() ? "yes" : "no") << std::endl;

        b2.rename("Something Completely Different");
        std::cout << "b2 after rename: ";
        b2.display();
        std::cout << "b1 remains unchanged: ";
        b1.display();

        Book scienceFiction("Dune", 1965, Book::Genre::SCIENCE_FICTION);
        Book history("The Guns of August", 1962, Book::Genre::HISTORY);
        Book childrens("Charlotte's Web", 1952, Book::Genre::CHILDRENS);
        // Omitting the third argument demonstrates the default OTHER genre.
        Book other("A Brief History of Time", 1988);

        std::cout << "All five genres:" << std::endl;
        describe(b1);
        describe(scienceFiction);
        describe(history);
        describe(childrens);
        describe(other);
    }

    std::cout << "Books after block: " << Book::bookCount() << std::endl;
    return 0;
}
