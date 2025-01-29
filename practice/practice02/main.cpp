#include <iostream>//no ai used
#include <fstream>//for file input/output
#include <limits>//for getInt


int getInt(const std::string& prompt);//forward declarations
double getDouble(const std::string& prompt);
void writeToFile(const std::string& fileName, double balance);
void readFile(const std::string& fileName, double& balance);
void checkBalance(const std::string& fileName);

int main(){
    //insert code here
    std::string fileName("account_balance.txt");
    double balance{};//if the txt file can't be read, set the balance to $100.00
    readFile(fileName, balance);//checks if the file is there at startup


    while(true){
        std::cout << "\n======Menu======\n1. Check Balance\n2. Deposit Money\n3. Withdraw money\n4. Exit\n";
        int choice {getInt("Enter a number 1-4 (inclusive): ")};

        if(choice == 1){
            std::cout << "You chose to check balance\n";

            checkBalance(fileName);
        }

        else if(choice == 2){
            std::cout << "You chose to deposit money\n";

            double deposit {getDouble("Enter an ammount to deposit: $")};

            balance += deposit;

            writeToFile(fileName, balance);//updates balance
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

void writeToFile(const std::string& fileName, double balance){
    std::ofstream outf(fileName);//opens file

    outf << balance;//overwrites the first line of account_balance.txt
    outf.close();//makes sure that file is saved

}

void readFile(const std::string& fileName, double& balance){
    std::ifstream inF(fileName);
    
    if(!inF.is_open()){//if writing to a file that doesn't exist, it will make a new one
        inF.close();//very important! can't read and write to files at once
        balance = 100.00;

        writeToFile(fileName, balance);
        std::cout << "Failed to open file. Setting balance to $" << balance << '\n';
    }

    else{
        inF >> balance;//gets balance amount from file
        std::cout << "Initial balance is: $" << balance << '\n';
    }
}


void checkBalance(const std::string& fileName){
    std::ifstream inF(fileName);
    std::string line {};

    if(!inF.is_open()){
        std::cout << "Failed to open file for reading.\n";
    }

    else{
        while(inF >> line){
            std::cout << "Account balance: $" << line << '\n';
        }
    }
}

