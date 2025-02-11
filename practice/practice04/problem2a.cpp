#include <iostream>
#include <limits>
#include <string>

template<typename V>
V getNum(const std::string& prompt){
    V input{};

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

        else if(num1 % num2 > 0){//checks if both int and has a remainder
            auto divide = num1 / num2;
            auto remainder = num1 % num2;

            std::cout << "Result: " << divide << " with a remainder of " << remainder << '\n';
        }

        else{
            std::cout << "Result: " << (num1 / num2) << '\n';
        }
    }
}


//forward declaration
char getChar(const std::string& prompt);

int main(){
    auto num1 {getNum("Enter first number: ")};
    auto num2 {getNum("Enter second number: ")};
    char symbol {getChar("Enter operation (+, -, *, /): ")};

    calculate(num1, num2, symbol);



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
