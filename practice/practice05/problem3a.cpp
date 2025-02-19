#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>//for pow() function

int getChoice(const std::string& prompt);
int getInt(const std::string& prompt);

int main(){
    std::vector<int> nums{};
    int count {getChoice("How many numbers would you like?: ")};

    while(count > 0){
        int num {getInt("Enter a number: ")};

        nums.push_back(num);

        count--;
    }

    std::cout << "Each number squared: ";

    std::for_each(nums.begin(), nums.end(), [](int num){
        num = pow(num, 2);//doesn't actually change the value of the nums inside the vector
        std::cout << num << ' ';
    });

    std::cout << '\n';

    std::vector<int> squaredNums {};
    for(int i {0}; i < nums.size(); i++){
        squaredNums.push_back(pow(nums.at(i), 2.0));
    }

    auto sum = [squaredNums](){
        int total = std::accumulate(squaredNums.begin(), squaredNums.end(), 0);
        std::cout << "The sum of the squared numbers: " << total << '\n';
    };

   sum();

   //std::cout << "The sum of the squared numbers: " << total << '\n';
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