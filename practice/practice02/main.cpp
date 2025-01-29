#include <iostream>//no ai used
#include <fstream>//for file input/output
#include <limits>//for getInt

int getInt(const std::string& prompt);//forward declarations
double getDouble(const std::string& prompt);
bool writeToFile(const std::string& fileName, double balance);
bool checkBalance(const std::string& fileName);


int main(){
    //insert code here
    std::string fileName{"account_balance.txt"};
    double balance{};//if the txt file can't be read, set the balance to $100.00

    std::ifstream inF(fileName);

    if(!inF.good()){//checks if file exists. want it to be different text from check balance and writeToFile
        balance = 100.00;

        writeToFile(fileName, balance);
        std::cout << "File doesn't exist. Making a new one and setting the initial balance to $" << balance << '\n';
        inF.close();
    }

    else{
        inF >> balance;
        inF.close();
        std::cout << "The file exists. The balance is: $" << balance << '\n';
    }
    


    while(true){//menu
        std::cout << "\n======Menu======\n1. Check Balance\n2. Deposit Money\n3. Withdraw money\n4. Exit\n";
        int choice {getInt("Enter a number 1-4 (inclusive): ")};

        if(choice == 1){
            std::cout << "You chose to check balance\n";

            checkBalance(fileName);

            if(!checkBalance(fileName)){
                std::cout << "Critical error. Shutting down\n";
                return 1;//throws an error
            }
        }

        else if(choice == 2){
            std::cout << "You chose to deposit money\n";

            double deposit {getDouble("Enter an ammount to deposit: $")};

            balance += deposit;

            writeToFile(fileName, balance);//updates balance

            if(!writeToFile(fileName, balance)){
                std::cout << "Critical error. Shutting down\n";
                return 1;//throws an error
            }
        }   

        else if(choice == 3){
            std::cout << "You chose to withdraw money\n";

            double withdraw {getDouble("Enter an ammount to withdraw: $")};


            if(withdraw > balance){
                std::cout << "You don't have enough money for that!\n";
            }
            
            else{
                balance -= withdraw;
            }


            writeToFile(fileName, balance); 

            if(!writeToFile(fileName, balance)){
                std::cout << "Critical error. Shutting down\n";
                return 1;//throws an error
            }
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

bool writeToFile(const std::string& fileName, double balance){
    std::ofstream outF(fileName);//opens file

    if(!outF.is_open()){
        std::cout << "Failed to open file for reading.\n";
        return false;
    }

    else{
        outF << balance;//overwrites the first line of account_balance.txt
        outF.close();//makes sure that file is saved

    }
    
    return true;
}

bool checkBalance(const std::string& fileName){
    std::ifstream inF(fileName);
    std::string line {};

    if(!inF.is_open()){
        std::cout << "Failed to open file for reading.\n";
        return false;
    }

    else{
        while(inF >> line){
            std::cout << "Account balance: $" << line << '\n';
        }

        inF.close();
    }

    return true;
}

