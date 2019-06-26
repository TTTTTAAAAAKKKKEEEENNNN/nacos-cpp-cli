#ifndef __CLIENT_WORKER_H_
#define __CLIENT_WORKER_H_
#include <map>
#include <pthread.h>
#include "NacosString.h"
#include "http/HttpAgent.h"
#include "listen/Listener.h"
#include "listen/CacheData.h"

class ClientWorker
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

	//You just can't construct a ClientWorker object without any parameter
	ClientWorker();
	std::list<String> parseListenedKeys(const String &ReturnedKeys);
public:
	ClientWorker(HttpAgent *_httpAgent);
	~ClientWorker();
	void startListening();
	void stopListening();
	void addListener(const Cachedata &cachedata);
	void removeListener(const Cachedata &cachedata);
	String performWatch();
};

#endif