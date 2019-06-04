#include "Board.hpp"


/*********************************************************************
* Comment
*********************************************************************/
Board::Board(vector<vector<string>> &initial_board, int board_rows, int board_cols)
{
  bool init_state;
  rows = board_rows;
  cols = board_cols;
  curr_board = new vector<vector<Cell>>;
  *curr_board = vector<vector<Cell>>(board_rows, vector<Cell>(board_cols));
  next_board = new vector<vector<Cell>>;
  *next_board = vector<vector<Cell>>(board_rows, vector<Cell>(board_cols));

  for (int i = 0; i < board_rows; i++)
  {
    for (int j = 0; j < board_cols; j++)
    {
      init_state = (initial_board[i][j][0]=='1') ? true : false;
      Cell c(init_state, i, j);
      (*curr_board)[i][j] = c;
      (*next_board)[i][j] = c;
    }
  }

}

/*********************************************************************
* Comment
*********************************************************************/
Board::~Board()
{
  delete curr_board;
  delete next_board;
}
/*********************************************************************
* Comment
*********************************************************************/
int Board::get_board_rows()
{
  return rows;
}
/*********************************************************************
* Comment
*********************************************************************/
int Board::get_board_cols()
{
  return cols;
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::swap_boards()
{
  vector<vector<Cell>> *temp;
  temp=curr_board;
  curr_board=next_board;
  next_board = temp;
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::set_cell_next_state(bool state, int row, int col)
{
  (*next_board)[row][col].set_state(state);
}
/*********************************************************************
* Comment
*********************************************************************/
bool Board::cell_curr_evolution(int row, int col)
{
  return (*curr_board)[row][col].evolution(*curr_board, rows, cols);
}
/*********************************************************************
* Comment
*********************************************************************/
void Board::print_board()
{
  const size_t board_rows = rows;
  const size_t board_cols = cols;
  cout << u8"╔" << string(u8"═") * cols << u8"╗" << endl;
  for (uint i = 0; i < board_rows; ++i) {
    cout << u8"║";
    for (uint j = 0; j < board_cols; ++j) {
      cout << ((*curr_board)[i][j].get_state() ? u8"█" : u8"░");
	//cout << (curr_board[i][j].get_state() ? u8"1" : u8"0");
    }
    cout << u8"║" << endl;
  }
  cout << u8"╚" << string(u8"═") * cols << u8"╝" << endl;
}
