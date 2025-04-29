#include <iostream>//not done
#include <memory>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

//base class
class Shape{
public:
    virtual double area() const = 0;//pure virtual function
    virtual ~Shape() = default;
};

//concrete classes
class Circle : public Shape{
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}
    double area() const override{
        return (3.14159 * pow(radius, 2.0));
    }
};

class Square : public Shape{
private:
    double length;
public:
    Square (double length) : length(length) {}
    double area() const override{
        return pow(length, 2.0);
    }
};

class Rectangle : public Shape{
private:
    double length;
    double width;
public:
    Rectangle (double length, double width) : length(length), width(width) {}
    double area() const override{
        return length * width;
    }
};

std::unique_ptr<Shape> createShape(const std::string& line){
    std::istringstream ssin(line);

    std::string type{};
    ssin >> type;

    if(type == "circle"){
        double radius {};
        ssin >> radius;
        return std::make_unique<Circle>(radius);

    }
    
    else if(type == "square"){
        double length{};
        ssin >> length;
        return std::make_unique<Square>(length);
    }

    else if(type == "rectangle"){
        double length{};
        ssin >> length;
        double width{};
        ssin >> width;
        return std::make_unique<Rectangle>(length, width);
    }

    else{
        return nullptr;
    }
}
int main(){
    std::vector<std::unique_ptr<Shape>> shapes {};
    std::ifstream fin("shapes.txt");

    if (!fin.is_open()) {
        std::cout << "error in opening file!\n";
        return 1;//early return. returning 1 usually indicates something went wrong
    }

    std::string line;
    while(getline(fin, line)){
        auto shape = createShape(line);

        shapes.push_back(std::move(shape));
    }

    double sum {};
    for(int i{0}; i < shapes.size(); i++){
        sum += shapes.at(i) -> area();
    }

    std::cout << "The sum of all of the shapes' areas is " << sum << '\n';

    return 0;
}