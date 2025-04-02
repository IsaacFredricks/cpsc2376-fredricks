#include <iostream>
#include <memory>//for unique ptrs
#include <vector>
#include <fstream>//for reading files
#include <cmath>//for pow()
#include <sstream>
#include <string>

//base class
class Shape {
public:
    virtual double getArea() const = 0;//pure virtual function
};

//derived classes:
class Rectangle : Shape {
private:
    double w;
    double l;

public:
    //need to call shape constructor to access get area
    Rectangle(double w, double l) : Shape(), w{ w }, l{ l } {
        std::cout << "rectangle constructed\n";
    }

    ~Rectangle() {
        std::cout << "dectangle destructed\n";
    }

    double getArea() const override {
        return w * l;
    }

};

class Circle : Shape {
private:
    double r;

public:
    //need to call shape constructor to access get area
    Circle(double r) : Shape(), r{ r } {
        std::cout << "circle constructed\n";
    }

    ~Circle() {
        std::cout << "circle destructed\n";
    }//destructor

    double getArea() const override {
        return pow(r, 2.0) * 3.14159;//M_PI didn't work for me
    }

};



/*void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (std::unique_ptr<Shape> shape : shapes) {
        std::cout << shape->getArea();
    }
}*/

int main()
{
    /*
    Rectangle rect{4, 5};

     std::cout << rect.getArea() << '\n';

     Circle c{ 4 };

     std::cout << c.getArea() << '\n';
    */


    /*
    * get ifstream to open file
    * read line by line and push back each shape into the vector
    * deletes all pointers when done
    */
    std::vector<std::unique_ptr<Shape>> shapes{};

    std::string fileName{ "shapes.txt" };

    std::ifstream fin{ fileName };

    if (!fin.is_open()) {
        std::cout << "error in opening file!\n";
        return 1;//early return. returning 1 usually indicates something went wrong
    }

    std::string line{};
    while (fin >> line) {//keeps going until empty line
        //from problem 4 of midterm solutions
        std::stringstream ssin(line);

        std::string type{};

        ssin >> type;

        if (type == "rectangle") {
            //std::cout << "its a rectangle\n";
            
        }

        else if (type == "circle") {
            //std::cout << "its a circle\n";
            
        }

    }
    return 0;
}