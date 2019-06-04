#ifndef __JOB_H
#define __JOB_H
#include "Board.hpp"

/*--------------------------------------------------------------------------------
									Job Declaration
--------------------------------------------------------------------------------*/
class Job {
public:

	Job(int upper, int lower,int job_id);
	int tile_evolution(); //iterate on all potentially next live cells, and updates the next_board
	static void set_board(Board* game_board);
	void set_upper_lower(int upper, int lower);
	int job_id();
protected: // All members here are protected, instead of private for testing purposes

	static Board* board;
	int upper_border;
	int lower_border;
	int m_job_id;
};
#endif
