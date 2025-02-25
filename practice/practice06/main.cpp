#include <iostream>//no ai used
#include "Person.h"

int main() {
	Person p;
	//std::cout << p.age;//can't do. it's private

	std::cout << p.getAge() << '\n';

	p.setAge(5);

	std::cout << p.getAge() << '\n';
	return 0;
}