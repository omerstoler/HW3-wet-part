#include "Job.hpp"

Board* Job::board=NULL;

/*********************************************************************
* Comment
*********************************************************************/
Job::Job(int upper, int lower)
{
  upper_border=upper; // First row - valid row number
  lower_border=lower; // The row after the last - invalid row for this tile
}
/*********************************************************************
* Comment
*********************************************************************/
void Job::tile_evolution()
{
  bool temp_state;
  for (int i = lower_border; i < upper_border; i++) {
    for (int j = 0; j < Job::board->get_board_cols(); j++) {
      temp_state = Job::board->cell_curr_evolution(i, j);
      //==== NOTE: Might need a lock?
      Job::board->set_cell_next_state(temp_state, i, j);
    }
  }
}
/*********************************************************************
* Comment
*********************************************************************/
void Job::set_board(Board* game_board)
{
  Job::board = game_board;
}
