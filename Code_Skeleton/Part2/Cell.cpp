#include "Cell.hpp"


/*********************************************************************
* Comment
*********************************************************************/
Cell::Cell(bool state,int row, int col)
{
  is_alive = state;
  coord_row = row;
  coord_col = col;
}

/*********************************************************************
* Comment
*********************************************************************/
void Cell::set_state(bool state)
{
    is_alive = state;
}
/*********************************************************************
* Comment
*********************************************************************/
bool Cell::get_state()
{
    return is_alive;
}

{/*********************************************************************
* Comment
*********************************************************************/
int Cell::_get_neigh_alive_num(bool** curr_board,int board_rows, int board_cols)

{
  int counter = 0;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; i++)
    {
      if(i = 0 && j = 0)
      {
        continue;
      }
      if(i +  0 <= coord_row && i + coord_row < board_rows && j + 0 <= coord_col && j + coord_col < board_cols)
      {
        if(curr_board[i+coord_row][j+coord_col] == true)
        {
          counter++;
        }
      }
    }
  }
  return counter;
}
/*********************************************************************
* What happend with me in the next board?
*********************************************************************/
bool Cell::evolution(bool** curr_board,int board_rows, int board_cols)
{
  int num_of_alive = _get_neigh_alive_num(curr_board, board_rows, board_cols);

  //=== I'm alive!
  if(curr_board[coord_row][coord_col]==true)
  {
    if(num_of_alive < 2 ||  num_of_alive > 3 )
      return false;

    return true;
  }
  //=== I'm dead...
  else
  {
    if(num_of_alive == 3)
      return true;

    return false;
  }
}

void Cell::set_state(bool state)
{
  is_alive = state;
}
