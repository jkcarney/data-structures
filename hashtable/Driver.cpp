#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "HashTable.hpp"


int main(){
    HashTable<std::string> t1;
    t1.insert(5, "Apple");
    t1.insert(16, "Banana");
    t1.insert(20, "Cherry");
    std::cout<<t1.find(16).first<<" "<<t1.find(16).second<<std::endl;
    t1.erase(16);
    t1.insert(12, "Orange");
    t1.modify(20, "Cantalop");
    t1.insert(25, "Pear");
    t1.insert(23, "Peach");
    t1.insert(34, "Lemon");
    std::cout<<t1.find(5).first<<" "<<t1.find(5).second<<std::endl;
    std::cout<<t1.find(20).first<<" "<<t1.find(20).second<<std::endl;
    std::cout<<t1.find(12).first<<" "<<t1.find(12).second<<std::endl;
    std::cout<<t1.find(15).first<<" "<<t1.find(15).second<<std::endl;
    std::cout<<t1.find(25).first<<" "<<t1.find(25).second<<std::endl;
    t1.modify(23, "Kiwi");
    std::cout<<t1.find(23).first<<" "<<t1.find(23).second<<std::endl;
    t1.erase(25);
    std::cout<<t1.find(25).first<<" "<<t1.find(25).second<<std::endl;

}