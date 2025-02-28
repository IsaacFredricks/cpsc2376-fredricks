#include <iostream>//no ai used
#include "MixedFraction.h"
#include <string>
#include <limits>


int getChoice(const std::string& prompt);//from practice05
char getOperator(const std::string& prompt);
int getInt(const std::string& prompt);

int main() {
    Fraction frac;//makes fraction object

	while (true) {
        std::cout << "1. Enter a fraction\n2. Perform operations (+, -, *, /)\n"
        << "3. Display fraction as mixed fraction\n4. Clear current fraction\n"
        << "5. Exit program\n\n";

        std::cout << "Current Fraction : " << frac << "\n\n";

        int choice{getChoice("Enter the a number 1-5 (inclusive) to make a choice: ")};


        if (choice == 1) {
            std::cout << "You chose to enter a fraction\n";

            frac.setNumerator(getInt("Enter numerator: "));

            frac.setDenominator(getInt("Enter denominator: "));

            frac.simplify();
        }

        else if (choice == 2) {
            std::cout << "You chose to perform operations (+, -, *, /)\n";

            char symbol{ getOperator("Enter the operator: ") };

            Fraction frac2;

            frac2.setNumerator(getInt("Enter numerator for 2nd fraction: "));

            frac2.setDenominator(getInt("Enter denominator for 2nd fraction: "));

            frac2.simplify();

            if (symbol == '+') {
                frac = operator+(frac, frac2);
            }

            else if (symbol == '-') {
                frac = operator-(frac, frac2);
            }

            else if (symbol == '*') {
                frac = operator*(frac, frac2);
            }

            else {
                frac = operator/(frac, frac2);
            }

            std::cout << "Fraction after operation: " << frac << '\n';
        }

        else if (choice == 3) {
            std::cout << "You chose to display fraction as mixed fraction\n";

            MixedFraction mixFrac{ frac };

            std::cout << mixFrac << '\n';
        }

        else if (choice == 4) {
            std::cout << "You chose to clear current fraction\n";

            frac = Fraction();//clears fraction
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

char getOperator(const std::string& prompt) {
    char input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || (input != '+' && input != '-' && input != '*' && input != '/')) {//peek looks at next character in queue
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


int getInt(const std::string& prompt) {

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