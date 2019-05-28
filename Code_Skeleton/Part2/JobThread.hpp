#ifndef __JOBTHREAD_H
#define __JOBTHREAD_H
#include "Thread.hpp"
class JobThread : public Thread
{
public:
	JobThread(uint thread_id)
	{
		// Only places thread_id
	}
	virtual ~JobThread() {} // Does nothing

	// Returns true if the thread was successfully started, false if there was an error starting the thread
	// Creates the internal thread via pthread_create
	bool start()
	{
	}

	// Will not return until the internal thread has exited.
	void join()
	{
	}

	// Returns the user identifier
	uint thread_id()
	{
		return m_thread_id;
	}
protected:
	// Implement this method in your subclass with the code you want your thread to run.
	virtual void thread_workload();

private:
	pthread_t m_thread;
};

#endif
