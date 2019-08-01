#ifndef __THREAD_H_
#define __THREAD_H_
#include <exception>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "NacosString.h"
#include "Debug.h"
#define gettidv1() syscall(__NR_gettid)  

typedef void (*ThreadFn)();

class Thread {
private:
	NacosString _threadName;
	pthread_t _thread;
	ThreadFn _function;
	pid_t _tid;
	bool _start;
	
public:
	void setThreadName(const NacosString &threadName) { _threadName = threadName; };
	NacosString getThreadName() { return _threadName; };
	static void *threadFunc(void *param)
	{
		Thread *currentThread = (Thread*)param;
		currentThread->_tid = gettid();

		try
		{
			currentThread->_function();
		}
		catch (std::exception &e)
		{
			log_error("Exception happens when executing:\n");
			log_error("Thread Name:%s Thread Id:%d\n", currentThread->_threadName.c_str(), currentThread->_tid);
			abort();
		}
		catch (...)
		{
			log_error("Unknown exception happens when executing:\n");
			log_error("Thread Name:%s Thread Id:%d\n", currentThread->_threadName.c_str(), currentThread->_tid);
			throw;
		}

		return NULL;
	}

	Thread(const NacosString &threadName, ThreadFn fn)
	: _threadName(threadName), _function(fn)
	{
		_start = false;
	};

	~Thread()
	{
		_start = false;
	}

	void start()
	{
		_start = true;
		pthread_create(&_thread, NULL, threadFunc, (void*)this);
	}

	void join()
	{
		if (!_start)
		{
			return;
		}

		pthread_join(_thread, NULL);
	}
};


#endif
