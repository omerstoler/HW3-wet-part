#ifndef __BOARD_H
#define __BOARD_H
#include "Cell.hpp"

/*--------------------------------------------------------------------------------
									Board Declaration
--------------------------------------------------------------------------------*/
class Board {
public:

	Board(vector<vector<string>> &initial_board,int board_rows, int board_cols);
	int get_board_rows() const;
	int get_board_cols() const;
	void swap_boards();
	void set_cell_next_state(bool state, int row, int col);
	bool cell_curr_evolution(int row, int col) const;
	void print_board() const;

protected: // All members here are protected, instead of private for testing purposes

	vector<vector<Cell>> curr_board;
	vector<vector<Cell>> next_board;
	int board_rows;
	int board_cols;

};
#endif
