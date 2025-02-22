//***************************************************************************
//
//  Trevor Janis
//  Z1839641
//  CSCI 340-1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************
#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H

//#warning These programs will not work properly until you have implemented the template functions in assign2-algos.h. Once you have, remove this #warning line from the file. In the beginning, there will likely be more warnings and errors after this because of the missing implementations.

#include <iomanip>
#include <iostream>
#include <string>
#include "assign2-algos.decl.h"

// Implement your algorithms for assignment 2 in this file.

/**
 * @brief Iterate over the range provided, add up the elements, and return the sum.
 * 
 * @tparam ITERATOR 
 * @param begin 
 * @param end 
 * @return int sum of elements
 */
template <typename ITERATOR>
int range_sum(ITERATOR begin, ITERATOR end) {
  int sum = 0; //initialize sum 0
  for (ITERATOR i = begin; i != end; i++) //loop through elements
  {
    sum += *i; //add elements
  }
  return sum; //return total
}

/**
 * @brief Iterate over the range provided, add up and count the elements, 
 * then calculate and return the average (mean) as a double.
 * 
 * @tparam ITERATOR 
 * @param begin 
 * @param end 
 * @return double average of elements
 */
template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
  int count = 0;  //initalize count 0
  double avg = 0; //initalize avg 0
  for (ITERATOR itr = begin; itr != end; itr++) //loop through elements
  {
    avg += *itr; //divisor
    count++;  //count of elements
  }
  return avg / count; //divide & return
}

/**
 * @brief Iterate over the range provided, keeping track of the maximum value found. 
 * Return that maximum value.
 * 
 * @tparam ITERATOR 
 * @param begin 
 * @param end 
 * @return auto maximum value of elements
 */
template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
  auto max = 0; //initalize max 0
  int val = 0; //initalize val 0

  for (ITERATOR itr = begin; itr != end; itr++){
    val = *itr; //set value
    if (max < val) //compare with max
    {
      max = val; //set val until max found
    }
    
  }
  return max;

}

/**
 * @brief @brief terate over the range provided, keeping track of the minimum value found.
 * Return that minimum value.
 * 
 * @tparam ITERATOR 
 * @param begin 
 * @param end 
 * @return auto minimum value of elements
 */
template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
  auto min = 0; //initialize variables with 0
  int val = 0;

  for (ITERATOR itr = begin; itr != end; itr++){ //loop thru elements
    val = *itr; //set value
    if (min > val)
    {
      min = val; //set value until max found
    }
    
  }
  return min;

}

/**
 * @brief Iterate over the range provided, counting the number of elements that 
 * occur within the range. Return that count.
 * 
 * @tparam ITERATOR 
 * @param begin 
 * @param end 
 * @return int count of elements
 */
template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
  int count = 0;  //initialize count at 0
  for (ITERATOR itr = begin; itr != end; itr++) //loop through elements
  {
    count++;  //increase count
  }
  return count;
}

/**
 * @brief This function should iterate over the range given, 
 * and print out the elements with the formatting determined by the other parameters.
 * 
 * @tparam ITERATOR 
 * @param ost std::ostream that the output should be printed to.
 * @param begin iterator to the beginning of the range to be printed
 * @param end iterator just past the last valid element of the range to be printed
 * @param pre string that gets printed one time before anything else
 * @param sep string that gets printed between each element
 * @param post string that gets printed after all of the elements have been printed
 * @param width width, in characters, of the column in which the elements' values are printed
 */
template <typename ITERATOR>
void print_range(std::ostream & ost, ITERATOR begin, ITERATOR end, const std::string &pre, const std::string &sep, const std::string &post, int width) {
  ost << pre; //initialize ostream with pre string once
  for (ITERATOR itr = begin; itr != end; itr++) //loop through elements
  {
    if (itr != begin){  //iterator not at begin
      ost << sep; //load seperator string
    }
    if (width == 0){  //if width zero
      ost << std::setw(0) << *itr;  //format
    } else {
      ost << *itr;  //load iterator element into ost
    }
  }
  ost << post; //final string print
}

/**
 * @brief tool used in statistics where data is subdivided into several sub-ranges, 
 * which we will refer to as bins, and the frequency of occurrence of values within 
 * each range is measured
 * 
 * @tparam ITERATOR 
 * @tparam RANDOM_ACCESS 
 * @param begin iterator at the beginning of the sequence we're computing a histogram for
 * @param end iterator one past the last element of the sequence we're computing a histogram for
 * @param nums an object supports the subscript [] operator to access integers containing the bin counts
 * @param N the total number of bins, and an upper bound on the indices used with nums
 * @param divisor divide the number by this and use the quotient to decide which bin this fits in.
 */
template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS & nums, int N, int divisor) {
  for (auto i = 0; i < N; i++) //initialize bins
  {
    nums[i] = 0; //set to zero
  }

  for (ITERATOR itr = begin; itr != end; itr++) //loop through elemenets
  {
    int q = *itr / divisor; //divide bins by divisor
    
    if (q >= 0) //if quotent less than zero 
    {
      ++nums[q]; //increment nums using q index
    } else if (q < N){ //or greater than N-1
      ++nums[q]; //increment nums using q index
    }
  }
}

/**
 * @brief Get the next token strict object
 * 
 * @tparam ITERATOR 
 * @tparam T 
 * @param begin Where to begin the search for a delimiter.
 * @param end The end of the range to search. If we reach this, there are no more elements to form tokens with.
 * @param delim the delimiter value, when it is found in the range, it is used to indicate that one token has ended
 * @return iter_token_info<ITERATOR> return tokens
 */
template <typename ITERATOR, typename T>
iter_token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
    iter_token_info<ITERATOR> token_info; //initialize token info struct
    token_info.b = begin; // initialize iterators for tokens
    token_info.e = begin;  
    token_info.n = begin;

    while (token_info.n != end) {  // loop through the inputs
        if (*token_info.n == delim) { //if delimiter
            token_info.e = token_info.n; //set current token
            ++token_info.n; //move iterator to next token
            break; //found token
        }
        ++token_info.e; //next character
        ++token_info.n; //next character
    }
    return token_info;
}

/**
 * @brief Get the next token strict object
 * 
 * @tparam ITERATOR 
 * @tparam T 
 * @param begin Where to begin the search for a delimiter.
 * @param end The end of the range to search. If we reach this, there are no more elements to form tokens with.
 * @param delim the delimiter value, when it is found in the range, it is used to indicate that one token has ended
 * @return iter_token_info<ITERATOR> return tokens
 */
template <typename ITERATOR, typename T>
iter_token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {
    iter_token_info<ITERATOR> token_info; //initialize token info struct
    token_info.b = begin; // initialize iterators for tokens
    token_info.e = begin;  
    token_info.n = begin;

    while (token_info.b != end &&*token_info.b == delim) { //skip delimiters
        ++token_info.b; //move iterator to next token
    }
    token_info.e = token_info.b; //initialize to begin
    token_info.n = token_info.b; //initialize to begin

    while (token_info.e != end) { //loop through elements
        if (*token_info.e == delim) { //if delimiter
            ++token_info.n; //move to next element
            break; //fund token
        }
        ++token_info.e; //move end iterator
        ++token_info.n; //move next iterator
    }

    return token_info; //return tokens
}

#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/
