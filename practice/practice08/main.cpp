#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>

class Shape {//interface class. only virtual functions
public:
    virtual double area() = 0;

    static Shape* build(std::string s);
};

class Circle : public Shape{

private:
    double r;

public:
    Circle(double r) : r{ r } {}

    double area() override{//only override things you want to be polymorphic
        return 3.14159 * r * r;//M_PI didn't work for me
    }

    static Shape* build(std::string s) {
        std::istringstream ssin(s);
        std::string type;
        ssin >> type;
        assert(type == "CIRCLE");
        std::cout << "building circle\n";
        double r;
        ssin >> r;
        return new Circle(r);
    }
};

class Rectangle : public Shape {
private:
    double w;
    double h;

public:
    Rectangle(double w, double h) : w{ w }, h { h } {}

    double area() override {//only override things you want to be polymorphic
        return w * h;//M_PI didn't work for me
    }

    static Shape* build(std::string s) {
        std::istringstream ssin(s);
        std::string type;
        ssin >> type;
        assert(type == "RECTANGLE");
        std::cout << "building circle\n";
        double w;
        ssin >> w;

        double h;
        ssin >> h;
        return new Circle(w);
    }
};

class Square : public Shape {
private:
    double l;

public:
    Square(double l) : l{ l } {}

    double area() override {//only override things you want to be polymorphic
        return l * l;//M_PI didn't work for me
    }

    static Shape* build(std::string s) {
        std::istringstream ssin(s);
        std::string type;
        ssin >> type;
        assert(type == "SQUARE");
        std::cout << "building circle\n";
        double l;
        ssin >> l;
        return new Square(l);
    }
};

Shape* Shape::build(std::string s) {
    //map with shapetypes as key and factor functions as values
    if (s.at(0) == 'R') return Rectangle::build(s);
    else if (s.at(0) == 'S') return Square::build(s);
    else if (s.at(0) == 'C') return Circle::build(s);
    else return nullptr;

    return nullptr;
}

int main()
{
    /*
    Circle c(5);//can't make derived class without defining base class virtual functions
    std::cout << c.area() << '\n';

    Square s(5);

    Rectangle r(5, 6);
    std::cout << s.area() << '\n';
    std::cout << r.area() << '\n';
    */

    //avoid pass by value with base-derive objects. does obj slicing

    std::vector<Shape*> shapes;//use pointers instead

    std::ifstream fin("shapes.txt");//reading file
    

    while (true) {
        std::string line;

        std::getline(fin, line);

        if (line == "") break; 

        std::cout << line << '\n';

        shapes.push_back(Shape::build(line));
    }

    double area{ 0 };

    for (auto* s : shapes) {
        area += s->area();
    }

    std::cout << "total area is " << area << '\n';
    std::cout << "vector size is " << shapes.size() << '\n';
    return 0;
}

