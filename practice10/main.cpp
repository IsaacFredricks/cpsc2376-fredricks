#include <iostream>//chat gpt used. prompts and answers below code
#include <memory>//for unique ptrs
#include <vector>
#include <fstream>//for reading files
#include <cmath>//for pow()
#include <sstream>
#include <string>

//base class
class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;//pure virtual function
};

//derived classes:
class Rectangle : public Shape {//i forgot to add public here that was leading to the errors
private:
    double w;
    double l;

public:
    //need to call shape constructor to access get area
    Rectangle(double w, double l) : Shape(), w{ w }, l{ l } {
        //std::cout << "rectangle constructed with w: " << w << " and l: " << l << '\n';
    }

    ~Rectangle() override{
        //std::cout << "rectangle destructed\n";
    }

    double getArea() const override {
        return w * l;
    }


};

class Circle : public Shape {
private:
    double r;

public:
    //need to call shape constructor to access get area
    Circle(double r) : Shape(), r{ r } {
        //std::cout << "circle constructed with r: " << r << '\n';
    }

    ~Circle() override{
        //std::cout << "circle destructed\n";
    }//destructor

    double getArea() const override {
        return pow(r, 2.0) * 3.14159;//M_PI didn't work for me
    }

};



void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (int i{ 0 }; i < shapes.size(); i++) {
        std::cout << "Area: " << shapes.at(i)->getArea() << '\n';
    }
}

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

    while (true) {
        std::string line{};
        std::getline(fin, line);

        if (line == "") {//keeps going until empty line
            break;
        }
        //from problem 4 of midterm solutions
        std::istringstream ssin(line);//some help from here: https://stackoverflow.com/questions/62441883/using-stringstream-to-read-integers-and-add-them-up

        std::string type{};

        ssin >> type;
        //std::cout << "type: " << type << '\n';

        if (type == "rectangle") {
            //std::cout << "its a rectangle\n";
            
            int w{};

            ssin >> w;

            //std::cout << "w: " << w << '\n';

            int l{};

            ssin >> l;

            //std::cout << "l: " << l << '\n';

            std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(w, l);

            shapes.push_back(std::move(rect));
        }

        else if (type == "circle") {
            //std::cout << "its a circle\n";
            
            int r{};
            
            ssin >> r;

            //std::cout << "r: " << r << '\n';

            std::unique_ptr<Circle> circ = std::make_unique<Circle>(r);

            shapes.push_back(std::move(circ));
        }

    }

    printAllAreas(shapes);

    return 0;
}

/*
Chatgpt prompts:

*prompt: When I try to push back a unique pointers of a derived class into a vector of base class unique pointers, it says that there is no overloaded function to do so. Can you explain why this is not the case in bullet points? Here is the code: *insert code*

*responce: Sure! I'll walk you through why this issue happens when trying to push a std::unique_ptr of a derived class into a std::vector of std::unique_ptr to the base class. Here are the key points that explain the behavior:

std::unique_ptr is not copyable:

std::unique_ptr is designed to prevent ownership from being copied. It can only be moved.

When you try to push a derived std::unique_ptr into a vector of base class std::unique_ptrs, this requires a move, not a copy.

Type mismatch:

A std::unique_ptr<Derived> is not implicitly convertible to a std::unique_ptr<Base>. Even though Derived is a subclass of Base, the ownership semantics of unique_ptr are strict. This prevents implicit conversion between the two.

Move semantics and ownership:

std::unique_ptr requires that the move constructor or move assignment operator be called when transferring ownership. The compiler needs to understand how to "move" the std::unique_ptr<Derived> into the std::unique_ptr<Base>, but it can't do this implicitly without an appropriate overload.

Explicit std::move() required:

You need to explicitly call std::move() on the derived class pointer when inserting it into the vector, since std::move() is the way to enable the move semantics for std::unique_ptr.

Vector needs to be able to move the elements:

The vector's push_back() function is designed to move its argument into the container. In the case of unique pointers, this means you must move the derived class pointer into the vector of base class pointers.

*prompt: Here is what I typed out. It still says the same error: no instance of overloaded function "std::vector<_Ty, _Alloc>::push_back [with _Ty=std::unique_ptr<Shape, std::default_delete<Shape>>, _Alloc=std::allocator<std::unique_ptr<Shape, std::default_delete<Shape>>>]" matches the argument list. Can you explain this error to me?


* responce: The issue in your code is that you're trying to push a std::unique_ptr<Rectangle> and a std::unique_ptr<Circle> into a std::vector<std::unique_ptr<Shape>>. While Rectangle and Circle are derived classes of Shape, std::unique_ptr<Derived> is not implicitly convertible to std::unique_ptr<Base> due to the strict ownership rules of std::unique_ptr. You need to use std::move() to explicitly transfer ownership of the std::unique_ptr when adding it to the vector.

* prompt: I used std::move when pushing back to the vector, but it still shows the same error? Is there something wrong that I did with my class *inserts code here*

*responce : Possible Reasons for the Error:

Missing public Inheritance:

Your Rectangle and Circle classes are not publicly inheriting from Shape. In C++, the default inheritance is private, meaning the base class's methods (like getArea()) would not be accessible from derived class objects unless explicitly declared public.

Fix: Change the inheritance in the Rectangle and Circle classes to public:

cpp
Copy
class Rectangle : public Shape {  // Use 'public' inheritance
Incorrect Class Definitions:

Ensure that the Rectangle and Circle classes are actually correctly inheriting from Shape and are not just standalone classes. This can lead to confusion when Shape methods like getArea() are not available or can't be overridden.

Fix: Ensure that both Rectangle and Circle classes inherit from Shape as follows:

cpp
Copy
class Rectangle : public Shape {  // This is crucial
Class Constructors and Destructor:

If the constructor and destructor for your derived classes (Rectangle and Circle) are not properly defined or if the destructor of Shape is not virtual, it can cause issues with memory management and object cleanup. Make sure that the Shape class has a virtual destructor.

Fix: Add a virtual destructor to the Shape class:

cpp
Copy
virtual ~Shape() = default;  // Virtual destructor in base class
std::move on std::unique_ptr:

The usage of std::move() on the std::unique_ptr objects (rect and circ) is correct. However, if the type of the std::vector does not match the type of the elements being pushed, this will result in an error. Double-check that the vector is declared with std::unique_ptr<Shape> as the element type.

Fix: Ensure the vector declaration is correct:

cpp
Copy
std::vector<std::unique_ptr<Shape>> shapes{};
Inconsistent Function or Compiler Issues:

Occasionally, compiler errors may be caused by small inconsistencies, missing includes, or issues with the build environment. Clean your project and rebuild it to ensure the compiler is picking up all the correct header files and object files.

Summary of Fixes:
Ensure the inheritance is public in both Rectangle and Circle.

Make sure Shape has a virtual destructor to allow proper cleanup.

Ensure the vector is of type std::vector<std::unique_ptr<Shape>>.

The std::move() is correct, but you need to ensure everything is set up properly with inheritance and destructors.
*/