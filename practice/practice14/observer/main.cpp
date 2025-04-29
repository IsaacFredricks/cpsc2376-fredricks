//ignore. will fix later
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class GradeBook;//subject class

class Observer{
public:
    virtual void update(GradeBook& grades) = 0;
    virtual ~Observer() = default;
};

class GradeBook{
    std::vector<std::weak_ptr<Observer>> observers;
    std::vector<double> grades;
    double average = 0;
public:
    void attachObserver(const std::shared_ptr<Observer>& obs){
        observers.push_back(obs);
    }

    void addGrade(double grade){
        grades.push_back(grade);
        getAverage();
        notify();
    }

    void setGrade(double grade, int index){
        grades.at(index) = grade;
        notify();
    }

    int getAverage() {
        double total {};
        for(double grade : grades){
            total += grade;
        }

        average = total / grades.size();
        //notify();
        return average;
    }

private:
    void notify() {//from class lecture
    // Remove expired observers while notifying active ones
    observers.erase(
        std::remove_if(observers.begin(), observers.end(),
            [this](std::weak_ptr<Observer>& wp) {
                if (auto sp = wp.lock()) {
                    sp->update(*this);
                    return false;
                }
                return true;
            }),
        observers.end());
}

};

//derived observer classes
class Averager : public Observer{
public:
    void update(GradeBook& gradebook) override{
        std::cout << "The average grade is now: " << gradebook.getAverage() << "%\n";
    }
};

class Notifier : public Observer{
public:
    void update(GradeBook& gradebook) override{
        if(gradebook.getAverage() < 60){
            std::cout << "Grade below 60%. Email sent to totallyRealStudent@email.com\n";
        }
    }
};

int getInt(const std::string& prompt) {

    int input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n') {
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

double getDouble(const std::string& prompt) {

    double input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || input < 0) {
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

int main(){
    GradeBook gradebook {};
    auto avg = std::make_shared<Averager>();
    gradebook.attachObserver(avg);

    auto notice = std::make_shared<Notifier>();
    gradebook.attachObserver(notice);

    while(true){
        std::cout << "1.Add grade\n2.update specific grade\n3.Exit\n";
        int choice{getInt("enter 1-3 to make a choice: ")};
    
        if(choice == 1){
            double grade{getDouble("enter the grade: ")};
            gradebook.addGrade(grade);
        }

        else if(choice == 2){
            int index{getInt("enter the index: ")};
            double grade{getDouble("enter the new grade: ")};
            gradebook.setGrade(grade, index);
        }

        else if(choice == 3){
            std::cout << "goodbye\n";
            break;
        }

        else{
            std::cout << "invalid input. try again\n";
        }

    }
    
    return 0;
}

/*
chat gpt prompt: int main(){
    GradeBook gradebook {};
    Averager avg {};
    gradebook.attachObserver(std::make_shared<Averager>(avg));

    Notifier notice {};
    gradebook.attachObserver(std::make_shared<Notifier>(notice));

    gradebook.addGrade(50);

    std::cout << gradebook.getAverage() << '\n';
}

can you explain why the observer classes aren't updating when I set the grade? Explain in bullet points

responce:

Certainly! Here's why the observer classes aren't updating when you call setGrade():

✅ Observer Pattern is implemented correctly overall – the GradeBook stores weak pointers to Observer instances and notifies them via notify() when a grade changes.

❌ Observers are not being properly tracked – in main(), you're creating temporary Averager and Notifier objects on the stack and then wrapping copies of them in shared_ptr via std::make_shared<Averager>(avg).

avg and notice are local stack objects.

std::make_shared<Averager>(avg) creates a copy of each observer.

Once the original avg and notice go out of scope, their lifetimes end.

The shared_ptr copy is not held anywhere else except weakly (via weak_ptr), so it is immediately destroyed.

The weak_ptrs in GradeBook::observers expire instantly.

❗ Expired weak_ptrs mean notify() skips them – the notify() function skips any expired weak_ptr and removes them during std::remove_if.

✅ Fix:
Use std::shared_ptr to create the observers, and pass those into attachObserver() so they stay alive:

cpp
Copy
Edit
int main(){
    GradeBook gradebook {};

    auto avg = std::make_shared<Averager>();
    gradebook.attachObserver(avg);

    auto notice = std::make_shared<Notifier>();
    gradebook.attachObserver(notice);

    gradebook.addGrade(50);
    gradebook.setGrade(70, 0); // This will now trigger updates

    return 0;
}
*/