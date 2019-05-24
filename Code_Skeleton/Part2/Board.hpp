#ifndef __BOARD_H
#define __BOARD_H
#include "Cell.hpp"

/*--------------------------------------------------------------------------------
									Board Declaration
--------------------------------------------------------------------------------*/
class Board {
public:

	Board(int board_rows, int board_cols);
	int get_board_rows();
	int get_board_cols();
	void swap_boards();
	void set_cell_state(int row, int col);

protected: // All members here are protected, instead of private for testing purposes

	vector<vector<Cell>> curr_board;
	vector<vector<Cell>> next_board;
	int board_rows;
	int board_cols;

};
#endif
