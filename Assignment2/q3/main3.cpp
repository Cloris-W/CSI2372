#include "Book.h"
#include <iostream>

// Displays a by-value copy to demonstrate its temporary lifetime.
void describe(Book aBook) {
    std::cout << "Describing: ";
    aBook.display();
    std::cout << "Books inside describe: " << Book::bookCount() << std::endl;
}

// Demonstrates live counts, renaming, and independent titles after copying.
int main() {
    {
        Book b1("The Hobbit", 1937);
        std::cout << "Books after creating b1: " << Book::bookCount() << std::endl;

        std::cout << "Books before describe: " << Book::bookCount() << std::endl;
        describe(b1);
        std::cout << "Books after describe: " << Book::bookCount() << std::endl;

        b1.rename("The Hobbit (Revised Edition)");
        std::cout << "b1 after rename: ";
        b1.display();

        // Initialization calls the copy constructor, not copy assignment.
        Book b2 = b1;
        std::cout << "b1 after copying: ";
        b1.display();
        std::cout << "b2 after copying: ";
        b2.display();
        std::cout << "Books after creating b2: " << Book::bookCount() << std::endl;

        std::cout << "Separate title buffers: "
                  << (b1.getTitle() != b2.getTitle() ? "yes" : "no") << std::endl;

        b2.rename("Something Completely Different");
        std::cout << "b2 after rename: ";
        b2.display();
        std::cout << "b1 remains unchanged: ";
        b1.display();
    }

    std::cout << "Books after block: " << Book::bookCount() << std::endl;
    return 0;
}
