#include <iostream>
#include <vector>
#include <algorithm>


int main() {
	std::vector<int> nums{55, -1000, 12, 32, 59, 18};

	auto maxElem { std::max_element(nums.begin(), nums.end()) };//returns an iterator to max elem

	std::cout << "Max element: " << *maxElem << '\n';//derefernces iterator

	auto minElem { std::min_element(nums.begin(), nums.end()) };//returns an iterator to min elem

	std::cout << "Min element: " << *minElem << '\n';

	return 0;
}