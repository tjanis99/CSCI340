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
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include <vector>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief If the coordinates fit within the boundaries of the grid, they will return true, otherwise false.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param x coordinate
 * @param y coordinate
 * @return true fits in boundaries
 * @return false doesn't fit in boundaries
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
  if ((x < _width) && (y < _height)){ //test size against height & width
    return true;  //fits
  } else {
    return false; //doesn't fit
  }
}

/**
 * @brief If the coordinates fit within the boundaries of the grid, they will return true, otherwise false.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row //coordinate
 * @param col //coordinate
 * @return true fits
 * @return false doesn't fit
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
  return (row < _height) && (col < _width); //return boundry check
}

/**
 * @brief This method should return true if, and only if, there are no elements present in the grid.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return true empty
 * @return false not empty
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
  if (_height == 0 && _width == 0) //check if empty
  {
    return 1; //empty
  } else {
    return 0; //not empty
  }
}

/**
 * @brief Get rid of all of the data that was being stored, and change the stored height and width accordingly.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
  data.clear(); //clear container
  _width = 0; //reset bounds
  _height = 0;
}

/**
 * @brief (x=0,y=0) is the top left element, and (x=width-1, y=height-1) is the bottom right.  
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param x coordinate
 * @param y coordinate
 * @return T&  location in the grid corresponding to the coordinates provided.
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
  return data[y * _width + x]; //return index
}

/**
 * @brief (x=0,y=0) is the top left element, and (x=width-1, y=height-1) is the bottom right. 
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param x coordinate
 * @param y coordinate
 * @return const T&  location in the grid corresponding to the coordinates provided.
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
  return data[y * _width + x]; //return index
}

/**
 * @brief row 0 is the first row, and row (height-1) is the last row. Column 0 is the first, leftmost column. 
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row coordinate
 * @param col coordinate
 * @return T&  location in the grid corresponding to the coordinates provided.
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
  return data[row * _width + col]; //return index
}

/**
 * @brief row 0 is the first row, and row (height-1) is the last row. Column 0 is the first, leftmost column. 
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row coordinate
 * @param col coordinate
 * @return const T&  location in the grid corresponding to the coordinates provided.
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
  return data[row * _width + col]; //return index
}

/**
 * @brief These keep track of the dimensions of the grid, and you'll need them in order to calculate the index where the data for a particular set of coordinates resides in.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return int width
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
    return _width; //return width var
}

/**
 * @brief These keep track of the dimensions of the grid, and you'll need them in order to calculate the index where the data for a particular set of coordinates resides in.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @return int height
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
  return _height; //return height var
}

/**
 * @brief Overwrite this grid by copying in the contents of the other grid. Replace this grid's width, height, and data, copying them from the other grid.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @tparam OTHER_CONTAINER 
 * @param source to be copied
 * @return grid_row_major <T, RA_CONTAINER>& copied grid
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) {
  resize(source.width(), source.height());  //resize bounds
  for (size_t i = 0; i < height(); i++) //loop through height
  {
    for (size_t j = 0; j < width(); j++) //loop through width
    {
      data.atxy(i,j) == source.atxy(i,j); //set
    }
  }
  return data; //return copy
}

/**
 * @brief provides an iterator that points to the first element in row i (numbering from 0). 
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
   size_t index = row * _width; //calculate index
   return data.begin() + index; //return row begin
}

/**
 * @brief returns an iterator that points just past the last element on row i. These are simple to provide in a row major grid.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
   size_t index = (row + 1) * _width; //calculate index
   return data.begin() + index; //return row end;
}

/**
 * @brief provides an iterator that points to the first element in row i (numbering from 0). 
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
   size_t index = row * _width; //calculate index
   return data.begin() + index; //return row begin const
}

/**
 * @brief returns an iterator that points just past the last element on row i. These are simple to provide in a row major grid.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param row 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
   size_t index = (row + 1) * _width; //calculate index
   return data.begin() + index; //return row end const
}

/**
 * @brief will return a column iterator that points to the first element in column i (numbering from 0)
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param col 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
  return col_iterator(data.begin() + col, _width); //return iterator
}

/**
 * @brief returns a column iterator that points to the position that you'd get to after iterating one time past the last valid element in the column.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param col 
 * @return auto 
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
  return col_iterator(data.begin() + col + _width * _height, _width); //return iterator

}

/**
 * @brief Destructively resize the grid. Do not worry about keeping the data that was previously present intact.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param new_width 
 * @param new_height 
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
  clear();  //clear container
  _width = new_width; //set bounds vars
  _height = new_height;
  data.resize(new_width * new_height); //resize to new vars
}

/**
 * @brief This method will try to replace the contents of this grid with the data from the specified file.
 * 
 * @tparam T 
 * @tparam RA_CONTAINER 
 * @param filename 
 * @return true 
 * @return false 
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {
  std::ifstream file(filename); //read in file
  int rows, cols; 
  file >> rows >> cols; //read in coords
  resize(rows, cols); //resize based on coords
  if (!file.eof()) //read file
  {
    for (auto i = 0; i < rows; i++)   //loops to set rows
    {
      for (auto j = 0; j < cols; j++)   //loops to set cols
      {
          file >> atxy(i,j);  //read values into matrix
      }
    }
  } else {
    file.close(); //close
    return false; //fail
  }
  return true; //success
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief In matrix multiplication, each cell (row i, col j) will contain the "dot product" 
 * of row i in the left hand side matrix with column j in the right hand side matrix. 
 * A dot product is the sum of the multiples of corresponding elements.
 * 
 * @tparam GRID1 The grid to be used as the left hand side of the matrix multiplication
 * @tparam GRID2 The grid to be used as the right hand side of the matrix multiplication
 * @tparam GRID3 The grid that will be used to store the result.
 * @param lhs 
 * @param rhs 
 * @param result 
 * @return true success multiply
 * @return false fail
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {
  result.resize(lhs.height(), rhs.width()); 
  for (auto i = 0; i < lhs.height(); ++i) //loop through lhs rows
    {
        for (auto j = 0; j < rhs.width(); ++j)    //loop through rhs cols
        {
          double dot_product = 0.0;
          for (auto k = 0; k < lhs.width(); ++k) //loop through lhs cols
          {
            dot_product += lhs.atrc(i,k) * rhs.atrc(k,j); //calculate product
          }
          result.atrc(i, j) = dot_product; //result
        }
    }
  return true; // report that it's not working, because it's not implemented yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////

template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
  pos += width; //set position
  return *this; //return pointer
}

template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
  col_iterator<ITERATOR> temp = *this; //temp iterator
  ++(*this); //increment
  return temp; //return iterator
}
    
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {
  return col_iterator(pos + (n * width), width); //return iterator
}

template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
  return *(pos+ (n * width)); //return pointer
}

template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
  return *(pos+ (n * width)); //return pointer
}
    
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
    return *pos; //return position

}

template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
    return *pos; //return position
}

template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
return pos == other.pos; //compare & return position
}

#endif

