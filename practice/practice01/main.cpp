#include <iostream>//no ai used
#include <vector>
#include <limits>//for getInt()

//forward declarations:
int getInt(const std::string& prompt);
void printVector(const std::vector<int>& vec);
std::vector<int>& doubleVector(std::vector<int>& vec);
int getSum(std::vector<int>& vec);
void printMultiples(const std::vector<int>& vec, int multiple);


int main(){

    std::vector<int> vec {};

    while(true){
        //the menu
        std::cout << "\n1. Add item to vector\n2. Print the vector\n3. Double the vector"
        << "\n4. Find the sum\n5. Print multiples of a user-defined value\n6. Exit\n";

        int num {getInt("Enter a number 1-6 (inclusive): ")};

        if(num == 1){
            std::cout << "You chose to add item to vector\n";

            int addedNum {getInt("Enter the number you want to add to the vector: ")};

            vec.push_back(addedNum);
            std::cout << "Number added\n";
        }

        else if(num == 2){
            std::cout << "You chose to print the vector\n";
            printVector(vec);
        }

        else if(num == 3){
            std::cout << "You chose to double the vector\n";
            doubleVector(vec);
            std::cout << "The numbers in the vector have been doubled\n";
        }

        else if(num == 4){
            std::cout << "You chose to find the sum\n";

            std::cout << "The sum is " << getSum(vec) << '\n';
        }

        else if(num == 5){
            std::cout << "You chose to print multiples of a user defined value\n";

            int multiple {getInt("Enter a number: ")};

            printMultiples(vec, multiple);
        }

        else if(num == 6){
            std::cout << "You chose to exit\n";
            std::cout << "Goodbye.\n";
            break;//exits loop
        }

        else{
            std::cout << "That was not one of the numbers listed. Please try again\n";
        }
    }

    return 0;
}//creator: Isaac Fredricks


//actual functions
int getInt(const std::string& prompt){

    int input {};

    while (true){
        std::cout << prompt;
        std::cin >> input;
    
        if(std::cin.fail()){
            std::cin.clear(); //clears the error
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input
        
             std::cout << "Inproper input. please try again.\n";
        }
        else{
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
            //discards any extra input
            break;//exits loop
        }
    }
}

void printVector(const std::vector<int>& vec){//don't want to modify vector so const
    for(int num : vec){
        std::cout << num << ' ';
    }
}

std::vector<int>& doubleVector(std::vector<int>& vec){//uses pass by ref to actually modify the values
    for(int i{0}; i < vec.size(); i++){
        vec.at(i) *= 2;
    }

    return vec;
}

int getSum(std::vector<int>& vec){
    int sum{};
    for(int i{0}; i < vec.size(); i++){
        sum += vec.at(i);
    }

    return sum;
}

void printMultiples(const std::vector<int>& vec, int multiple){
    std::cout << "The multiples of " << multiple << " are as follows: ";
    for(int i{0}; i < vec.size(); i++){
        if(vec.at(i) % multiple == 0){
            std::cout << vec.at(i) << ' ';
        }
    }

    std::cout << "\nThat's all folks!\n";
}