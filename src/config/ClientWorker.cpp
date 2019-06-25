#include <sys/time.h>
#include <unistd.h>
#include "listen/ClientWorker.h"
#include "listen/Listener.h"
#include "Debug.h"
#include "Constants.h"
#include "Parameters.h"

ClientWorker::ClientWorker(HttpAgent *_httpAgent)
{
	threadId = 0;
	stopThread = true;
	pthread_mutex_init(&watchListMutex, NULL);
	httpAgent = _httpAgent;
}

ClientWorker::~ClientWorker()
{
	stopListening();
}

int64_t getCurrentTimeInMs()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void *ClientWorker::listenerThread(void *parm)
{
	log_debug("Entered watch thread...\n");
	ClientWorker *thelistener = (ClientWorker*)parm;

	while (!thelistener->stopThread)
	{
		int64_t start_time = getCurrentTimeInMs();
		log_debug("Start watching at %u...\n", start_time);
		String changedKeys = thelistener->performWatch();
		
		log_debug("Watch function exit at %u...\n", getCurrentTimeInMs());
		while (getCurrentTimeInMs() - start_time < 30 * 1000)
		{
			log_debug("In the waiting loop at %u...\n", getCurrentTimeInMs());
			if (thelistener->stopThread)
			{
				return 0;
			}

			sleep(1);
		}
	}
	
	return 0;
}

std::list<String> ClientWorker::parseListenedKeys(const String &ReturnedKeys)
{
	
}

void ClientWorker::startListening()
{
	log_debug("Starting the thread...\n");
	stopThread = false;
	pthread_create(&threadId, NULL, listenerThread, (void*)this);
	log_debug("Started thread with id:%d...\n", threadId);
}

void ClientWorker::stopListening()
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

void ClientWorker::addListener(const Cachedata &cachedata)
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

void ClientWorker::removeListener(const Cachedata &cachedata)
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

String ClientWorker::performWatch()
{
	String postData;
	std::map<String, Cachedata *> copyOfDataBeingWatched;
	pthread_mutex_lock(&watchListMutex);
	for (std::map<String, Cachedata *>::iterator it = watchList.begin(); it != watchList.end(); it++)
	{
		Cachedata *curCachedata = it->second;

		postData += curCachedata->dataId;
		postData += Constants::WORD_SEPARATOR;
		postData += curCachedata->group;
		postData += Constants::WORD_SEPARATOR;
		
		if (!isNull(curCachedata->tenant))
		{
			postData += curCachedata->dataMD5;
			postData += Constants::WORD_SEPARATOR;
			postData += curCachedata->tenant;
			postData += Constants::LINE_SEPARATOR;
		}
		else
		{
			postData += curCachedata->dataMD5;
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
	//TODO:move /listener to constant
	String url = DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH + "/listener";
	HttpResult res;

	//TODO:constant for 30 * 1000
	try
	{
		res = httpAgent->httpPost(url, headers, paramValues, httpAgent->getEncode(), timeout);
	}
	catch (NetworkException e)
	{
		log_warn("Request failed with: %s\n", e.what());
		String result = "";
		return result;
	}

	log_debug("Received the message below from server:\n%s\n", res.content.c_str());
	return res.content;
}