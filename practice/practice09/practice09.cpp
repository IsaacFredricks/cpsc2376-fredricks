#include <iostream>
#include <limits>
#include <string>
#include <cctype>//to convert to lower case

/*
You are brewing potions in a fantasy lab.

Create these variables:

float redPotion{0.0f};    // Amount of red potion in mL
float bluePotion{0.0f};   // Amount of blue potion in mL
float* flask{nullptr};    // Pointer to the selected potion

Inside a while loop:

Ask the user which potion to add liquid to ("Red" or "Blue").
Update the flask pointer to point to the correct potion.
Ask how many milliliters to add and update it using the flask pointer.
Display both potion levels.
Repeat until the user types "Done" instead of a potion color.
*/

std::string getPotion(const std::string& prompt);

int main() {
    float redPotion{ 0.0f };    // Amount of red potion in mL
    float bluePotion{ 0.0f };   // Amount of blue potion in mL
    float* flask{ nullptr };    // Pointer to the selected potion

    while (true) {
        std::string choice{ getPotion("Which potion do you want to add to red or blue: ") };

        if (choice == "red") {
            std::cout << "You chose red\n";
        }

        else if (choice == "blue") {
            std::cout << "You chose blue\n";
        }

    }

    return 0;
}

std::string getPotion(const std::string& prompt) {

    std::string choice{};
    std::string lowerCase{};
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, choice);

        //source: https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case

        for (auto c : choice) {//converts string to lowercase one char at a time
            lowerCase += tolower(c);
        }

        if (std::cin.fail() || !(lowerCase == "red" || lowerCase == "blue")
            || std::cin.peek() != '\n') {//peek looks at next character in queue
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
    return lowerCase;
}