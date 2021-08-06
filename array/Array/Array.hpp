/*
  Filename   : Array.hpp
  Author     : Joshua Carney
  Course     : CSCI 362
  Assignment : N/A
  Description: Array class, our implementation of a list ADT 
                 with random access and dynamic resizing.

		 With templated class we often include the
		 implementation of the class in the header
		 file. In these cases we use the extension
		 ".hpp". 
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef ARRAY_H
#define ARRAY_H

/************************************************************/
// System includes

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations

// YOU DO NOT NECESSARILY NEED TO USE ALL OF THESE!
using std::copy;
using std::copy_backward;
using std::distance;
using std::fill;
using std::ostream;
using std::ptrdiff_t;

/************************************************************/

template<typename T>
class Array
{
public:
  //*****************************************************
  // DO NOT MODIFY THIS SECTION!
  // Some standard Container type aliases
  using value_type = T;
  // Iterators are just pointers to objects of type T
  using iterator = value_type*;
  using const_iterator = const value_type*;

  using reference = value_type&;
  using const_reference = const value_type&;

  using size_type = size_t;
  using difference_type = ptrdiff_t;
  //*****************************************************

  // Default ctor.
  // Initialize an empty Array.
  // This method is complete, and does NOT need modification.
  // Remember to use a _member initialization list_ for each ctor,
  //   like I have below for the default ctor.
  Array ()
    : m_size (0),
      m_capacity (0),
      m_array (nullptr)
  {
  }
  
  // Size ctor.
  // Initialize an Array of size "pSize", with each element
  //   set to "value".
  explicit Array (size_t pSize, const T& value = T ())
    : m_size (pSize),
      m_capacity (pSize),
      m_array (new T[m_capacity])
  {
    fill (begin (), end (), value);
  }

  // Range ctor.
  // Initialize an Array from the range [first, last).
  // "first" and "last" must be Array iterators or pointers
  //   into a primitive array.
  Array (const_iterator first, const_iterator last)
  : m_size(std::distance(first, last)),
    m_capacity(std::distance(first, last)),
    m_array (new T[m_capacity])
  {
    std::copy(first, last, begin());
  }

  // Copy ctor.
  // Initialize this object from "a".
  Array (const Array& a)
  : m_size(a.size()),
    m_capacity(a.capacity()),
    m_array(new T[a.capacity()])
  {
    std::copy(a.begin(), a.end(), begin());
  }

  // Destructor.
  // Release allocated memory.
  ~Array () {
    delete[] m_array;
  }

  // Assignment operator.
  // Assign "a" to this object.
  //   Be careful to check for self-assignment.
  Array& operator= (const Array& a) {
    if(&a != this) {
      reserve(a.capacity());
      std::copy(a.begin(), a.end(), begin());
      m_size = a.size();
    }
    return *this;
  }

  // Return the size.
  size_t size () const {
    return m_size;
  }

  // Return true if this Array is empty, false o/w.
  bool empty () const {
      return size() == 0;
  }

  // Return the capacity.
  size_t capacity () const {
      return m_capacity;
  }

  // Return the element at position "index".
  T& operator[] (size_t index) {
      return m_array[index];
  }

  const T& operator[] (size_t index) const {
      return m_array[index];
  }

  // Insert an element at the back.
  void push_back (const T& item) {
    if(capacity() == 0){
      reserve(1);
    }
    else if(capacity() == size()) {
        reserve(capacity() * 2);
    }
    *end() = item;
    ++m_size;
  }

  // Erase the element at the back.
  void pop_back () {
    if(size() != 0){
      --m_size;
    }
  }

  // Reserve capacity for "space" elements.
  // "space" must be  greater than capacity.
  //   If not, leave the capacity unchanged.
  // "size" must remain unchanged.
  void reserve (size_t space)
  {
    if (space > capacity ())
    {
      T* array = new T[space];
      copy (begin (), end (), array);
      delete[] m_array;
      m_array = array;
      m_capacity = space;
    }
  }

  // Change the size to be "newSize".
  // If "newSize" is less than "size",
  //   erase the last elements.
  // If "newSize" is more than "size",
  //   insert "value"-s at the end.
  void resize (size_t newSize, const T& value = T ()) {
    if(newSize > size()) {
      reserve(newSize);
      std::fill(end(), (end() + (newSize - size())), value);
    }
    m_size = newSize;
  }
  

  // Insert "item" before "pos", and return iterator pointing to "item".
  // If the capacity is insufficient, DOUBLE it.
  //   If the capacity is 0, increase it to 1.
  // NOTE: If a reallocation occurs, "pos" will be invalidated!
  iterator insert (iterator pos, const T& item) {
    if(capacity() == size()) {
      auto index = distance(begin(), pos);
      reserve(capacity() * 2 + 1);
      pos = begin() + index;
    }

    std::copy_backward(pos, end(), end()+ 1);
    *pos = item;
    ++m_size;

    return pos;
  }

  // Remove element at "pos", and return an iterator
  //   referencing the next element.
  iterator erase (iterator pos) {
    std::copy(pos + 1, end(), pos);
    --m_size;
    return pos;
  }

  // Return iterator pointing to the first element.
  iterator begin () {
    return m_array;
  }

  const_iterator begin () const {
    return m_array;
  }

  // Return iterator pointing one beyond the last element.
  iterator end () {
      return m_array + m_size;
  }

  const_iterator end () const {
      return m_array + m_size;
  }

  // Return a pointer to the underlying dynamic array
  T* data () {
    return m_array;
  }

  // Return a pointer to the underlying dynamic array
  T const* data () const {
    return m_array;
  }

private:
  // Stores the number of elements in the Array.
  size_t m_size;
  // Stores the capacity of the Array, which must be at least "m_size".
  size_t m_capacity;
  // Stores a pointer to the first element in the Array.
  T* m_array;
};

/************************************************************************/
// Free functions associated with the class

// Output operator.
// Allows us to do "cout << a;", where "a" is an Array.
// DO NOT MODIFY!
template<typename T>
ostream&
operator<< (ostream& output, const Array<T>& a)
{
  output << "[ ";
  // This for-each loop will employ iterators.
  for (const auto& elem : a)
    output << elem << " ";

  output << "]";

  return output;
}

#endif

/************************************************************************/
