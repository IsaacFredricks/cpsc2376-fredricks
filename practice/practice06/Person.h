#pragma once
#include <string>
#include <iostream>

class Person {
	int age;
	std::string name;

public:
	Person(std::string name, int age=1);

	int getAge() const;

	void setAge(int age);

	std::string getName() const;

	//operator overload
	friend Person operator+(Person& p1, Person& p2);//not technically in the class, but can access class instance variables
	friend std::ostream& operator<<(std::ostream& os, Person& p2);//not technically in the class, but can access class instance variables
};
