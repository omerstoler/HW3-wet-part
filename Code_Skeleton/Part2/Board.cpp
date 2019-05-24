#include "Board.hpp"


/*********************************************************************
* Comment
*********************************************************************/
Board::Board(vector<vector<string>> initial_board, int board_rows, int board_cols)
{
  curr_board.reserve(board_rows); // alloc
  next_board.reserve(board_rows);
  for (int i = 0; i < board_rows; i++)
  {
    for (int j = 0; j < board_cols; i++)
    {
      bool init_state = (initial_board[i][j]=='1') ? true : false;
      Cell c(init_state, i, j);
      curr_board[i].push_back(c);
      next_board[i].push_back(c);
    }
  }
}
/*********************************************************************
* Comment
*********************************************************************/
int Board::get_board_rows()
{
  return board_rows;
}
/*********************************************************************
* Comment
*********************************************************************/
int Board::get_board_cols()
{
  return board_cols;
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::swap_boards()
{
  curr_board.swap(next_board);
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::set_cell_next_state(bool state, int row, int col)
{
  next_board[row][col].set_state(state);
}
/*********************************************************************
* Comment
*********************************************************************/
bool Board::cell_curr_evolution(int row, int col)
{
  return next_board[row][col].evolution(curr_board, row, col);
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::print_board()
{
  cout << u8"╔" << string(u8"═") * board_cols << u8"╗" << endl;
  for (uint i = 0; i < board_rows ++i) {
    cout << u8"║";
    for (uint j = 0; j < board_cols; ++j) {
      cout << (curr_board[i][j].get_state() ? u8"█" : u8"░");
    }
    cout << u8"║" << endl;
  }
  cout << u8"╚" << string(u8"═") * board_cols << u8"╝" << endl;
}
