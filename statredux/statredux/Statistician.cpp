/***************************************************
 Name: Joshua Carney
 Course: 362-f20
 Date: 9/15/2020
 Assignment: Statistician_Redux
 Description: Find various statistics about float vectors
 
 ***************************************************/
#include "Statistician.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

// Function Implementations
// **************************************************

// Finds the largest value in the passed vector
// Assumes nums is not empty
float maximum (const std::vector<float>& nums) {
	auto max = std::max_element(nums.begin(), nums.end());
	return *max;
}


// Finds the largest value in the passed vector
// Assumes nums is not empty
float minimum (const std::vector<float>& nums) {
	auto min = std::min_element(nums.begin(), nums.end());
	return *min;
}


// Finds the sum of values from the passed vector
// Should return zero if the vector is empty
float sumOfValues (const std::vector<float>& nums) {
	float sum = std::accumulate(nums.begin(), nums.end(), 0.0f);
	return sum;
}

// Finds the average of all values from the passed vector
// assumes nums is not empty
float average (const std::vector<float>& nums) {
	return sumOfValues(nums) / nums.size();
}

// Creates and returns a new vector. Reads in count number
// of values from the user by prompting for each one
// should return an empty vector if count <= 0
std::vector<float> populate (int count) {
	std::vector<float> result;

	float value;
	for(int i = 0; i < count; ++i) {
		std::cout<<"Enter value ==> ";
		std::cin>> value;
		result.push_back(value);
	}
	
	return result;
}
