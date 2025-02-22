#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>

/**
 * @brief Construct a new simple linked list <T>::simple linked list object
 * Initializes the list to a working state, then iterates over the range provided, 
 * adding each element to the linked list in order. 
 * 
 * @tparam T 
 * @tparam ITERATOR 
 * @param beg beginning of range
 * @param end end of range
 */
template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {
  head = nullptr; //initalize list
  tail = nullptr;
  for (ITERATOR itr = beg; itr != end; itr++) //iterate through
  {
    push_back(*itr); //insert elements
  }
  
}

/**
 * @brief This method should return true if, and only if, 
 * there are no nodes in the linked list.
 * 
 * @tparam T 
 * @return true no nodes in list
 * @return false nodes present in list
 */
template <typename T>
bool simple_linked_list<T>::empty() const {
  if (head == nullptr && tail == nullptr) //if no nodes in list
  {
    return 1; //true
  } else {
    return 0; //false
  }
}

/**
 * @brief This method should return a simple_linked_iterator that points to the head node.
 * 
 * @tparam T 
 * @return simple_linked_iterator <T> iterator that points to head
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {
  return simple_linked_iterator<T>(head); //iterator for head
}

/**
 * @brief This method should return a simple_linked_iterator that would 
 * compare == an iterator that is off the end of the list.
 * 
 * @tparam T 
 * @return simple_linked_iterator <T> iterator that points to null terminator after end
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
  return simple_linked_iterator<T>(nullptr); //iterator after tail
}

/**
 * @brief This should return a reference to the data member of the head node.
 * 
 * @tparam T 
 * @return T& reference to data in head
 */
template <typename T>
T & simple_linked_list<T>::front() {
  return head->data; //data contained in head
}

/**
 * @brief This should return a reference to the data member of the tail node.
 * 
 * @tparam T 
 * @return T& reference of tail data
 */
template <typename T>
T & simple_linked_list<T>::back() {
  return tail->data;  //data contained in tail
}

/**
 * @brief Modify the linked list to remove the last node.
 * 
 * @tparam T 
 */
template <typename T>
void simple_linked_list<T>::pop_back() {
  if (head == tail) //if final node
  {
    delete head; //reset linked list
    head = nullptr;
    tail = nullptr;
  } else {
    linked_node<T>* node = head; //temporary node
    while (node->next != tail)  //set to next & not equal to tail
    {
    node = node->next;  //set node to next
    }
  delete tail; //delete tail node
  tail = node; //set to temp(next)
  tail->next = nullptr; //reset tail
  }
}

/**
 * @brief Add a new node containing the provided value to the end of the linked list.
 * 
 * @tparam T 
 * @param x node element to be inserted
 */
template <typename T>
void simple_linked_list<T>::push_back(const T & x) {
  linked_node<T>* node = new linked_node<T>(x); //new node to be inserted
  if (!head)  //if first node
  {
    head = node; //set to new node
    tail = node; //set to new node
  } else {
    tail->next = node; //set tail for linkage
    tail = node; //link tail
  }
}

/**
 * @brief Destroy the simple linked list<T>::simple linked list object
 * 
 * @tparam T 
 */
template <typename T>
simple_linked_list<T>::~simple_linked_list() {
  clear(); //deletes all nodes & resets object
}

/**
 * @brief Returns how many elements are currently in the linked list.
 * 
 * @tparam T 
 * @return size_t number of elemetns
 */
template <class T>
size_t simple_linked_list<T>::size() const {
  size_t cnt = 0; //begin count for size
  linked_node<T>* node = head; //temporary node set to beginning for iteration
  while (node) //iterate based on current location
  {
    cnt++;  //increase count
    node = node->next; //link next node to continue iteration
  }
  return cnt; //return number of elements
}

/**
 * @brief Remove all of the nodes from the linked list to reset it to an empty state.
 * 
 * @tparam T 
 */
template <typename T>
void simple_linked_list<T>::clear() {
  while (!empty()) //while not empty
  {
    pop_back(); //delete last element
  }
}

// IMPLEMENTATIONS FOR ITERATOR

/**
 * @brief This returns true if and only if both simple_linked_iterators (*this and the parameter) are pointing to the same node.
 * 
 * @tparam T 
 * @param other 
 * @return true equal
 * @return false not equal
 */
template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T> & other) const {
  if (pos == other.pos) //compare
  {
    return 1; //equal
  } else {
    return 0; //not equal
  }
  
}

/**
 * @brief Called when you increment your iterator with ++ before the name, i.e. ++i. 
 * This changes the current iterator so it points to the next node, and returns a reference to the current iterator, 
 * which will be at the new position.
 * 
 * @tparam T 
 * @return simple_linked_iterator <T>& reference to current iterator
 */
template <typename T>
simple_linked_iterator <T> & simple_linked_iterator <T>::operator ++ () { // preincrement
  if (pos == *this) //compare position with current iterator
  {
    pos = pos->next; //increment
  }
  return *this; //return new position
}

/**
 * @brief Called when you increment your iterator with ++ after the variable name, i.e. i++. 
 * This also changes the current iterator so it points to the next node, 
 * but it returns another iterator that points to the original node position.
 * 
 * @tparam T 
 * @return simple_linked_iterator <T> iterator that points to origin location
 */
template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
  simple_linked_iterator<T> node = *this; //temporary node to save location
  ++(*this);  //increase current location
  return node; //return original location
}
    
/**
 * @brief This should return a reference to the data member of the linked_node that the current iterator points to
 * 
 * @tparam T 
 * @return T& data in current position
 */
template <typename T>
T & simple_linked_iterator<T>::operator * () { // dereference operator
  return pos->data;
}

#endif

