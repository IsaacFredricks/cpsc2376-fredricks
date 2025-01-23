#include <iostream>//no ai used
#include <vector>
#include <limits>

//forward declarations:
int getInt(const std::string& prompt);

//menu
int main(){

    while(true){
        std::cout << "\n1. Add item to vector\n2. Print the vector\n3. Double the vector"
        << "\n4. Find the sum\n5. Print multiples of a user-defined value\n6. Exit\n";

        std::cout << "Enter a number 1-6 (inclusive): ";
    }

    return 0;
}//creator: Isaac Fredricks


//actual functions
int getInt(const std::string& prompt){
    int input {};

    while (true){
        std::cout << prompt;
        std::cin >> input;
    
        if(std::cin.fail() || input < 0){
            std::cin.clear(); //clears the error
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input
        
             std::cout << "Inproper input. please try again. "
            << "Text should reappear for ship inputs except for mission inputs." 
            << " For that just type below for inputs and hit enter. "
            << "DO IT RIGHT THIS TIME.\n";
        }
        else{
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
            //discards any extra input
            break;//exits loop
        }
    }
}