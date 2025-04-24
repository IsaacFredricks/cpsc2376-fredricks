/* Strategy Pattern — Text Filter (strategy/)
Prompt the user to enter a sentence.
Offer multiple text filter strategies: reverse, uppercase, remove vowels, or censor bad words.
Let the user select a strategy and apply it to the input.
Allow the user to switch strategies and reprocess the input without restarting the program*/
#include <iostream>
#include <memory>
#include <string>
#include <limits>

//interface class
class Print{
public:
    virtual void print(const std::string& prompt) = 0;
    virtual ~Print() = default;
};

class NormalPrint : public Print{
    void print(const std::string& prompt) override{
        std::cout << prompt << '\n';
    }
};

class ReversePrint : public Print{
    void print(const std::string& prompt) override{
        for(int i {prompt.length() - 1}; i >= 0; i--){
            std::cout << prompt.at(i);
        }
        std::cout << '\n';
    }
};

class BoldPrint : public Print{
    void print(const std::string& prompt) override{
        for(int i{0}; i < prompt.length(); i++){
            char c {prompt.at(i)};
            c = std::towupper(c);//converts it to uppercase letter
            std::cout << c;
        }
        std::cout << '\n';
    }
};

class SpacedPrint : public Print{
    void print(const std::string& prompt) override{
        for(int i{0}; i < prompt.length(); i++){
            char c {prompt.at(i)};
            if(c != ' '){
                std::cout << c << ' ';
            }
        }
        std::cout << '\n';
    }
};

class NoVowelPrint : public Print{
    void print(const std::string& prompt) override{
        for(int i{0}; i < prompt.length(); i++){
            char c {prompt.at(i)};
            if(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y'){
                std::cout << c;
            }
        }
        std::cout << '\n';
    }
};


//class that stores print class. based off of tutorial 14
class Agent{
    std::unique_ptr<Print> statement;
public:
    void setPrint(std::unique_ptr<Print> p){
        statement = std::move(p);
    }

    void act(const std::string& prompt){
        if(statement) statement->print(prompt);
    }
};

//forward declaration:
int getInt(const std::string& prompt);

int main(){
    //test code
    /*Agent a;
    a.setPrint(std::make_unique<ReversePrint>());
    a.act("testing");
    a.setPrint(std::make_unique<BoldPrint>());
    a.act("testing");
    a.setPrint(std::make_unique<SpacedPrint>());
    a.act("testing");
    a.setPrint(std::make_unique<NoVowelPrint>());
    a.act("testing");*/
    std::cout << "Strategy Pattern\n";
    std::cout << "Enter a sentence: ";
    std::string prompt {};
    getline(std::cin, prompt);
    Agent a;

    while(true){
        //menu
        std::cout << "1.Normal Print\n2.Reverse Print\n3.Bold Print\n4.Spaced Print\n5.No Vowel Print\n6.Exit\n";
        int choice {getInt("Enter a number between 1-6 to choose how you want to print the sentence: ")};

        std::cout << '\n';

        if(choice == 1){
            a.setPrint(std::make_unique<NormalPrint>());
            a.act(prompt);
        }

        else if(choice == 2){
            a.setPrint(std::make_unique<ReversePrint>());
            a.act(prompt);
        }

        else if(choice == 3){
            a.setPrint(std::make_unique<BoldPrint>());
            a.act(prompt);
        }

        else if(choice == 4){
            a.setPrint(std::make_unique<SpacedPrint>());
            a.act(prompt);
        }

        else if(choice == 5){
            a.setPrint(std::make_unique<NoVowelPrint>());
            a.act(prompt);
        }

        else if(choice == 6){
            std::cout << "Goodbye\n";
            break;
        }

        std::cout << '\n';
    }

}


//for menu
int getInt(const std::string& prompt) {

    int input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || input < 1 || input > 6) {
            //peek looks at next character in queue
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