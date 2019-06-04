#include "Game.hpp"
#include "JobThread.hpp"

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
Game::Game(game_params gp)
{
	pthread_cond_init(&gen_done, NULL);
  pthread_mutex_init(&m_lock, NULL);
	m_curr_gen_num = 0;
	const string const_gp_filename = gp.filename;
	vector<string> file_lines = utils::read_lines(const_gp_filename);
	vector<vector<string>> string_mat_board;
	int rows = file_lines.size();
	int cols;

	m_gen_num = gp.n_gen;
	m_thread_num = gp.n_thread;
	//m_thread_num = 1; // ===== for debug / tests
	interactive_on = gp.interactive_on;
  print_on = gp.print_on;

	for (int i = 0; i < rows; i++)
	{
		string_mat_board.push_back(utils::split(file_lines[i], ' '));
	}
	cols = string_mat_board[0].size(); // IFF not empty


	Board* b = new Board(string_mat_board, rows, cols);
	board = b;
	Job::set_board(board);

}

Game::~Game()
{
	pthread_cond_destroy(&gen_done);
  pthread_mutex_destroy(&m_lock);
	delete board;
}
/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
void Game::run()
{
	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		m_curr_gen_num = i;
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(nullptr);
	} // generation loop
	print_board("Final Board");
	_destroy_game();
}

void Game::_init_game()
{
  // init threads pool, init jobs vec
	int lower=0;
	int upper=0;
	int board_rows = board->get_board_rows();
	 // ===== NOTE: before use of threads parallelism, we init job to be all board filling
	int job_rows, div, mod;

	// divide to tiles
	int tiles_num = _calc_tiles_num();
	div = board_rows / tiles_num;
	mod = board_rows % tiles_num;
	//=======================================
	m_tile_hist.reserve(tiles_num*m_gen_num);
	//=======================================
	for (int i = 0; i < tiles_num; i++)
	{
		job_rows = div;
		if (i < mod)
			job_rows += 1;
		lower = upper;
		upper += job_rows;
		//===== Job init
		Job* job = new Job(upper, lower); //==== TODO: To update instead of allocating everytime
		jobs_vec.push_back(job);
		//===== Thread init
		JobThread* thread = new JobThread(i,this);
		thread->start();
		m_threadpool.push_back(thread);
	}
}

int Game::_calc_tiles_num() const
{
	uint board_rows = board->get_board_rows();
	int tiles_num = (board_rows > m_thread_num) ? m_thread_num : board_rows;
	return tiles_num;
}

void Game::_step(uint curr_gen)
{
	int tiles_num = _calc_tiles_num();
	tiles_done = 0; // ============= NOTE: risky ?
	for (int i = 0; i < tiles_num; i++)
	{
		jobs.push(jobs_vec[i]);
	}
	// sync
	pthread_mutex_lock(&m_lock);
	while(tiles_done < tiles_num)
		pthread_cond_wait(&gen_done, &m_lock);
	pthread_mutex_unlock(&m_lock);

	board->swap_boards();

	// Push jobs to queue
	// Wait for the workers to finish calculating
	// Swap pointers between current and next field
	// NOTE: Threads must not be started here - doing so will lead to a heavy penalty in your grade
}

void Game::_destroy_game()
{
	// Destroys board and frees all threads and resources
	// Not implemented in the Game's destructor for testing purposes.
	// All threads must be joined here
	uint tiles_num = _calc_tiles_num();
	for (uint i = 0; i < tiles_num; ++i)
	{
			jobs_vec[i]->set_upper_lower(-1,-1);
			jobs.push(jobs_vec[i]);
  }
	for (uint i = 0; i < tiles_num; ++i)
	{
      m_threadpool[i]->join();
  }
	uint size_vec = jobs_vec.size();
	for (uint i = 0; i < size_vec; i++)
	{
		delete jobs_vec[i];
	}
}

uint Game::thread_num() const
{
	const uint t_num = _calc_tiles_num();
	return t_num;
}

const vector<double> Game::gen_hist() const
{
	return m_gen_hist;
}

const vector<tile_record> Game::tile_hist() const
{
	return m_tile_hist;
}

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
inline void Game::print_board(const char* header) {

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
/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/
Job* Game::jobs_pop()
{
	return jobs.pop();
}
/*--------------------------------------------------------------------------------
							             tiles_done++, hist update
--------------------------------------------------------------------------------*/
void Game::count_increment(double tile_compute_time, uint id,double tile_start, double tile_finish)
{
	pthread_mutex_lock(&m_lock);
	tiles_done++;
	pthread_cond_signal(&gen_done);
	pthread_mutex_unlock(&m_lock);
	
	tile_record tr = {tile_compute_time, id,tile_start,tile_finish};
	m_tile_hist[m_curr_gen_num * thread_num() + id] = tr;
}
