#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include "listen/ClientWorker.h"
#include "listen/Listener.h"
#include "utils/url.h"
#include "utils/GroupKey.h"
#include "md5/md5.h"
#include "utils/ParamUtils.h"
#include "Debug.h"
#include "Constants.h"
#include "Parameters.h"

using namespace std;

ClientWorker::ClientWorker(HttpAgent *_httpAgent)
{
	threadId = 0;
	stopThread = true;
	pthread_mutex_init(&watchListMutex, NULL);
	pthread_mutex_init(&stopThreadMutex, NULL);
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

String ClientWorker::getServerConfig
(
	const String &tenant,
	const String &dataId,
	const String &group,
	long timeoutMs
) throw (NacosException)
{
	std::list<String> headers;
	std::list<String> paramValues;
	//Get the request url
	String url = DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;

	HttpResult res;

	paramValues.push_back("dataId");
	paramValues.push_back(dataId);
	if (!isNull(group))
	{
		paramValues.push_back("group");
		paramValues.push_back(group);
	}
	else
	{
		paramValues.push_back("group");
		paramValues.push_back(Constants::DEFAULT_GROUP);
	}

	if (!isNull(tenant))
	{
		paramValues.push_back("tenant");
		paramValues.push_back(tenant);
	}

	try
	{
		res = httpAgent->httpGet(url, headers, paramValues, httpAgent->getEncode(), timeoutMs);
	}
	catch (NetworkException e)
	{
		throw NacosException(NacosException::SERVER_ERROR, e.what());
	}
	return res.content;
}

void *ClientWorker::listenerThread(void *parm)
{
	log_debug("Entered watch thread...\n");
	ClientWorker *thelistener = (ClientWorker*)parm;

	while (!thelistener->stopThread)
	{
		int64_t start_time = getCurrentTimeInMs();
		log_debug("Start watching at %u...\n", start_time);
		thelistener->performWatch();
		
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

vector<String> ClientWorker::parseListenedKeys(const String &ReturnedKeys)
{
	String changedKeyList = urldecode(ReturnedKeys);

	vector<String> explodedList;
	ParamUtils::Explode(explodedList, changedKeyList, Constants::LINE_SEPARATOR);

	log_debug("Parsing----------------------\n");
	for (int i = 0; i < explodedList.size(); i++)
	{
		log_debug("%d : %s\n", i, explodedList[i].c_str());
	}
	log_debug("Parsing---------------------e\n");
	//If the server returns a string with a trailing \x01, actually there is no data after that
	//but ParamUtils::Explode will return an extra item with empty string, we need to remove that
	//from the list so it won't disrupt subsequent operations
	log_debug("extra data:%s\n", explodedList[explodedList.size() - 1].c_str());
	if (explodedList.size() >= 1 && ParamUtils::isBlank(explodedList[explodedList.size() - 1]))
	{
		log_debug("remove extra data\n");
		explodedList.pop_back();
	}
	return explodedList;
}

void ClientWorker::startListening()
{
	//Already started, skip this
	if (!stopThread)
	{
		log_debug("The thread is already started or the starting is in progress...\n");
		return;
	}

	pthread_mutex_lock(&stopThreadMutex);
	if (!stopThread)
	{
		pthread_mutex_unlock(&stopThreadMutex);
		log_debug("The thread is already started or the starting is in progress...\n");
		return;
	}

	stopThread = false;
	pthread_mutex_unlock(&stopThreadMutex);

	log_debug("Starting the thread...\n");
	pthread_create(&threadId, NULL, listenerThread, (void*)this);
	log_debug("Started thread with id:%d...\n", threadId);
}
	
void ClientWorker::stopListening()
{
	if (stopThread)//Stop in progress
	{
		log_debug("The thread is already stopped or the stop is in progress...\n");
		return;
	}

	pthread_mutex_lock(&stopThreadMutex);
	if (stopThread)//Stop in progress
	{
		pthread_mutex_unlock(&stopThreadMutex);
		log_debug("The thread is already stopped or the stop is in progress...\n");
		return;
	}

	stopThread = true;
	pthread_mutex_unlock(&stopThreadMutex);

	pthread_join(threadId,NULL);
	log_info("The thread is stopped successfully...\n");

}

void ClientWorker::addListener(const Cachedata &cachedata)
{
	String key = GroupKey::getKeyTenant(cachedata.dataId, cachedata.group, cachedata.tenant);
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
	String key = GroupKey::getKeyTenant(cachedata.dataId, cachedata.group, cachedata.tenant);
	pthread_mutex_lock(&watchListMutex);
	map<String, Cachedata *>::iterator it = watchList.find(key);
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

String ClientWorker::checkListenedKeys()
{
	String postData;
	pthread_mutex_lock(&watchListMutex);
	for (map<String, Cachedata *>::iterator it = watchList.begin(); it != watchList.end(); it++)
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

	list<String> headers;
	list<String> paramValues;

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

void ClientWorker::performWatch()
{
	MD5 md5;
	String changedData = checkListenedKeys();
	vector<String> changedList = ClientWorker::parseListenedKeys(changedData);
	pthread_mutex_lock(&watchListMutex);
	for (std::vector<String>::iterator it = changedList.begin(); it != changedList.end(); it++)
	{
		String dataId, group, tenant;
		ParamUtils::parseString2KeyGroupTenant(*it, dataId, group, tenant);
		log_debug("Processing item:%s, dataId = %s, group = %s, tenant = %s\n",
					it->c_str(), dataId.c_str(), group.c_str(), tenant.c_str());
		
		String key = GroupKey::getKeyTenant(dataId, group, tenant);
		map<String, Cachedata *>::iterator cacheDataIt = watchList.find(key);
		//check whether the data being watched still exists
		if (cacheDataIt != watchList.end())
		{
			log_debug("Found entry for:%s\n", key.c_str());
			Cachedata *cachedq = cacheDataIt->second;
			//TODO:Constant
			String updatedcontent = ClientWorker::getServerConfig(cachedq->tenant, cachedq->dataId,	cachedq->group, 3000);
			log_debug("Data fetched from the server: %s\n", updatedcontent.c_str());
			md5.reset();
			md5.update(updatedcontent.c_str());
			cachedq->dataMD5 = md5.toString();
			log_debug("MD5 got for that data: %s\n", cachedq->dataMD5.c_str());
			cachedq->listener->receiveConfigInfo(updatedcontent);
		}
	}
	pthread_mutex_unlock(&watchListMutex);
}