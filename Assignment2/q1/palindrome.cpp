#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>

const int MAX_LEN = 200;

// Checks letters from both ends, ignoring nonletters and letter case.
bool isPalindrome(const char* phrase);

// Reads phrases until FIN and prints the result for each phrase.
int main() {
    char line[MAX_LEN];

    while (true) {
        std::cout << "Enter a phrase (or FIN to quit): ";
        std::cin.getline(line, MAX_LEN);

        if (std::cin.bad()) {
            break;
        }
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                break;
            }
            // Keep the first 199 characters and discard the rest of this line.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (std::strcmp(line, "FIN") == 0) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        std::cout << '"' << line << '"';
        if (isPalindrome(line)) {
            std::cout << " is a palindrome." << std::endl;
        } else {
            std::cout << " is NOT a palindrome." << std::endl;
        }
    }

    return 0;
}

bool isPalindrome(const char* phrase) {
    int left = 0;
    int right = static_cast<int>(std::strlen(phrase)) - 1;

    while (left < right) {
        // cctype functions require unsigned-char values (or EOF).
        while (left < right &&
               !std::isalpha(static_cast<unsigned char>(phrase[left]))) {
            ++left;
        }
        while (left < right &&
               !std::isalpha(static_cast<unsigned char>(phrase[right]))) {
            --right;
        }

        if (std::tolower(static_cast<unsigned char>(phrase[left])) !=
            std::tolower(static_cast<unsigned char>(phrase[right]))) {
            return false;
        }
        ++left;
        --right;
    }

    return true;
}
