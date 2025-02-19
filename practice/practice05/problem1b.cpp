#include <iostream>//ask user for integers, store in vector, then print in reverse order
#include <vector>//no ai used
#include <limits>

int getChoice(const std::string& prompt);
int getInt(const std::string& prompt);

int main(){
    std::vector<int> nums {};

    int count {getChoice("How many numbers would you like in your vector: ")};

    while(count > 0){
        int num {getInt("Enter a number: ")};

        nums.push_back(num);

        count--;
    }

    std::cout << "The numbers in reverse order are: ";
    for(auto it = prev(nums.end()); it != nums.begin() - 1; it--){
        //have to do prev on end since end is one more than the last number
        //begin is 1 more than the first number as well
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    return 0;
}

int getChoice(const std::string& prompt){//from project01

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input == 0 || std::cin.peek() != '\n') {//peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else if(input == 1){
            std::cout << "Too short! Try again\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}

int getInt(const std::string& prompt){//from project01

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