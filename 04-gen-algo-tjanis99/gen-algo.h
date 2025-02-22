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
#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H

#include "gen-algo.decl.h"

#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

/**
 * @brief read in lines from file or cin
 * 
 * @tparam FN 
 * @param instream a std::istream that you will read the lines from. This could be cin or an open file.
 * @param linecb a callable -- a function or a function-like object that you can call with the () operator
 * @return size_t number of lines read.
 */
template <typename FN>
size_t read_lines(std::istream &instream, FN linecb) {
  std::string input; //to save inputs
  int count = 0; //count of lines
  while (getline(instream, input)) //get line from input
  {
    count++;  //increment
    linecb(input); //pass input to linecb
  }
  return count; //return count
}

/**
 * @brief goes through the whole string passed in, splitting it into tokens based on the delimiter character. 
 * 
 * @tparam FN 
 * @param instring The string to be split.
 * @param tokencb something that can be invoked as a function, which takes a single string as a parameter. 
 * This function will be called once for each token detected.
 * @param delim The character used as the delimiter for splitting.
 * @return size_t total number of tokens detected.
 */
template <typename FN>
size_t split_string_strict(const std::string &instring, FN tokencb, char delim) {
  int num_tokens = 0; //number of tokens
  size_t start = 0; //start index
    
  while (start < instring.length()) { // Find the next delimiter
      size_t delim_pos = instring.find(delim, start);
      std::string token = instring.substr(start, delim_pos - start);
      tokencb(token); // Extract the token and invoke tokencb
      num_tokens++;
      
      // Move the start position to the next character after the delimiter
      if (delim_pos != std::string::npos) {
        start = delim_pos + 1;
      } else {
        break; // No more delimiter found, exit loop
      }
  }
  return num_tokens; //return number of tokens
}

/**
 * @brief goes through the whole string passed in, splitting it into tokens based on the delimiter character. 
 * 
 * @tparam FN 
 * @param instring The string to be split.
 * @param tokencb something that can be invoked as a function, which takes a single string as a parameter. 
 * This function will be called once for each token detected.
 * @param delim The character used as the delimiter for splitting.
 * @return size_t total number of tokens detected.
 */
template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim) {
  int num_tokens = 0; //number of tokens found
  size_t start = 0; //start index
  bool in_token = false; // Indicates whether we are currently inside a token
    
  for (size_t i = 0; i < instring.length(); ++i) {
    if (instring[i] == delim) {
      if (in_token) {
        // If we were inside a token, end the token and invoke tokencb
        std::string token = instring.substr(start, i - start);
        tokencb(token);
        num_tokens++;
        in_token = false;
        }
        // Skip consecutive delimiters
        while (i + 1 < instring.length() && instring[i + 1] == delim) {
            i++;
        }
        } else {
            if (!in_token) {
                // Start a new token
                start = i;
                in_token = true;
            }
        }
    }
    
    // If the last character is not a delimiter and we are inside a token, end it
    if (in_token) {
        std::string token = instring.substr(start);
        tokencb(token);
        num_tokens++;
    }
    
    return num_tokens;
}

/**
 * @brief responsible for printing out your table in a tidy format.
 * 
 * @tparam TABLE 
 * @tparam ARRLIKE 
 * @param ost The std::ostream to print the output to.
 * @param table The STR_TABLE containing the data you need to print
 * @param widths widths[i] will contain the column width for column i
 * @param maxcol maximum number of columns to print
 * @param pre prefix - string to print before each row
 * @param sep separator - string to print between columns
 * @param post string to print at the end of each row
 * @param leftalign bool - true makes columns left-aligned, false aligns them to the right.
 */
