#include <iostream>
#include <limits>
#include <string>


template<typename T, typename U>
void calculate(T num1, U num2, char symbol){
    
    if(symbol == '+'){
        std::cout << "Result: " << (num1 + num2) << '\n';
    }

    else if(symbol == '-'){
        std::cout << "Result: " << (num1 - num2) << '\n';
    }

    else if(symbol == '*'){
        std::cout << "Result: " << (num1 * num2) << '\n';
    }

    else if(symbol == '/'){
        if(num2 == 0){
            std::cout << "Can't operate that. Divide by 0\n";
        }

        else{
            std::cout << "Result: " << (num1 / num2) << '\n';
        }
    }
}


template <typename V>
V getNum(const std::string& prompt){
    V input{};

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

//forward declaration
char getChar(const std::string& prompt);
int getChoice(const std::string& prompt);

int main(){
    int choice1 {getChoice("Enter 1 if you want an int or 2 if you want a double for your first number: ")};

    int numOneInt {};
    double numOneDouble {};
    int numTwoInt {};
    double numTwoDouble {};

    if(choice1 == 1){
        numOneInt = getNum<int>("Enter first number: ");
    }

    else if(choice1 == 2){
        numOneDouble = getNum<double>("Enter first number: ");
    }

    int choice2 {getChoice("Enter 1 if you want an int or 2 if you want a double for your second number: ")};

    if(choice2 == 1){
        numTwoInt = getNum<int>("Enter second number: ");
    }

    else if(choice2 == 2){
        numTwoDouble = getNum<double>("Enter second number: ");
    }

    char symbol {getChar("Enter operation (+, -, *, /): ")};

    if(choice1 == 1 && choice2 == 1){
        calculate(numOneInt, numTwoInt, symbol);
    }

    else if(choice1 == 1 && choice2 == 2){
        calculate(numOneInt, numTwoDouble, symbol);
    }

    else if(choice1 == 2 && choice2 == 1){
        calculate(numOneDouble, numTwoInt, symbol);
    }

    else if(choice1 == 2 && choice2 == 2, symbol){
        calculate(numOneDouble, numTwoDouble, symbol);
    }

    return 0;
}

char getChar(const std::string& prompt){
    char input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || !(input == '+' || input == '-' || input == '*' || input == '/')) {//peek looks at next character in queue
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

int getInt(const std::string& prompt){
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

int getChoice(const std::string& prompt){//want choice to have different range than getInt
    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input > 2 || input < 1 || std::cin.peek() != '\n') {//peek looks at next character in queue
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
