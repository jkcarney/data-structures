#include <iostream>
#include <string>

#include "Josephus.h"


int main(int argc, char* argv[]) {

    int n = 31;
    int k = 13;

    int survivor = josephus(n, k);
    std::cout << "And the survivor is " << survivor << std::endl;
    return 0;
};

