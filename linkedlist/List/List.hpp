/*
  Filename   : List.hpp
  Author(s)  : William Killian, Gary M. Zoppetti
  Course     : CSCI 362-01
  Assignment : List
  Description: List class, our implementation of a list ADT 
               with bidirectional access and dynamic resizing.
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef LIST_HPP_
#define LIST_HPP_

/************************************************************/
// System includes

// for initializer_list
#include <initializer_list>
// for ostream
#include <iostream>
// for bidirectional_iterator_tag, prev, next, distance
#include <iterator>
// for ptrdiff_t, size_t, swap
#include <utility>

#ifndef IS_ITERATOR
#define IS_ITERATOR(T) \
  typename = decltype (*std::declval<T&> (), void(), ++std::declval<T&> (), void())
#endif

/************************************************************/
// Forward declaration of types

template<typename T>
struct ListConstIterator;

template<typename T>
struct ListIterator;

template<typename T>
struct List;

/************************************************************/
// Forward declaration of global functions

template<typename T>
std::ostream&
operator<< (std::ostream&, const List<T>&);

template<typename T>
bool
operator== (const ListIterator<T>&, const ListIterator<T>&);

template<typename T>
bool
operator!= (const ListIterator<T>&, const ListIterator<T>&);

template<typename T>
bool
operator== (const ListConstIterator<T>&, const ListConstIterator<T>&);

template<typename T>
bool
operator!= (const ListConstIterator<T>&, const ListConstIterator<T>&);

/************************************************************/
// struct representing our ListNode
//
// contains three data members:
// - data
// - next
// - prev

template<typename T>
struct ListNode
{
  ListNode () : data ()
  {
  }

  ListNode (const T& v) : data (v)
  {
  }

  ListNode (const T& v, ListNode* n, ListNode* p) : data (v), next (n), prev (p)
  {
  }

  // unhooks the range [begin,end] from a linked list
  // NOTE: will lose reference to begin and end if you
  //   are not keeping track of it!
  //
  // - does not create any new nodes
  // - does not destroy any existing nodes
  // - begin is start of range to remove
  // - end is inclusive end of range to remove
  //
  // [5]
  static void unhook_range (ListNode* begin, ListNode* end) {
    //    +---+   +---+   +---+   +---+   +---+   +---+
    // <->| 1 |<->| 2 |<->| 3 |<->| 4 |<->| 5 |<->| 6 |<->
    //    +---+   +---+   +---+   +---+   +---+   +---+
    //              ^                       ^
    //            begin                    end
    //
    // becomes
    //
    //    +---+   +---+
    // <->| 1 |<->| 6 |<->
    //    +---+   +---+
    //
    // begin and end do not need to change at all
    begin->prev->next = end->next;
    end->next->prev = begin->prev;
  }

  // inserts the range [first,last] before this
  // NOTE: does not create any new nodes, does not destroy any existing nodes
  //
  // [5]
  void hook_range (ListNode* first, ListNode* last) {
    //            this
    //              v
    //    +---+   +---+          +---+   +---+   +---+
    // <->| 1 |<->| 6 |<->    <->| 2 |<->| 3 |<->| 4 |<->
    //    +---+   +---+          +---+   +---+   +---+
    //                             ^               ^
    //                           first           last
    //
    // becomes
    //                                    this
    //                                      v
    //    +---+   +---+   +---+   +---+   +---+
    // <->| 1 |<->>| 2 |<-| 3 |<->| 4 |<->| 6 |<->
    //    +---+   +---+   +---+   +---+   +---+
    //              ^               ^
    //            first           last
    //
    this->prev->next = first;
    first->prev = this->prev;
    this->prev = last;
    last->next = this;
  }

  // insert first before this
  void
  hook (ListNode* first)
  {
    hook_range (first, first);
  }

  // unhooks current node from linked list
  void
  unhook ()
  {
    ListNode::unhook_range (this, this);
  }

  T data;
  ListNode* next{nullptr};
  ListNode* prev{nullptr};
};

/************************************************************/
// Struct representing a List const_iterator
//
// contains a single data member:
// - m_nodePtr

template<typename T>
struct ListConstIterator
{
  using value_type = T;
  using pointer = const value_type*;
  using reference = const value_type&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  using Node = const ListNode<value_type>;

public:
  // construct from Node
  ListConstIterator (Node* n) : m_nodePtr (n)
  {
  }

  // construct from Iterator
  ListConstIterator (const ListIterator<T>& i) : m_nodePtr (i.m_nodePtr)
  {
  }

  // iterator dereference
  reference operator* () const
  {
    return m_nodePtr->data;
  }

  // iterator member access
  pointer operator-> () const
  {
    return &(m_nodePtr->data);
  }

  // pre-increment
  ListConstIterator&
  operator++ ()
  {
    m_nodePtr = m_nodePtr->next;
    return *this;
  }

