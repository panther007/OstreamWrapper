#include "OstreamWrapper.hpp"
#include <iostream>



int
main() {

    cs540::OstreamWrapper os(std::cout);
    
    // Prints "1234".
    os << 1234 << std::endl;
    
    // Prints "123,456,789; 123456789".
    os << cs540::sep(',') << 123456789 << cs540::nosep << "; " << 123456789 << cs540::sep('\'') << std::endl;

    // The separator is "sticky".  Prints "123'456'789; 123456789".
    os << 123456789 << "; " << cs540::nosep << 123456789 << std::endl;
}
