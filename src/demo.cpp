#include "dftu.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {
    if ( argc != 2 )
    {
        std::cerr << "Usage: " << argv[0] << " <input>\n";

        return -1;
    }

    dftu::Reading reading;
    dftu::ParseResult result = dftu::parse(argv[1],&dftu::SI,&reading);
    std::cout << "Float: " << reading.value << std::endl;

    return 0;
}

