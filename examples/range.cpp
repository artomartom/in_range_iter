#include <range.hpp>
#include <iostream>


using namespace ranges;

int main()
{
     

    for (auto i :in_range(0, 10 ))
        std::cout << i << "\n";
 

     

    return 0;
}

//#endif // RANGE_HPP