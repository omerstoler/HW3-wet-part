#ifndef __JOB_H
#define __JOB_H
#include "Board.hpp"

/*--------------------------------------------------------------------------------
									Job Declaration
--------------------------------------------------------------------------------*/
class Job {
public:

	Job(int upper_border, int lower_border);
	void tile_evolution(); //iterate on all potentially next live cells, and updates the next_board
	// static void init_boards(int board_rows, int board_cols);

protected: // All members here are protected, instead of private for testing purposes

	// static vector<vector<Cell>> curr_board;
	// static vector<vector<Cell>> next_board;
	// static int board_rows;
	// static int board_cols;
	static Board* game_board;
	int upper_border;
	int lower_border;

};
#endif
