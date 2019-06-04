#ifndef __BOARD_H
#define __BOARD_H
#include "Cell.hpp"
#include "utils.hpp"

/*--------------------------------------------------------------------------------
									Board Declaration
--------------------------------------------------------------------------------*/
class Board {
public:

	Board(vector<vector<string>> &initial_board,int board_rows, int board_cols);
	~Board();
	int get_board_rows();
	int get_board_cols();
	void swap_boards();
	void set_cell_next_state(bool state, int row, int col);
	bool cell_curr_evolution(int row, int col);
	void print_board();

protected: // All members here are protected, instead of private for testing purposes

	vector<vector<Cell>> *curr_board;
	vector<vector<Cell>> *next_board;
	int rows;
	int cols;

};
#endif