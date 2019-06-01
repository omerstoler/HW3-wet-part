#include "Cell.hpp"

/*********************************************************************
* Comment
*********************************************************************/
Cell::Cell()
{
  is_alive = false;
  coord_row = -1;
  coord_col = -1;
}
/*********************************************************************
* Comment
*********************************************************************/
Cell::Cell(const Cell& c)
{
  is_alive = c.is_alive;
  coord_row = c.coord_row;
  coord_col = c.coord_col;
}
/*********************************************************************
* Comment
*********************************************************************/
Cell::Cell(bool state, int row, int col)
{
  is_alive = state;
  coord_row = row;
  coord_col = col;
}
/*********************************************************************
* Comment
*********************************************************************/
// Cell& Cell::operator=(const Cell& c)
// {
//   is_alive = c.is_alive;
//   coord_row = c.coord_row;
//   coord_col = c.coord_col;
// }
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

/*********************************************************************
* Comment
*********************************************************************/
int Cell::_get_neigh_alive_num(vector<vector<Cell>> &curr_board,int board_rows, int board_cols)

{
  int counter = 0;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if(i == 0 && j == 0)
      {

      }
      else if(i + coord_row >= 0 && i + coord_row < board_rows && j + coord_col >= 0 && j + coord_col < board_cols)
      {
        if(curr_board[i+coord_row][j+coord_col].get_state() == true)
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
bool Cell::evolution(vector<vector<Cell>> &curr_board,int board_rows, int board_cols)
{

  int num_of_alive = _get_neigh_alive_num(curr_board, board_rows, board_cols);

  //=== I'm alive!
  if(curr_board[coord_row][coord_col].get_state() == true)
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
