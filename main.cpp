#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

constexpr int kRows = 6;
constexpr int kCols = 5;

const std::string kBoard[kRows] = {
    "abcde",
    "fghij",
    "klmno",
    "pqrst",
    "uvwxy",
    "z    "
};

char displayCell(char letter) {
    return (letter == ' ') ? '_' : letter;
}

bool readInt(const std::string& prompt, int low, int high, int& out) {
    while (true) {
        std::cout << prompt << " (" << low << "-" << high << "): ";

        int value = 0;
        if (std::cin >> value) {
            if (value >= low && value <= high) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                out = value;
                return true;
            }
            std::cout << "  Please enter a number from " << low << " to " << high
                      << ".\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (std::cin.eof()) {
            std::cout << "\n  Input ended. Stopping.\n";
            return false;
        }

        std::cout << "  That was not a whole number. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printBoard() {
    std::cout << "    ";
    for (int col = 0; col < kCols; ++col) {
        std::cout << col << ' ';
    }
    std::cout << "\n";

    for (int row = 0; row < kRows; ++row) {
        std::cout << "    ";
        for (int col = 0; col < kCols; ++col) {
            std::cout << displayCell(kBoard[row][col]) << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printCapturedBoard(const std::vector<int>& columns) {
    std::cout << "    ";
    for (int row = 0; row < kRows; ++row) {
        std::cout << row << ' ';
    }
    std::cout << "\n";

    for (int column : columns) {
        std::cout << "    ";
        for (int row = 0; row < kRows; ++row) {
            std::cout << displayCell(kBoard[row][column]) << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

}

int main() {
    std::cout << "=== MindReader ===\n";
    std::cout << "Think of a name. I will guess it without you typing a letter.\n";
    std::cout << "(You can include spaces between words.)\n\n";

    constexpr int kMaxLength = 100;
    int length = 0;
    if (!readInt("How many letters are in the name", 1, kMaxLength, length)) {
        return 0;
    }

    std::cout << "\nHere is the board. Note the COLUMN (0-4) of each of your "
                 "letters.\n\n";
    printBoard();

    std::vector<int> columns(length, 0);
    for (int i = 0; i < length; ++i) {
        const std::string prompt =
            "Letter #" + std::to_string(i + 1) + ": which column";
        if (!readInt(prompt, 0, kCols - 1, columns[i])) {
            return 0;
        }
    }

    std::system("cls");

    std::cout << "=== MindReader ===\n\n";
    std::cout << "Here are your letters again -- one row per letter, in order.\n";
    std::cout << "Tell me the POSITION (0-5) of each letter within its row.\n\n";

    printCapturedBoard(columns);

    std::string guessedName;
    for (int i = 0; i < length; ++i) {
        const std::string prompt =
            "Letter #" + std::to_string(i + 1) + ": which position";
        int position = 0;
        if (!readInt(prompt, 0, kRows - 1, position)) {
            return 0;
        }

        guessedName += kBoard[position][columns[i]];
    }

    std::cout << "The name you were thinking of is: \"" << guessedName << "\"\n";
    return 0;
}
