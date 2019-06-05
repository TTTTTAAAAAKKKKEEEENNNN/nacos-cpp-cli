#include "listen/ListenWorker.h"
#include "listen/Listener.h"
#include "Debug.h"
#include "Constants.h"
#include "Parameters.h"

ListenWorker::ListenWorker(HttpAgent *_httpAgent)
{
	threadId = 0;
	stopThread = true;
	pthread_mutex_init(&watchListMutex, NULL);
	httpAgent = _httpAgent;
}

ListenWorker::~ListenWorker()
{
	stopListening();
}

void *ListenWorker::listenerThread(void *parm)
{
	log_debug("Entered watch thread...\n");
	ListenWorker *thelistener = (ListenWorker*)parm;

	while (!thelistener->stopThread)
	{
		thelistener->performWatch();
	}
	
	return 0;
}

void ListenWorker::startListening()
{
	log_debug("Starting the thread...\n");
	stopThread = false;
	pthread_create(&threadId, NULL, listenerThread, (void*)this);
	log_debug("Started thread with id:%d...\n", threadId);
}

void ListenWorker::stopListening()
{
	log_debug("Stopping the thread...\n");
	if (stopThread)//Stop in progress
	{
		log_debug("The thread is already stopped or the stop is in progress...\n");
		return;
	}

	stopThread = true;
	pthread_join(threadId,NULL);
	log_info("The thread is stopped successfully...\n");
}

void ListenWorker::addListener(const Cachedata &cachedata)
{
	String key = cachedata.dataId + "||" + cachedata.group + "||" + cachedata.tenant;
	log_debug("Adding listener with key: %s\n", key.c_str());
	pthread_mutex_lock(&watchListMutex);

	//Check whether the cachedata being added to the list already exists
	if (watchList.find(key) != watchList.end())
	{
		log_warn("Key %s is already in the watch list, leaving...\n", key.c_str());
		pthread_mutex_unlock(&watchListMutex);
		return;
	}

	//If no, copy one
	Cachedata *copyOfCurWatchData = new Cachedata();
	*copyOfCurWatchData = cachedata;
	watchList[key] = copyOfCurWatchData;
	pthread_mutex_unlock(&watchListMutex);
	log_debug("Key %s is added successfully!\n", key.c_str());
}

void ListenWorker::removeListener(const Cachedata &cachedata)
{
	String key = cachedata.dataId + "||" + cachedata.group + "||" + cachedata.tenant;
	pthread_mutex_lock(&watchListMutex);
	std::map<String, Cachedata *>::iterator it = watchList.find(key);
	//Check whether the cachedata being removed exists
	if (it == watchList.end())
	{
		pthread_mutex_unlock(&watchListMutex);
		return;
	}

	//If so, remove it and free the resources
	Cachedata *copyOfCurWatchData = it->second;
	watchList.erase(it);
	delete copyOfCurWatchData;
	copyOfCurWatchData = NULL;
	pthread_mutex_unlock(&watchListMutex);
}

String ListenWorker::performWatch()
{
	String postData;
	std::map<String, Cachedata *> copyOfDataBeingWatched;
	pthread_mutex_lock(&watchListMutex);
	for (std::map<String, Cachedata *>::iterator it = watchList.begin(); it != watchList.end(); it++)
	{
		Cachedata *curCachedata = it->second;
		//Copy the keys being watched
		Cachedata *copyOfCurWatchData = new Cachedata();
		*copyOfCurWatchData = *curCachedata;
		copyOfDataBeingWatched[it->first] = copyOfCurWatchData;

		postData += copyOfCurWatchData->dataId;
		postData += Constants::WORD_SEPARATOR;
		postData += copyOfCurWatchData->group;
		postData += Constants::WORD_SEPARATOR;
		
		if (!isNull(copyOfCurWatchData->tenant))
		{
			postData += copyOfCurWatchData->dataMD5;
			postData += Constants::WORD_SEPARATOR;
			postData += copyOfCurWatchData->tenant;
			postData += Constants::LINE_SEPARATOR;
		}
		else
		{
			postData += copyOfCurWatchData->dataMD5;
			postData += Constants::LINE_SEPARATOR;
		}
	}
	pthread_mutex_unlock(&watchListMutex);

	std::list<String> headers;
	std::list<String> paramValues;

	//TODO:put it into constants list
	long timeout = 30000;

	headers.push_back("Long-Pulling-Timeout");
	headers.push_back("30000");

	paramValues.push_back(Constants::PROBE_MODIFY_REQUEST);
	paramValues.push_back(postData);
	log_debug("Assembled postData:%s\n", postData.c_str());

	//Get the request url
	String url = DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;
	HttpResult res;

	//TODO:constant for 30 * 1000
	res = httpAgent->httpPost(url, headers, paramValues, httpAgent->getEncode(), timeout);

	return res.content;
}