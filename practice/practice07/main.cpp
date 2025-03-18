#include <iostream>//no ai used
#include <vector>
#include <fstream>//for file i/o
#include <sstream>//from last weeks lecture
#include <string>

class Employee{//base class. has virtual function so can't instantiate
private:
    std::string name;
    int id;

public:
    Employee(std::string name, int id) : name{name}, id{id} {}

    virtual ~Employee() = default;//virtual destructor. helps prevent memory leaks

    //pure virtual function
    virtual double calculateSalary() const = 0;

    virtual void displayInfo() const;

    std::string& getName(){
        return name;
    }

    int getId() const{
        return id;
    }    

    static Employee* build(std::string& s);//from last week's lecture

};

class SalariedEmployee : public Employee{//derived class
private:
    double monthlySalary;

public:
    SalariedEmployee(std::string name, int id, double monthlySalary) : Employee{name, id}, monthlySalary{monthlySalary} {}
    double calculateSalary() const{
        return monthlySalary;
    }

    void displayInfo(){
        std::cout << "ID: " << getId() << ", Name: " << getName() << ", Type: Salaried, Monthly Salary: " << calculateSalary() << '\n';
    }

    static Employee* build(std::string s) {//based off of last week's lecture
        std::istringstream ssin(s);
        std::string name;
        ssin >> name;
        int id;
        ssin >> id;
        double monthlySalary;
        ssin >> monthlySalary;
        return new SalariedEmployee(name, id, monthlySalary);
    }

};

class HourlyEmployee : public Employee{//derived class
private:
    double hourlyRate;
    int hoursWorked;
    
public:
    HourlyEmployee(std::string name, int id, double hourlyRate, int hoursWorked) 
    : Employee{name, id}, hourlyRate{hourlyRate}, hoursWorked{hoursWorked} {}

    double calculateSalary() const{
        return hourlyRate * hoursWorked;
    }

    void displayInfo(){
        std::cout << "ID: " << getId() << ", Name: " << getName() << ", Type: Hourly Salary, Hourly Rate: " << hourlyRate
        << ", Hours Worked: " << hoursWorked << ", Salary: " << calculateSalary() << '\n';
    }

    static Employee* build(std::string s) {
        std::istringstream ssin(s);
        std::string name;
        ssin >> name;
        int id;
        ssin >> id;
        double hourlyRate;
        ssin >> hourlyRate;
        int hoursWorked;
        ssin >> hoursWorked;
        return new HourlyEmployee(name, id, hourlyRate, hoursWorked);
    }

    
};

class CommissionedEmployee : public Employee{//derived class
private:
    double baseSalary;
    double salesAmount;
    double commissionRate;
    
public:
    CommissionedEmployee(std::string name, int id, double baseSalary, double salesAmount, double commissionRate) 
    : Employee{name, id}, baseSalary{baseSalary}, salesAmount{salesAmount}, commissionRate{commissionRate} {}

    double calculateSalary() const{
        return baseSalary + (salesAmount * commissionRate);
    }

    void displayInfo(){
        std::cout << "ID: " << getId() << ", Name: " << getName() << ", Type: Hourly Salary, Base Salary: " << baseSalary
        << ", Sales Amount: " << salesAmount << ", Commission Rate" << commissionRate << ", Salary: " << calculateSalary() << '\n';
    }

    static Employee* build(std::string s) {
        std::istringstream ssin(s);
        std::string name;
        ssin >> name;
        int id;
        ssin >> id;
        double baseSalary;
        ssin >> baseSalary;
        double salesAmount;
        ssin >> salesAmount;
        double commissionRate;
        ssin >> commissionRate;
        return new CommissionedEmployee(name, id, baseSalary, salesAmount, commissionRate);
    }
    
};

Employee* Employee::build(std::string& s) {//based off of last week's lecture
    //map with shapetypes as key and factor functions as values
    if (s.at(0) == 'S') return SalariedEmployee::build(s);
    else if (s.at(0) == 'H') return HourlyEmployee::build(s);
    else if (s.at(0) == 'C') return CommissionedEmployee::build(s);
    else return nullptr;

    return nullptr;
}

int main(){

    std::vector<Employee*> employees;//use pointers to avoid obj slicing

    std::ifstream fin("employees.txt");//opens file for reading

    if(!fin.is_open()){
        std::cout << "File not opened correctly or not found\n";
        return 1;
    }

    else{
        while(true){
            std::string line{};
            std::getline(fin, line);

            if(line == ""){
                break;
            }

            employees.push_back(Employee::build(line));
        }

        for(auto* employee : employees){
            employee->displayInfo();
        }

        for(auto* employee : employees){
            delete employee;//prevents memory leaks
        }
    }

    return 0;
}
