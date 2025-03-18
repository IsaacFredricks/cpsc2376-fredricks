#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

/*
Ask the user to enter a list of space-separated numbers (e.g., 5 2 9 1 7).
Store the numbers in a std::vector<int>.
Use std::sort with a lambda function to implement the following custom sorting rule:
All odd numbers are considered larger than all even numbers.
Among odd numbers, sort in descending order.
Among even numbers, sort in descending order.*/

int main() {
	std::cout << "Enter a space separated list of numbers: ";
	std::string line{};

	std::getline(std::cin, line);
	std::vector<int> nums{};

	std::istringstream ssin(line);
	while (true) {
		//don't know how to stop while loopso psuedo code:
		//gets number from string
		//if it fails to get number, it exits the loop
		int num{};
		ssin >> num;

		//example code: if(ssin.fail()) break;
		nums.push_back(num);
	}

	std::cout << "input: ";
	std::for_each(nums.begin(), nums.end(), [](int n) {std::cout << n << ' ';});

	std::cout << '\n';

	std::sort(nums.begin(), nums.end(), [](int a, int b) {
		if (a % 2 == 0 && b % 2 == 0) {
			return a < b;
		}

		else if (a % 2 > 0 && b % 2 > 0) {
			return a > b;
		}

		else if (a % 2 > 0 && b % 2 == 0 && a > b || a < b) {
			return a > b;
		}

		else if (a % 2 == 0 && b % 2 > 0 && a > b || a < b) {
			return a < b;
		}

		});

	std::cout << "output: ";
	std::for_each(nums.begin(), nums.end(), [](int n) {std::cout << n << ' ';});

	std::cout << '\n';


	return 0;
}
