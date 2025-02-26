#include "Person.h"
#include <string>


Person::Person(std::string name, int age) : name{ name }, age{ age } {}

int Person::getAge() const{
	return age;
}

void Person::setAge(int age) {
	this->age = age;
}

std::string Person::getName() const{
	return name;
}

Person operator+(Person& p1, Person& p2) {
	return Person(p1.getName() + p2.getName(), p1.getAge() + p2.getAge());
}

std::ostream& operator<<(std::ostream& os, Person& p) {
	os << "person " << p.getName() << " age: " << p.getAge() << "\n";
	return os;
}