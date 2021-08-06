/*
    Filename: Vect.h
    Author: Joshua Carney
    Course: 362-f20
    Description: an integer vector class with random access and dynamic resizing
*/

/*********************************************/
//macro guard to prevent multiple inclusions//
#ifndef VECT_H
#define VECT_H
#include <algorithm>
#include <cstdlib>
#include <iterator>
/*********************************************/

class Vect {
    // Member variables
    private:
        int* vect; //array holding vector
        unsigned size; //size of current vector
        unsigned capacity; //max capacity of vector
    //std::vector<int>::iterator iter1 = v3.begin()
    public:
        using iterator = int*; //iterators are just integer pointers
        //const_iterators are read only iterators
        //std::vector<int>::const_iterator iter2 = v3.begin();
        //*iter2 = 15 is illegal, 
        using const_iterator = const int*;

        //constructors
        //default constructor
        // member initializer list
        Vect(): size(0), capacity(0), vect(nullptr) { //doing this is more efficient as opposed to the normal way, the compiler starts at a random number before the first line, then assigns our values otherwise

        }

        Vect(unsigned size): size(size), capacity(size), vect(new int[size]) {

        }

        Vect(unsigned size, const int& value): size(size), capacity(size), vect(new int[size]) {
            std::fill(begin(), end(), value);
        }

        //Destructor
        ~Vect() {
            //delete array vect
        }

        //size member functions
        unsigned sizeOfVect() const {
            return size;
        }

        bool empty() {
            return true;
        }

        unsigned vectCapacity() const {
            return capacity;
        }

        
        iterator begin() {
            return vect; //array name is a pointer to the first element
        }

        iterator end() {
            return vect + size;
        }

        const_iterator begin() const {
            return vect;
        }

        const_iterator end() const {
            return vect + size;
        }
};
#endif