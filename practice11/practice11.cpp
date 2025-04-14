#include <iostream>
#include <memory>

class Car {
private:
    std::unique_ptr<std::string> name;//just a dumb example. don't actually do this with just strings

public:
    Car(const std::string& name) : name{ std::make_unique<std::string>(name) } {};

    //copy constructor. doesn't change original car
    Car(const Car& c) : name{ std::make_unique<std::string>(*(c.name)) } {
        std::cout << "copy constructor called!\n";
    }

    //move constructor. passes rref of car
    Car(Car&& c) : name{ std::move(c.name)} {//don't make Car&& c  a const value
        std::cout << "move constructor called!\n";
    }

    //destructor
    ~Car() {
        std::cout << "destructor called\n";
    }

    //copy assignment
    Car& operator=(const Car& c) {
        *name = *(c.name);
        std::cout << "copy assignment called\n";

        return *this;
    }

    //move assignment
    Car& operator=(const Car&& c) {//passes r value of car
        std::move(c.name);//original car name is now null ptr
        std::cout << "move assignment called\n";

        return *this;
    }

    void setName(const std::string& name) {
        *(this->name) = name;
    }

    friend std::ostream& operator<<(std::ostream& os, Car& c) {
        os << "Car (name= " << *(c.name) << ")\n";

        return os;
    }
};

int main(){

    Car c("mildred");

    Car d(c);//calls copy constructor
    std::cout << c << '\n';

    d.setName("gildred");
    std::cout << d << '\n';

    Car e(std::move(d));//calls move constructor. passes r values. d not valid anymore

    d = c; //copy assignment
    
    std::cout << d << '\n';

    d = Car("fred"); //move assignment

    std::cout << d << '\n';
    return 0;
}

