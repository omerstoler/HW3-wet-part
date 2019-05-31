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
	while(true)
	{
		//job = Gameptr->jobs_pop();
		//calc start time
		//res = job->tile_evolution();
		// calc end time
		// if res < 0 : break;           // need to update -1 scenarios in tile_evolution
		//Gameptr->count_increment(tile_compute_time);    // when game wakes-up need to set counter to 0 .
	}
}

#endif
