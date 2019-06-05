#ifndef __LISTEN_WORKER_H_
#define __LISTEN_WORKER_H_
#include <map>
#include <pthread.h>
#include "NacosString.h"
#include "http/HttpAgent.h"
#include "listen/Listener.h"

//We keep it simple first, only 1 watcher thread and only 1 listener for 1 key
class Cachedata
{
public:
	String tenant;
	String dataId;
	String group;
	String dataMD5;
	Listener *listener;
	bool isFirstCheck;
	bool operator == (const Cachedata &rhs) const
	{
		return tenant == rhs.tenant && dataId == rhs.dataId && group == rhs.group;
	};
};

class ListenWorker
{
private:
	//dataID||group||tenant -> Cachedata* Mapping
	std::map<String, Cachedata*> watchList;
	pthread_mutex_t watchListMutex;
	HttpAgent *httpAgent = NULL;
	//Listener thread related info
	pthread_t threadId;
	bool stopThread;

	static void *listenerThread(void *watcher);

	//You just can't construct a ListenWorker object without any parameter
	ListenWorker();
public:
	ListenWorker(HttpAgent *_httpAgent);
	~ListenWorker();
	void startListening();
	void stopListening();
	void addListener(const Cachedata &cachedata);
	void removeListener(const Cachedata &cachedata);
	String performWatch();
};

#endif