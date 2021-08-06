/*
  Filename   : HashTable.hpp
  Author     : Jingnan Xie
  Course     : CSCI 362
  Description: A simple separate chaining Hash Table
              we learned in class with hash function:
              f(key) = key mod 11

    Modified/Completed by Joshua Carney
*/
/*********************************************************
 *                 !! DRIVER OUTPUT:
 * 
 *  1 Banana
    1 Apple
    1 Cantalop
    1 Orange
    0 
    1 Pear
    1 Kiwi
    0
*/

/*********************************************************/
//macro guard
#ifndef hash_table_h
#define hash_table_h
/*********************************************************/
//System includes
#include<vector>
#include<list>
#include<string>

/*********************************************************/
//local includes



template<typename T>
class HashTable{

    //data memeber: bucket array (a list vector) 
    //Each list is a <int, T> pair list
    std::vector<std::list<std::pair<int, T>>> m_table;

public:

    //constructor
    HashTable() : m_table()
    {
      for(int i = 0; i < 11; ++i) {
          std::list<std::pair<int, T>> listPair;
          m_table.push_back(listPair);
      }
    }

    //Hash Function
    //Division Hashing mod k where k is a prime number close to the input size
    int hash_function(const int& key){
        return key % 11;
    }


    //insert <key, value> into the table
    //To D0: Fix it so when key exits, do nothing
    void insert(const int& key, const T& value){
        int index = hash_function(key);
        if(find(key).first) {
            return;
        }
        //use std::make_pair to make a pair
        m_table[index].push_back(std::make_pair(key, value));   
    }


    //erase the <key, value> with key = "key"
    //return true if "key" exists and the pair erased
    //return false if "key" does not exist
    bool erase(const int& key){
        int index = hash_function(key);
        auto iter = m_table[index].begin();
        while(iter != m_table[index].end()) {
            if((*iter).first == key) {
                m_table[index].erase(iter);
                return true;
            }
            ++iter;
        }
        return false;
    }


    //find the value with key = "key"
    //If "key" exists, return true and the value
    //else return false and a defaul (meaningless) value 
    std::pair<bool, T> find(const int& key){
        int index = hash_function(key);
        auto iter = m_table[index].begin();
        T value;
        while(iter != m_table[index].end()){
            //use pair.first to get the first element in the pair
            if((*iter).first == key){
                //use pair.second to get the second element in the pair
                value = (*iter).second;
                return std::make_pair(true, value);
            } 
            ++iter;
        }
        return std::make_pair(false, value);
    }
    

    //modify the value with key = "key"
    //If "key" exists, modify it's value to "value", and return true
    //else, return false
    bool modify(const int& key, const T& value){
        int index = hash_function(key);
        auto iter = m_table[index].begin();
        while(iter != m_table[index].end()) {
            if((*iter).first == key) {
                (*iter).second = value;
                return true;
            }
            ++iter;
        }
        return false;
    }

};
#endif