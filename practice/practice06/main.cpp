#include <iostream>//no ai used
#include "Person.h"
#include <string>

class SuperPerson : Person{
	int hp;
public:
	SuperPerson(std::string name, int age, int hp = 100) : Person(name, age) , hp{hp} {}//has to call derived class person

	void talk() {
		std::cout << "hi\n";
	}
};
int main() {
	Person p("bob", 3);
	Person j("jill");//works because default value in header
	//std::cout << p.age;//can't do. it's private

	std::cout << p.getAge() << '\n';

	p.setAge(5);
	
	p = j + p;

	std::cout << p.getAge() << '\n';
	std::cout << p.getName() << '\n';
	std::cout << p << '\n';
	
	SuperPerson sp("james", 5, 16);

	sp.talk();
	return 0;
}