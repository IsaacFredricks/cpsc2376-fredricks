#include <iostream>//no ai used
#include "Fraction.h"
#include <string>
#include <limits>
#include <numeric>//for gcd in cimplify
#include <algorithm>//also for gcd


int getChoice(std::string& prompt);//from practice05
char getOperator(std::string& prompt);
int getInt(std::string& prompt);

int main() {
    Fraction frac;//makes fraction object

	while (true) {
        std::cout << "1. Enter a fraction\n2. Perform operations (+, -, *, /)\n "
        << "3. Display fraction as mixed fraction\n4. Clear current fraction\n"
        << " 5. Exit program\n\n";

        int choice{getChoice("Enter the a number 1-5 (inclusive) to make a choice: ")};


        if (choice == 1) {
            std::cout << "You chose to enter a fraction\n";

        }

        else if (choice == 2) {
            std::cout << "You chose to perform operations (+, -, *, /)\n";
        }

        else if (choice == 3) {
            std::cout << "You chose to display fraction as mixed fraction\n";
        }

        else if (choice == 4) {
            std::cout << "You chose to clear current fraction\n";
        }

        else if (choice == 5) {
            std::cout << "You chose to exit\n";
            std::cout << "Goodbye.\n";
            break;
        }

        else {//just in case
            std::cout << "How did you even get here?\n";
        }
	}

	return 0;
}

int getChoice(const std::string& prompt) {//from project01

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || input < 1 || input > 5) {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}

char getOperator(std::string& prompt) {
    char input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || (input != '+' || input != '-' || input != '*' || input != '/') {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}


int getInt(std::string& prompt) {

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n') {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}