#include "Job.h"


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
    for (int j = 0; j < board.get_board_cols(); j++) {
      temp_state = board->curr_cell_evolution(i, j);
      //==== NOTE: Might need a lock?
      board->set_next_state(temp_state, i, j);
    }
  }
}
/*********************************************************************
* Comment
*********************************************************************/
void Job::set_board(Board* game_board)
{
  board = game_board;
}
