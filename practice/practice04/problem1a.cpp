#include <iostream>//no ai used
#include <limits>
#include <string>

//forward declarations
int getInt(const std::string& prompt);
double getDouble(const std::string& prompt);
void convertTemperature(double temp, char scale = 'F');//'F' is default arguement

int main(){

    double temp{};

    while(true){
        std::cout << "1. Convert Celsius to Fahrenheit\n"
        << "2. Convert Fahrenheit to Celsius\n3. Quit\n";

        int choice = getInt("Choose an option: ");

        if(choice == 1){
            std::cout << "You chose to Convert Celsius to Fahrenheit\n";
            temp = getDouble("Enter temperature: ");

            convertTemperature(temp);
        }

        else if(choice == 2){
            std::cout << "You chose to Convert Fahrenheit to Celsius\n";
            temp = getDouble("Enter temperature: ");

            convertTemperature(temp, 'C');
        }

        else if(choice == 3){
            std::cout << "You chose to exit.\nGoodbye\n";
            break;
        }

        else{//just in case
            std::cout << "How did you even get here! That was not one of the options! Try again\n";
        }
    }

    return 0;
}

int getInt(const std::string& prompt){//from project01

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < 1 || input > 3 || std::cin.peek() != '\n') {//peek looks at next character in queue
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

double getDouble(const std::string& prompt){
    double input{};

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


void convertTemperature(double temp, char scale){
    if(scale == 'F'){//formula source: https://www.calculatorsoup.com/calculators/conversions/celsius-to-fahrenheit.php
        temp = (temp * (9.0/5.0) + 32.0);

        std::cout << "Converted: " << temp << " degrees F\n";
    }

    else if(scale == 'C'){//formula source: https://www.calculatorsoup.com/calculators/conversions/fahrenheit-to-celsius.php
        temp = ((temp - 32.0) / (9.0/5.0));

         std::cout << "Converted: " << temp << " degrees C\n";
    }
}