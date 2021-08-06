/*
  Filename   : Josephus.cpp
  Author     : Joshua Carney
  Course     : CSCI 362
  Assignment : Josephus Lab
  Description: Solving the Josephus problem with a list
*/

#include "Josephus.h"
#include <list>
#include <iostream>

    /* Simulate the Josephus problem modeled as a std::list.
    * This function will modify the passed list with only a
    * single survivor remaining.
    *
    * @param circle -- the linked list of people
    * @param k -- skip amount. NOTE: k > 0
    *
    * @return a list of those who are executed in chronological order
    */

   /*
        From my observation, the complexity of the algorithm in 
        relation to N and k is that the amount of links traversed
        is roughly equal to T(N * (k - 1)). The reason there may
        be any discrepancy between that number and the amount of 
        links travsersed could be attributed to cases where the 
        begin() == end(), and we must add another link traverseral.

   */
    template <typename T> std::list<T> execute (std::list<T>& circle, int k){
        //LINKS TRAVSERED:
        int linksTraversed = 0;

        if(circle.size() <= 1)
            return circle;

        int changingK;
        std::list<T> executedCircle;
        auto iter = circle.begin();

        while(circle.size() != 1) {
            for(changingK = k; changingK > 1; --changingK) {
                iter++;
                ++linksTraversed;
                if(iter == circle.end()) {
                    iter = circle.begin();
                    ++linksTraversed;
                }
            }
            executedCircle.push_back(*iter);
            iter = circle.erase(iter);
            if(iter == circle.end()) {
                iter = circle.begin();
                ++linksTraversed;
            }
        }
        return executedCircle;
    }

    /* entry point to the Josephus problem from the autograder
    *
    * @param N -- number of people in the circle
    * @param k -- skip amount. NOTE: k > 0
    */
    int josephus (int n, int k){
        std::list<int> circle;
        for(int i = 1; i <= n; ++i){
            circle.push_back(i);
        };
        std::list<int> executedCircle = execute(circle, k);
        return circle.front();
    };
