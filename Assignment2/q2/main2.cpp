#include "Fraction.h"
#include <iostream>

// Demonstrates simplification, addition, and live counts before and after a scope.
int main() {
    std::cout << "Live objects before block: " << Fraction::liveCount() << std::endl;

    {
        Fraction a(1, 2), b(2, 4), c(3, -9);

        std::cout << "a: ";
        a.display();
        std::cout << std::endl;

        std::cout << "b: ";
        b.display();
        std::cout << std::endl;

        std::cout << "c: ";
        c.display();
        std::cout << std::endl;

        Fraction d = a.add(b);
        std::cout << "a + b: ";
        d.display();
        std::cout << std::endl;

        std::cout << "Live objects inside block: " << Fraction::liveCount()
                  << std::endl;
    }

    std::cout << "Live objects after block: " << Fraction::liveCount() << std::endl;
    return 0;
}
