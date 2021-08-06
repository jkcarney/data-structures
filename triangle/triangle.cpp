/*  Name: Joshua Carney
    Course: 362-2
    Description: A program to the test the triangle header
*/
#include "triangle.h"
#include<iostream>

int main() {

    float triangle::perimeter() const{
        return m_side1 + m_side2 + m_side3;
    }
    triangle t1(3,4,5);
    triangle t2;

    std::cout<<"Is t1 a right triangle? " <<t1.is_right()<<std::endl;
    std::cout<<"Is t2 a right triangle? " <<t2.is_right()<<std::endl;
    std::cout<<"t1's perimeter is "<<t1.perimeter()<<std::endl;
    std::cout<<"t2's perimeter is "<<t2.perimeter()<<std::endl;
}