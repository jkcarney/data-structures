#include<iostream>

int main(){
    const int x;
    const int y = 10;
    int z = 20, k = 30;
    y = 10;
    y = 15;
    const int* ptr1 = &z;
    *ptr1 = 15;
    ptr1 = &k;
    int* const ptr2 = &z;
    *ptr2 = 15;
    ptr2 = &k;
}