template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream & ost, 
                 const TABLE & table, 
                 const ARRLIKE & widths, 
                 unsigned int maxcol, 
                 const std::string &pre, 
                 const std::string &sep,
                 const std::string &post,
                 bool leftalign) 
{
for (auto row : table) {
  // Limit the number of columns to be printed
    int num_columns_to_print = std::min(static_cast<unsigned int>(row.size()), maxcol);

    ost << pre;
    for (int i = 0; i < num_columns_to_print; ++i) {
      // Set column width and alignment
      ost << std::setw(widths[i]);
      if (leftalign) {  //set left align
        ost << std::left;
      } else { //set ost to alignment
        ost << std::right;
      }
        ost << row[i]; //pass value
      if (i < num_columns_to_print - 1) {
          ost << sep; //include separator
      }
    }
    ost << post << std::endl; //output
  }
}


// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
/**
 * @brief looks at each of the rows in the table provided, and returns the width of the shortest row present.
 * 
 * @param table table to iterate through
 * @return int the width of the shortest row present.
 */
int table_min_cols(const STR_TABLE &table) {
    auto shortest_row = std::min_element(table.begin(), table.end(), [](const std::vector<std::string>& row1, const std::vector<std::string>& row2) {
        return row1.size() < row2.size(); //compare
    });
    if (shortest_row != table.end()) { //if not equal to table end
        return shortest_row->size(); //set & return
    }
    return 0; //return 0
}

/**
 * @brief calculates width of string in table
 * 
 * @tparam STR_TABLE 
 * @param table table to be iterated through
 * @return std::vector<int> vector of integers. Each integer in the vector will 
 * contain the width (in characters) of the longest string in the corresponding 
 * column of the STR_TABLE passed in, table.
 */
template <typename STR_TABLE>
std::vector<int> calc_widths(const STR_TABLE &table) {
    std::vector<int> column_widths;

    // Use a flag to indicate whether any non-zero width columns are found
    bool has_non_zero_width = false;

    // Iterate through each row and update column widths
    for (const auto &row : table) {
        // If column_widths is empty, initialize it with the row's size
        if (!has_non_zero_width) {
            column_widths.assign(row.size(), 0);
        }

        // Iterate through the columns and update widths
        for (size_t i = 0; i < row.size(); ++i) {
            column_widths[i] = std::max(column_widths[i], static_cast<int>(row[i].size()));
        }

        // Check if any non-zero width columns are found
        for (int width : column_widths) {
            if (width > 0) {
                has_non_zero_width = true;
                break;
            }
        }
    }

    // If no non-zero width columns are found, return an empty vector
    if (!has_non_zero_width) {
        column_widths.clear();
    }

    return column_widths;
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
/**
 * @brief This function is responsible for loading a table 
 * from the file given, which must be a tab-separated values file. 
 * This data will be returned as a STR_TABLE.
 * 
 * @param filename file read in
 * @return STR_TABLE table with loaded values
 */
STR_TABLE load_tsv(const std::string & filename) {
    STR_TABLE table;
    std::ifstream file(filename); //file
    if (file.is_open()) { //open
        std::string line; //save string
        while (std::getline(file, line)) { //getline from file
            std::vector<std::string> row; //save row
            split_string_strict(line, [&row](const std::string &token){
              row.push_back(token); //pass token using row
            }, '\t');
            table.push_back(row); //put into table
        }
        file.close();
    }
    return table; //return table
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
/**
 * @brief sorts alphanumeric characters in table
 * 
 * @param table table to be iterated through
 * @param col column to be compared to
 */
void table_sort_alpha(STR_TABLE & table, unsigned int col) {
    std::sort(table.begin(), table.end(), [&col](const std::vector<std::string>& row1, const std::vector<std::string>& row2) {
        return row1[col] < row2[col]; //compare vector strings & return sorted
    });
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.

/**
 * @brief sorts nums in table
 * 
 * @param table table to be iterated through
 * @param col column to be compared to
 */
void table_sort_numer(STR_TABLE & table, unsigned int col) {
    std::sort(table.begin(), table.end(), [&col](const std::vector<std::string>& row1, const std::vector<std::string>& row2) {
        return row1[col] < row2[col]; //compare vector strings & return sorted
    });
}
#endif
