#include <iostream>//no ai used
#include <fstream>//for file input/output
#include <limits>//for getInt


int getInt(const std::string& prompt);//forward declarations
double getDouble(const std::string& prompt);
void checkBalance(const std::string& fileName);
void writeToFile(std::string& fileName, double balance);


int main(){
    //insert code here
    double balance{};//if the txt file can't be read, set the balance to $100.00
    std::string fileName("account_balance.txt");
    checkBalance(fileName);//checks if the file is there on startup

    while(true){
        std::cout << "\n======Menu======\n1. Check Balance\n2. Deposit Money\n3. Withdraw money\n4. Exit\n";
        int choice {getInt("Enter a number 1-4 (inclusive): ")};

        if(choice == 1){
            std::cout << "You chose to check balance\n";

            checkBalance(fileName);
        }

        else if(choice == 2){
            std::cout << "You chose to deposit money\n";

            double deposit {getDouble("Enter an ammount to deposit: ")};
        }   

        else if(choice == 3){
            std::cout << "You chose to withdraw money\n";

            double withdraw {getDouble("Enter an ammount to withdraw: ")};
        }

        else if(choice == 4){
            std::cout << "Bye.";
            break;
        }

        else{
            std::cout << "That was not one of the options\n";
        } 
    }
    

    return 0;
}

int getInt(const std::string& prompt){//like getInt from practice01

    int input {};

    while (true){
        std::cout << prompt;
        std::cin >> input;
    
        if(std::cin.fail() || input < 0){
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

double getDouble(const std::string& prompt){//like getInt but for doubles
    double input {};

    while (true){
        std::cout << prompt;
        std::cin >> input;
    
        if(std::cin.fail() || input < 0){
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

void checkBalance(const std::string& fileName){

}

void writeToFile(std::string& fileName, double balance){

}