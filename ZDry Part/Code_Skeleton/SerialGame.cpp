#include "SerialGame.hpp"

// struct game_params {
// 	// All here are derived from ARGV, the program's input parameters.
// 	string filename;
// };
/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
SerialGame::SerialGame(game_params gp)
{
	const string const_gp_filename = gp.filename;
	vector<string> file_lines = utils::read_lines(const_gp_filename);
	vector<vector<string>> string_mat_board;
	int rows = file_lines.size();
	int cols;

	m_gen_num = gp.n_gen;
	m_thread_num = gp.n_thread;
	//m_thread_num = 1; // ===== Serial version
	interactive_on = gp.interactive_on;
  print_on = gp.print_on;

	for (int i = 0; i < rows; i++)
	{
		string_mat_board.push_back(utils::split(file_lines[i], ' '));
	}
	cols = string_mat_board[0].size(); //==== IFF not empty


	Board* b = new Board(string_mat_board, rows, cols);
	board = b;
	Job::set_board(board);
	// Create game fields - Consider using utils:read_file, utils::split
	// Create & Start threads
	// Testing of your implementation will presume all threads are started here
}

SerialGame::~SerialGame()
{
	//=====
	delete board;
}

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
void SerialGame::run()
{
	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(nullptr);
	} // generation loop
	print_board("Final Board");
	_destroy_game();
}

void SerialGame::_init_game()
{

	// Create game fields - Consider using utils:read_file, utils::split
	// Create & Start threads
	// Testing of your implementation will presume all threads are started here
}

int SerialGame::_calc_tiles_num()
{
	int board_rows = board->get_board_rows();
	int tiles_num = (board_rows > m_thread_num) ? m_thread_num : board_rows;
	return tiles_num;
}

void SerialGame::_step(uint curr_gen)
{
	int lower=0;
	int upper=0;
	int board_rows = board->get_board_rows();
	 // ===== NOTE: before use of threads parallelism, we init job to be all board filling
	int job_rows, div, mod;

	// divide to tiles
	int tiles_num = _calc_tiles_num();

	for (int i = 0; i < tiles_num; i++) {
		// PCQueue does push_back(job)
		div = board_rows / tiles_num;
		mod = board_rows % tiles_num;

		job_rows = div;
		if (i < mod)
			job_rows += 1;
		lower = upper;
		upper += job_rows;
		Job job(upper, lower);
		//====== add job to PCQueue - NOTE: sync problems might come upon insertion
																						// job.tile_evolution(); - moves to consumer
	}
	/*=======================================================
	cond: num of finished jobs != tiles_num
	while(cond != true)
		cond_wait(cond_var,m);
	=======================================================*/

	 //===== NOTE: Will be moved to thread implementation
	board->swap_boards();
	// Push jobs to queue
	// Wait for the workers to finish calculating
	// Swap pointers between current and next field
	// NOTE: Threads must not be started here - doing so will lead to a heavy penalty in your grade
}

void SerialGame::_destroy_game()
{
	// Destroys board and frees all threads and resources
	// Not implemented in the Game's destructor for testing purposes.
	// All threads must be joined here

	// for (uint i = 0; i < m_thread_num; ++i) {
  //       m_threadpool[j]->join();
  //   }
}

uint SerialGame::thread_num() const
{
	return m_thread_num;
}

const vector<double> SerialGame::gen_hist() const
{
	return m_gen_hist;
}

const vector<tile_record> SerialGame::tile_hist() const
{
	return m_tile_hist;
}

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
inline void SerialGame::print_board(const char* header) {

	if(print_on){

		// Clear the screen, to create a running animation
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != nullptr)
			cout << "<------------" << header << "------------>" << endl;

		//===================
		board->print_board();
		//===================

		// Display for GEN_SLEEP_USEC micro-seconds on screen
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}
