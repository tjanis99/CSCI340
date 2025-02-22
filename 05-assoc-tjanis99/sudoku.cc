// Implementations of the sudoku functions go in this file
// Details can be found in README.md

// This will be compiled to sudoku.o by the Makefile and linked when needed

#include "settings.h"
#include "sudoku.h"

/**
 * @brief Set the sudoku cell known object
 * 
 * @param grid the SUDOKUGRID to use
 * @param row the row of the cell we're marking
 * @param col the column of the cell we're marking
 * @param solution the value we're marking for the cell
 */
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
    // Set the known solution in the specified cell
    grid.atrc(row, col).clear();
    grid.atrc(row, col).insert(solution);
}

/**
 * @brief Set the sudoku cell unknown object
 * 
 * @param grid the SUDOKUGRID to use
 * @param row he row of the cell we're marking
 * @param col the column of the cell we're marking
 */
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
    // Mark the cell as unknown (fill it with all possibilities)
    grid.atrc(row, col).clear();
    for (int value = 1; value <= 9; ++value) {
        grid.atrc(row, col).insert(value);
    }
}

/**
 * @brief removes the given value from the set of remaining possibilities for the cell at in the given row and column.
 * 
 * @param grid the SUDOKUGRID to use
 * @param row the row of the cell we're removing an option from
 * @param col the column of the cell we're removing an option from
 * @param value value to be removed
 */
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
    // Remove a specific possibility from the cell
    grid.atrc(row, col).erase(value);
}

/**
 * @brief If a cell is known, its known value should be displayed. If it's unknown, 
 * the unknown character should be printed, and if there are no remaining possibilities, 
 * display the impossible character.
 * 
 * @param ost output stream to print to
 * @param grid SUDOKUGRID containing the grid information
 * @param unknown The character used for a cell with an unknown value. The default is ' ' (space).
 * @param impossible The character used when a cell has no remaining possibilities. The default is 'x'
 */
void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown, char impossible) {
    const int width = grid.width();
    const int height = grid.height();
    for (int row = 0; row < height; ++row) {
        if (row % 3 == 0 && row > 0) {
            ost << "---------|---------|---------\n"; //set dividers
        }
        for (int col = 0; col < width; ++col) {
            if (col % 3 == 0 && col > 0) {
                ost << "|"; //print separators
            }

            const SET_TYPE &possibilities = grid.atrc(row, col);

            if (possibilities.empty()) {
                ost << " " << impossible << " "; 
            } else if (possibilities.size() == 1) {
                ost << " " << *possibilities.begin() << " ";
            } else {
                ost << " " << unknown << " ";
            }
        }
        ost << '\n';
    }
}

////////////////////////////////////////////////////////////////////////////////
// This one is provided. You do not need to change it.
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 * @param grid SUDOKUGRID containing the grid information
 * @param row The row of the cell we're marking
 * @param col the column of the cell we're removing an option from
 * @return int count handeled
 */
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;

  count += handle_row_for_cell(grid, row, col); 
  count += handle_col_for_cell(grid, row, col); //set counts
  count += handle_subgrid_for_cell(grid, row, col); 

  return count; 
}

/**
 * @brief 
 * 
 * @param grid the SUDOKUGRID to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling
 * @return int count erased
 */
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
    int count = 0;
    const SET_TYPE &possibilities = grid.atrc(row, col);
        //set at row & col
    if (possibilities.size() == 1) { //compare sizes
        int known_value = *possibilities.begin();
        for (int c = 0; c < 9; ++c) {
            if (c != col) {   
                count += grid.atrc(row, c).erase(known_value); //set count
            }
        }
    }

    return count;
}

/**
 * @brief If the cell at (row,col) is known (only one possibility remaining), 
 * remove its value from the possibilities of all of the other cells in the same column. 
 * If unknown, do nothing for now.
 * 
 * @param grid the SUDOKUGRID to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling
 * @return int count erased
 */
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
    int count = 0;
    const SET_TYPE &possibilities = grid.atrc(row, col);

    if (possibilities.size() == 1) { //compare size
        int known_value = *possibilities.begin();
        for (int r = 0; r < 9; ++r) {
            if (r != row) {
                count += grid.atrc(r, col).erase(known_value); //set count
            }
        }
    }

    return count;
}

/**
 * @brief if the cell at (row,col) is known (only one possibility remaining), 
 * remove its value from the possibilities of all of the other cells in the same 
 subgrid. If unknown, do nothing for now.
 * 
 * @param grid the SUDOKUGRID to use
 * @param row the row of the cell we're handling
 * @param col the column of the cell we're handling
 * @return int count handled
 */
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
    int count = 0; //set count
    const SET_TYPE &possibilities = grid.atrc(row, col); //create object

    if (possibilities.size() == 1) { //compare size
        int known_value = *possibilities.begin();
        int subgrid_row = row / 3 * 3; //set subgrids
        int subgrid_col = col / 3 * 3;

        for (int r = subgrid_row; r < subgrid_row + 3; ++r) { //interate subgrids
            for (int c = subgrid_col; c < subgrid_col + 3; ++c) {
                if (r != row || c != col) {
                    count += grid.atrc(r, c).erase(known_value); //erase
                }
            }
        }
    }

    return count;
}

/**
 * @brief 
 * 
 * @param filename filename of the grid file that's storing our Sudoku grid
 * @param grid the SUDOKUGRID that will be populated based on the input data
 * @return true If the file is successfully loaded
 * @return false Not loaded successfully
 */
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;  // Failed to open the file
    }

    // Skip the first line that contains dimensions (9x9)
    std::string line;
    std::getline(file, line);

    // Read Sudoku values from the file
    for (int row = 0; row < 9; ++row) {
        std::getline(file, line);
        std::istringstream iss(line);
        for (int col = 0; col < 9; ++col) {
            int value;
            if (iss >> value) {
                // Set known values in the grid
                set_sudoku_cell_known(grid, row, col, value);
            } else {
                // If the file doesn't contain a value for a cell, mark it as unknown
                set_sudoku_cell_unknown(grid, row, col);
            }
        }
    }

    file.close();
    return true;  // Successfully loaded the Sudoku grid
}

////////////////////////////////////////////////////////////////////////////////
// This is what the implementation looks like for grid_row_major,
//   if you're using another SUDOKUGRID type, you will likely have to change it.
////////////////////////////////////////////////////////////////////////////////
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9,9);
}

