/***************************************************
 Name: Joshua Carney
 Course: 362-f20
 Date: 9/15/2020
 Assignment: Statistician Redux
 Description: A driver class that utilizes the statiscian class
 
 ***************************************************/

// Include Directives
// **************************************************
#include <iostream>
#include <string>

#include "Statistician.h"

// Using Statements
// **************************************************
using std::cout;

// Main
// **************************************************

int main(int argc, char* argv[]) {
    int count;
    std::cout<<"Enter number of values ==> ";
	std::cin >> count;

    std::vector<float> result = populate(count);
    std::cout<< "\n";
    std::cout<< "The statistics of all " << count << " values are:" << std::endl;
    std::cout<< "  Sum: " << sumOfValues(result) << std::endl;
    std::cout<< "  Avg: " << average(result) << std::endl;
    std::cout<< "  Min: " << minimum(result) << std::endl;
    std::cout<< "  Max: " << maximum(result) << std::endl;

};


// Function Implementations
// **************************************************
