#include <iostream>//no ai used
#include <vector>
#include <fstream>//for file i/o

class Employee{//base class. has virtual function so can't instantiate
private:
    std::string name;
    int id;

public:
    Employee(std::string name, int id) : name{name}, id{id} {}

    //pure virtual function
    virtual double calculateSalary() const = 0;

    virtual void displayInfo() const;

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
        //std::cout << name << 
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
    
};

int main(){
    std::cout << "Hello World!\n";

    return 0;
}
