#include "config/NacosConfigService.h"
#include "http/HTTPCli.h"
#include "http/ServerHttpAgent.h"
#include "Constants.h"
#include "Parameters.h"
#include "ParamUtils.h"
#include "Debug.h"
#include "md5/md5.h"

using namespace std;

NacosConfigService::NacosConfigService(Properties &props) throw (NacosException)
{
	httpcli = new HTTPCli();
	encoding = "UTF-8";
	namesp = "";//TODO:According to Ali's logic
	svrListMgr = new ServerListManager(props);
	httpAgent = new ServerHttpAgent(httpcli, encoding, svrListMgr, namesp);
	clientWorker = new ClientWorker(httpAgent);
}

NacosConfigService::~NacosConfigService()
{

	if (clientWorker != NULL)
	{
		clientWorker->stopListening();
		delete clientWorker;
		clientWorker = NULL;
	}

	if (httpAgent != NULL)
	{
		delete httpAgent;
		httpAgent = NULL;
	}
	
	if (svrListMgr != NULL)
	{
		delete svrListMgr;
		svrListMgr = NULL;
	}
	
	if (httpcli != NULL)
	{
		delete httpcli;
		httpcli = NULL;
	}
}

String NacosConfigService::getConfig
(
	const String &dataId,
	const String &group,
	long timeoutMs
) throw(NacosException)
{
	return getConfigInner(namesp, dataId, group, timeoutMs);
}

bool NacosConfigService::publishConfig
(
	const String &dataId,
	const String &group,
	const String &content
) throw (NacosException)
{
	return publishConfigInner(namesp, dataId, group, NULLSTR, NULLSTR, NULLSTR, content);
}
	
bool NacosConfigService::removeConfig
(
	const String &dataId,
	const String &group
) throw (NacosException)
{
	return removeConfigInner(namesp, dataId, group, NULLSTR);
}

String NacosConfigService::getConfigInner
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

bool NacosConfigService::removeConfigInner
(
	const String &tenant,
	const String &dataId,
	const String &group,
	const String &tag
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
		res = httpAgent->httpDelete(url, headers, paramValues, httpAgent->getEncode(), POST_TIMEOUT);
	}
	catch (NetworkException e)
	{
		log_warn("[remove] error, %s, %s, %s, msg: %s\n", dataId.c_str(), group.c_str(), tenant.c_str(), e.what());
		return false;
	}
	
	//If the server returns true, then this call succeeds
	if (res.content.compare("true") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool NacosConfigService::publishConfigInner
(
	const String &tenant,
	const String &dataId,
	const String &group,
	const String &tag,
	const String &appName,
	const String &betaIps,
	const String &content
) throw (NacosException)
{
	//TODO:More stringent check, need to improve checkParam() function
	ParamUtils::checkParam(dataId, group, content);

	std::list<String> headers;
	std::list<String> paramValues;
	String parmGroupid;
	//Get the request url
	String url = DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;

	HttpResult res;

	if (!isNull(group))
	{
		parmGroupid = group;
	}
	else
	{
		parmGroupid = Constants::DEFAULT_GROUP;
	}
	paramValues.push_back("group");
	paramValues.push_back(parmGroupid);
	
	paramValues.push_back("dataId");
	paramValues.push_back(dataId);

	paramValues.push_back("content");
	paramValues.push_back(content);

	if (!isNull(tenant))
	{
		paramValues.push_back("tenant");
		paramValues.push_back(tenant);
	}
	
	if (!isNull(appName))
	{
		paramValues.push_back("appName");
		paramValues.push_back(appName);
	}
	
	if (!isNull(tag))
	{
		paramValues.push_back("tag");
		paramValues.push_back(tag);
	}
	
	if (!isNull(betaIps))
	{
		headers.push_back("betaIps");
		headers.push_back(betaIps);
	}

	try
	{
		res = httpAgent->httpPost(url, headers, paramValues, httpAgent->getEncode(), POST_TIMEOUT);
	}
	catch (NetworkException e)
	{
		//
		log_warn("[{}] [publish-single] exception, dataId=%s, group=%s, msg=%s\n", dataId.c_str(), group.c_str(), tenant.c_str(), e.what());
		return false;
	}
	
	//If the server returns true, then this call succeeds
	if (res.content.compare("true") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void NacosConfigService::addListener
(
	const String &dataId,
	const String &group,
	Listener *listener
) throw(NacosException)
{
	Cachedata cachedata;
	cachedata.tenant = namesp;
	cachedata.dataId = dataId;
	//TODO:give a constant to this hard-coded number
	String cfgcontent = getConfig(dataId, group, 3000);
	if (!isNull(group))
	{
		cachedata.group = group;
	}
	else
	{
		cachedata.group = Constants::DEFAULT_GROUP;
	}

	if (!isNull(cfgcontent))
	{
		MD5 md5;
		md5.update(cfgcontent);
		cachedata.dataMD5 = md5.toString();
	}
	else
	{
		cachedata.dataMD5 = "";
	}
	cachedata.listener = listener;
	clientWorker->addListener(cachedata);
	clientWorker->startListening();
}
