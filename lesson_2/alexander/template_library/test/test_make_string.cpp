#include "../src/make_string.h"

#include <iostream>

int main() {
    std::cout <<
                 ATL::make_string(std::vector<int>{3, 5, 7, 12414}) << std::endl <<
                 ATL::make_string("example_raw_string") << std::endl <<
                 ATL::make_string(std::vector({"first str", "second str"})) << std::endl <<
                 ATL::make_string("example of variadic usage: ",
                                  "(x,y) = (",3,",",4,"); ",
                                  "x,y,z = ", std::vector{5,5,4}) << std::endl;
                 ATL::make_string('$');

}