  // post-increment
  // [2]
  ListConstIterator
  operator++ (int)
  {
    ListConstIterator copy (*this);
    m_nodePtr = m_nodePtr->next;
    return copy;
  }

  // pre-decrement
  // [2]
  ListConstIterator&
  operator-- ()
  {
    m_nodePtr = m_nodePtr->prev;
    return *this;
  }

  // post-decrement
  ListConstIterator
  operator-- (int)
  {
    ListConstIterator copy (*this);
    m_nodePtr = m_nodePtr->prev;
    return copy;
  }

  friend bool operator==
    <> (const ListConstIterator& i, const ListConstIterator& j);

  friend bool operator!=
    <> (const ListConstIterator& i, const ListConstIterator& j);

private:
  Node* m_nodePtr{nullptr};
  friend class List<T>;
  friend class ListIterator<T>;
};

template<typename T>
bool
operator== (const ListConstIterator<T>& i, const ListConstIterator<T>& j)
{
  return i.m_nodePtr == j.m_nodePtr;
}

// compares the underlying pointers for equality
// [2]
template<typename T>
bool
operator!= (const ListConstIterator<T>& i, const ListConstIterator<T>& j)
{
  return i.m_nodePtr != j.m_nodePtr;
}

/************************************************************/
// Struct representing a List iterator
//
// contains a single data member:
// - m_nodePtr

template<typename T>
struct ListIterator
{
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  using Node = ListNode<value_type>;

public:
  // construct from Node
  ListIterator (Node* n) : m_nodePtr (n)
  {
  }

  reference operator* () const
  {
    return m_nodePtr->data;
  }

  pointer operator-> () const
  {
    return &(m_nodePtr->data);
  }

  // advances to the "next" pointer, returns reference to self
  // [2]
  ListIterator&
  operator++ ()
  {
    m_nodePtr = m_nodePtr->next;
    return *this;
  }

  // advances to the "next" pointer, returns copy of self prior to advancement
  ListIterator
  operator++ (int)
  {
    ListIterator copy (*this);
    m_nodePtr = m_nodePtr->next;
    return copy;
  }

  // advances to the "prev" pointer, returns reference to self
  ListIterator&
  operator-- ()
  {
    m_nodePtr = m_nodePtr->prev;
    return *this;
  }

  // advances to the "prev" pointer, returns copy of self prior to advancement
  // [2]
  ListIterator
  operator-- (int)
  {
    ListIterator copy (*this);
    m_nodePtr = m_nodePtr->prev;
    return copy;
  }

  friend bool operator==<> (const ListIterator& i, const ListIterator& j);
  friend bool operator!=<> (const ListIterator& i, const ListIterator& j);

private:
  Node* m_nodePtr{nullptr};
  friend class List<T>;
  friend class ListConstIterator<T>;
};

// compares the underlying pointers for equality
// [2]
template<typename T>
bool
operator== (const ListIterator<T>& i, const ListIterator<T>& j)
{
  return i.m_nodePtr == j.m_nodePtr;
}

template<typename T>
bool
operator!= (const ListIterator<T>& i, const ListIterator<T>& j)
{
  return i.m_nodePtr != j.m_nodePtr;
}

/************************************************************/
// Class representing a List
//
// contains two data members:
// - m_header
// - m_size

template<typename T>
class List
{
  using Node = ListNode<T>;

public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

public: /* should be private, but public for testing */
  // transfers [first, last) to before pos and sets all links
  // [4]
  static void transfer (iterator pos, iterator first, iterator last)
  {
    if(first != last) {
      auto lastToBeUnhooked = last.m_nodePtr->prev;
      Node::unhook_range(first.m_nodePtr, lastToBeUnhooked);
      pos.m_nodePtr->hook_range(first.m_nodePtr, lastToBeUnhooked);
    }
  }

public:
  // default constructor
  // [5]
  List () : m_header (), m_size (0)
  {
    m_header.next = &m_header;
    m_header.prev = &m_header;
  }

