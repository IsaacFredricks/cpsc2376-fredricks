#include "Person.h"

class Person {
	int age{};

public:
	int Person::getAge() {
		return age;
	};

	void Person::setAge(int age) {
		this->age = age;
	}
};