#ifndef __JOBTHREAD_H
#define __JOBTHREAD_H
#include "Thread.hpp"
class Game;

class JobThread : public Thread
{
public:
	JobThread(uint thread_id, Game* game);


protected:
	// Implement this method in your subclass with the code you want your thread to run.
	void thread_workload();

private:
	Game* game_ptr;
};

#include "Game.hpp"
JobThread::JobThread(uint thread_id, Game* game): Thread(thread_id)
{
		game_ptr = game;
}
void JobThread::thread_workload()
{
	Job* job;
	while(true)
	{
		job = game_ptr->jobs_pop();
		auto gen_start = std::chrono::system_clock::now(); //calc start time
		res = job->tile_evolution();
		auto gen_end = std::chrono::system_clock::now(); // calc end time
		if (res < 0)
			break;
		game_ptr->count_increment(gen_end-gen_start);    // when game wakes-up need to set counter to 0 .
	}
}

#endif