  // size-value constructor
  // [5]
  explicit List (size_type count, const value_type& value = T ()) : List () {
    for(size_type i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  // range constructor
  // [5]
  template<typename InputIt, IS_ITERATOR (InputIt)>
  List (InputIt first, InputIt last) : List ()
  {
    auto counter = first;
    while(counter != last) {
      push_back(*counter);
      ++counter;  
    }
  }

  // copy constructor
  List (const List& other) : List (other.begin (), other.end ())
  {
    // NOTE: depends on range-constructor working
  }

  // intializer_list constructor
  List (std::initializer_list<T> init) : List (init.begin (), init.end ())
  {
    // NOTE: depends on range-constructor working
  }

  // destructor
  // [5]
  ~List () {
    clear();
  }

  // copy assignment
  // [5]
  List& operator= (const List& other) {
    if(&other != this) {
     clear();
     auto start = other.begin();
     while (start != other.end()) {
       push_back(*start);
       ++start;
     }
    }
    return *this;
  }

  // returns an iterator to the first element in the list
  // [1]
  iterator begin () noexcept
  {
    return {m_header.next};
  }

  // [1]
  const_iterator begin () const noexcept
  {
    return {m_header.next};
  }

  const_iterator cbegin () const noexcept
  {
    return begin ();
  }

  // returns an iterator to one-past-the-last element in the list (the "dummy" header)
  // [1]
  iterator end () noexcept
  {
    return {&m_header};
  }

  // [1]
  const_iterator end () const noexcept
  {
    return {&m_header};
  }

  const_iterator cend () const noexcept
  {
    return end ();
  }

  bool empty () const noexcept
  {
    return m_size == 0;
  }

  size_type size () const noexcept
  {
    return m_size;
  }

  // inserts "value" before "pos" -- returns iterator pointing to newly inserted element
  // [4]
  iterator insert (iterator pos, const value_type& value) {
    auto n = new Node(value);
    pos.m_nodePtr->hook(n);
    ++m_size;
    return --pos;
  }

  // inserts an element at the end of the list
  // [2]
  void push_back (const value_type& value) {
    insert(end(),value);
  }

  // inserts an element at the front of the list
  // [2]
  void push_front (const value_type& value) {
    insert(begin(),value);
  }

  // return a reference to the first element in the list
  // [1]
  reference front () {
    return *begin();
  }

  // return a reference to the first element in the list
  // [1]
  const_reference front () const {
    return *begin();
  }

  // return a reference to the last element in the list
  // [1]
  reference back () {
    return *(--end());
  }

  // return a reference to the last element in the list
  // [1]
  const_reference back () const {
    return *(--end());
  }

  // erase element pointed to by "pos" -- returns iterator to next element
  // [4]
  iterator erase (iterator pos) {
    Node n = *pos.m_nodePtr;
    ++pos;
    n.unhook();
    --m_size;
    return pos;
  }

  // erase elements in the range [first, last) -- returns an iterator that points to the same element as "last"
  // [5]
  iterator erase (iterator first, iterator last) {
   while(first != last) {
     first = erase(first);
   }
   return last;
  }

  // removes all elements from the list
  // [5]
  void clear () {
    erase(begin(), end());  
  }

  // removes the last element of the linked list
  // [2]
  void pop_back () {
    erase(--end());
  }

  // removes the first element of the linked list
  // [2]
  void pop_front () {
    erase(begin());
  }

  // resize the list to contain count elements, using "value" if count > size()
  // [5]
  void resize (size_type count, const value_type& value = value_type ()) {
    // if count > size(), then add new elements with push_back()
    // if count < size(), then remove elements from the end
    // DONT USE IF STATEMENT HE WILL NOT LIKE THAT
    while(count > size()) {
      push_back(value);
    }
    while(count < size()) {
      pop_back();
    }

  }

  /*
    swap: 
  */
  void swap (List& other)
  {
    using std::swap;
    // swap pointers
    swap (m_header.prev, other.m_header.prev);
    swap (m_header.next, other.m_header.next);
    // fix links that should now point to m_header
    m_header.next->prev = &m_header;
    m_header.prev->next = &m_header;
    // fix links that should now point to other.m_header
    other.m_header.next->prev = &other.m_header;
    other.m_header.prev->next = &other.m_header;
    // finally, swap sizes
    swap (m_size, other.m_size);
  }

  // Reverses the elements of the list without invalidating/changing any iterators/values
  // [+5 extra credit]
  
  void reverse ()
  {
    
    // Hint: fixup all next/prev links
    // you can use std::swap(listnode*1, listnode*2)
    List<T> reversedList;
    iterator start = begin();
    while(start != end()){
      reversedList.push_front(*start);
      ++start;
    }
    swap(reversedList);
  }
  

  void
  splice (iterator pos, List& other, iterator first, iterator last)
  {
    if (&other != this)
    {
      size_type const dist = std::distance (first, last);
      other.m_size -= dist;
      m_size += dist;
    }
    List::transfer (pos, first, last);
  }

  void
  splice (iterator pos, List& other, iterator it)
  {
    splice (pos, other, it, std::next (it));
  }

  void
  splice (iterator pos, List& other)
  {
    splice (pos, other, other.begin (), other.end ());
  }

public: /* should be private, but public for testing */
  Node m_header;
  size_type m_size;

  friend std::ostream& operator<<<> (std::ostream& output, const List& a);
};

// Output operator.
// Allows us to do "cout << a;", where "a" is a List.
// DO NOT MODIFY!
template<typename T>
std::ostream&
operator<< (std::ostream& output, const List<T>& a)
{
  output << "[ ";
  // This for-each loop will employ iterators.
  for (const auto& elem : a)
  {
    output << elem << " ";
  }
  output << "]";

  return output;
}

#endif
