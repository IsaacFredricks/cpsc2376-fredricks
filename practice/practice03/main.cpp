
#include <iostream>
#include "mathyStuff.h"

int main()
{
    std::cout << add(2, 3);
    std::cout << double(5);
    Rectangle r{ 3, 4 };

    std::cout << r.area();

    return 0;
}
