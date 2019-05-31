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
int Job::tile_evolution()
{
  bool temp_state;
  int board_cols = Job::board->get_board_cols();
  if(upper_border==-1||lower_border==-1)
  {
    return -1;
  }
  for (int i = lower_border; i < upper_border; i++) {
    for (int j = 0; j < board_cols; j++) {
      temp_state = Job::board->cell_curr_evolution(i, j);
      //==== NOTE: Might need a lock?
      Job::board->set_cell_next_state(temp_state, i, j);
    }
  }
  return 0;
}
/*********************************************************************
* Comment
*********************************************************************/
void Job::set_board(Board* game_board)
{
  Job::board = game_board;
}

/*********************************************************************
* Comment
*********************************************************************/
void Job::set_lower_border(int upper, int lower)
{
    upper_border=upper; // First row - valid row number
    lower_border=lower; // The row after the last - invalid row for this tile
}
