#include <iostream>
#include <limits>
#include <string>
#include <list>

int getOption(const std::string& prompt);
int getIndex(const std::string& prompt, const std::list<std::string>& taskList);

int main(){
    std::list<std::string> taskList {};

    while(true){
        std::cout << "1. Add Task\n2. Remove Task\n3. Show Tasks\n4. Exit\n";
        int choice {getOption("Choice: ")};

        if(choice == 1){
            std::cout << "Enter task: ";
            std::string task {};

            getline(std::cin, task);

            if(task.size() == 0){
                std::cout << "There is nothing on this task\n";
            }

            else{
                taskList.push_back(task);

                std::cout << "Task added!\n";
            }
        }

        else if(choice == 2){//source: https://www.geeksforgeeks.org/how-to-get-element-at-specific-position-in-list-in-c/

            if(taskList.size() == 0){
                std::cout << "There's no tasks on the list!\n";
            }

            else{
                int index {getIndex("Enter task number to remove: ", taskList) - 1};

                std::list<std::string>::iterator iter = taskList.begin();
                advance(iter, index);//moves index
                std::string removed {*iter};//dereferences removed

                taskList.remove(removed);
            }
            
        }

        else if(choice == 3){

            if(taskList.size() == 0){
                std::cout << "There are no tasks!\n";
            }

            else{
                std::cout << "Tasks:\n";

                int counter {1};
                for(std::string task : taskList){
                std::cout << counter << ". " << task << '\n';
                counter++;
            }
            }
        }

        else if(choice == 4){
            
            std::cout << "Goodbye\n";
            break;
        }

        else{
            std::cout << "How did you even get here? Invalid input. Try again.\n";
        }

        std::cout << '\n';
    }
    
    return 0;
}

int getOption(const std::string& prompt){

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < 1 || input > 4 || std::cin.peek() != '\n') {//peek looks at next character in queue
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

int getIndex(const std::string& prompt, const std::list<std::string>& taskList){

    int input{};

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < 0 || input > taskList.size() - 1 || std::cin.peek() != '\n') {//peek looks at next character in queue
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
