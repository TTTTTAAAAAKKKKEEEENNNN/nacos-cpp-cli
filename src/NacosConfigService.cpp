#include "NacosConfigService.h"
#include "HTTPCli.h"
#include "Constants.h"
#include "Parameters.h"
#include "ParamUtils.h"
#include "Debug.h"

using namespace std;

NacosConfigService::~NacosConfigService()
{
	if (httpcli != NULL)
	{
		delete httpcli;
		httpcli = NULL;
	}
	
	if (svrListMgr != NULL)
	{
		delete svrListMgr;
		svrListMgr = NULL;
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
	String tag = "";
	return removeConfigInner(namesp, dataId, group, tag);
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
	String serverAddr = svrListMgr->getCurrentServerAddr();
	//Get the request url
	String url = serverAddr + "/" + DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;
	
	HttpResult res;
	
	paramValues.push_back("dataId");
	paramValues.push_back(dataId);
	if (group.compare("") != 0)
	{
		paramValues.push_back("group");
		paramValues.push_back(group);
	}
	else
	{
		paramValues.push_back("group");
		paramValues.push_back(Constants::DEFAULT_GROUP);
	}
	
	if (tenant.compare("") != 0)
	{
		paramValues.push_back("tenant");
		paramValues.push_back(tenant);
	}
	
	log_debug("Assembled URL:%s\n", url.c_str());
	try
	{
		res = httpcli->httpGet(url, headers, paramValues, encoding, timeoutMs);
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
	String serverAddr = svrListMgr->getCurrentServerAddr();
	//Get the request url
	String url = serverAddr + "/" + DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;
	
	HttpResult res;
	
	paramValues.push_back("dataId");
	paramValues.push_back(dataId);
	if (group.compare("") != 0)
	{
		paramValues.push_back("group");
		paramValues.push_back(group);
	}
	else
	{
		paramValues.push_back("group");
		paramValues.push_back(Constants::DEFAULT_GROUP);
	}
	
	if (tenant.compare("") != 0)
	{
		paramValues.push_back("tenant");
		paramValues.push_back(tenant);
	}
	
	log_debug("Assembled URL:%s\n", url.c_str());
	try
	{
		res = httpcli->httpDelete(url, headers, paramValues, encoding, POST_TIMEOUT);
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
	String serverAddr = svrListMgr->getCurrentServerAddr();
	//Get the request url
	String url = serverAddr + "/" + DEFAULT_CONTEXT_PATH + Constants::CONFIG_CONTROLLER_PATH;

	HttpResult res;

	if (group.compare("") != 0)
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

	if (tenant.compare("") != 0)
	{
		paramValues.push_back("tenant");
		paramValues.push_back(tenant);
	}
	
	if (appName.compare("") != 0)
	{
		paramValues.push_back("appName");
		paramValues.push_back(appName);
	}
	
	if (tag.compare("") != 0)
	{
		paramValues.push_back("tag");
		paramValues.push_back(tag);
	}
	
	if (betaIps.compare("") != 0)
	{
		headers.push_back("betaIps");
		headers.push_back(betaIps);
	}
	
	log_debug("Assembled URL:%s\n", url.c_str());
	try
	{
		res = httpcli->httpPost(url, headers, paramValues, encoding, POST_TIMEOUT);
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

NacosConfigService::NacosConfigService(Properties &props) throw (NacosException)
{
	httpcli = new HTTPCli();
	encoding = "UTF-8";
	namesp = "";//TODO:According to Ali's logic
	svrListMgr = new ServerListManager(props);
}