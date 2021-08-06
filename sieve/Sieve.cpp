
#include <set>
#include <string>
#include <vector>
#include "Timer.hpp"
#include <math.h>
#include <iostream>

using std::set;
using std::string;
using std::vector;


// This function accepts two sets, A and B, and returns a new set that only
// has values that are only seen in one set, and not duplicates. For example
// 
// Set A:        [ 2 3 4 5 6 7 8 9 10]
// Set B:        [     4   6   8 9 10]
// 
// Returned Set: [ 2 3 5 7 ]
set<unsigned> 
uniqueSetItems(set<unsigned> setA, set<unsigned> setB) {
    auto setAIter = setA.begin();
    set<unsigned> returnedSet;
    while(setAIter != setA.end()) {
        // If we don't find the value of the iterator in setB, then add it to a new set
        if(setB.find(*setAIter) == setB.end()) {
            returnedSet.insert(*setAIter);
        }
        ++setAIter;
    }
    return returnedSet;
};

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
set<unsigned>
sieveSet (unsigned N) {
    set<unsigned> primes;
    for (unsigned i = 2; i <= N; ++i){
        primes.insert(i);
    }

    unsigned incr;

    // Start the number at two
    for(unsigned number = 2; number < N; number++){
        // Set the increment amount to the current number
        incr = number;
        while(incr < N) {
            // Increment by the number 
            incr += number;
            if(incr <= N) {
                auto p = primes.find(incr);
                if(p != primes.end()) {
                    primes.erase(p);
                }
            }
        }
    }
    return primes;
};

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
set<unsigned>
sieveVector (unsigned N) {
    //Fill vector with N "TRUE"s
    vector<bool> primeSet (N + 1, true);
    primeSet[0] = false;
    primeSet[1] = false;

    //Setting up the iterator to run while it's less than sqrt(N)
    for(unsigned incr = 2; incr <= sqrt(N); ++incr){
        auto iter = primeSet.begin() + incr;
        while(iter != primeSet.end()){
            // Increment the iterator based on the number we're at (2,3...)
            for(unsigned i = 1; i <= incr; ++i){
                ++iter;
                //Protect against seg fault
                if(iter == primeSet.end()) {
                    break;
                }
            }
            // If the bool value at the iter is true, then we "cross it out" (set it to false)
            if(*iter) {
                *iter = false;
            }
        }
    }

    set<unsigned> allPrimes;
    for(unsigned i = 2; i <= primeSet.size(); ++i) {
        // If the value at [i] is true, that means i is a prime
        if(primeSet[i]) {
            allPrimes.insert(i);
        }
    }
    return allPrimes;
};

int main (int argc, char* argv[]) {
    std::string version{argv[1]};
    unsigned int number = std::stoul (std::string{argv[2]});
    auto sieveVersion = (version == "set" ? &sieveSet : &sieveVector);
    Timer<> t;
    set<unsigned> answer = sieveVersion (number);
    t.stop();
    std::cout << "Pi[" << number << "] = " << answer.size() << " (using a " << version << ")" << std::endl;
    std::cout << "Time: " << t.getElapsedMs() << " ms"<<std::endl;
}
/*
N       10,000,000    20,000,000   40,000,000
=============================================
set        124104       300425      658236
vector     318835       903598      65275e6

Even though my set ended up being faster, I think that is only due to the fact that the
algorithm I wrote for vector was very poorly performing, not properly utilizing bracket 
notation within vectors. 

In my vector class, I create one vector with N elements and another with the amount of primes.
The time is takes to iterate through those entirely and either insert into the allPrimes set
or iterate through the vector ended up being very costly. It properly executes at a 
complexity of around O(n^2).

In my set class however I just increment a number and rely on the find() function, which
runs in log(n) time. Using many of these find functions is likely the reason that the function
takes so long to run, since find has to run for each N. So the complexity would likely be
O(nlogn), which explains why it runs much faster than the vector version.
*/