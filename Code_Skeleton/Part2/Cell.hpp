#ifndef __CELL_H
#define __CELL_H
#include "Headers.hpp"

/*--------------------------------------------------------------------------------
									Cell Declaration
--------------------------------------------------------------------------------*/
class Cell {
public:
	Cell();
	Cell(const Cell& c);
	Cell(bool state,int row, int col);
	bool evolution(vector<vector<Cell>> &curr_board, int board_rows, int board_cols);
	bool get_state();
	void set_state(bool state);
	// Cell& operator=(const Cell& c);
protected: // All members here are protected, instead of private for testing purposes

	int coord_row; //=== coordinate
	int coord_col;

	bool is_alive;

	int _get_neigh_alive_num(vector<vector<Cell>> &curr_board, int board_rows, int board_cols);

};
#endif
