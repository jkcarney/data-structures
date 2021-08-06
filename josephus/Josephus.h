#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include <list>

/* Simulate the Josephus problem modeled as a std::list.
 * This function will modify the passed list with only a
 * single survivor remaining.
 *
 * @param circle -- the linked list of people
 * @param k -- skip amount. NOTE: k > 0
 *
 * @return a list of those who are executed in chronological order
 */
template <typename T>
std::list<T>
execute (std::list<T>& circle, int k);

/* entry point to the Josephus problem from the autograder
 *
 * @param N -- number of people in the circle
 * @param k -- skip amount. NOTE: k > 0
 */
int
josephus (int N, int k);

#endif