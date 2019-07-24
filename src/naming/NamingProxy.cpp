#include <map>
#include <stdlib.h>
#include "naming/NamingProxy.h"
#include "naming/CommonParams.h"
#include "utils/ParamUtils.h"
#include "utils/UtilAndComs.h"
#include "utils/UuidUtils.h"
#include "http/httpStatCode.h"
#include "Debug.h"
#include "NacosExceptions.h"

using namespace std;

NamingProxy::NamingProxy(HTTPCli *httpcli, const String &_namespaceId, const String &_endpoint, const String &_serverList)
{
	serverPort = "8848";//TODO:get this from the environment variable
	httpCli = httpcli;
	namespaceId = _namespaceId;
	endpoint = _endpoint;
	ParamUtils::Explode(serverList, _serverList, ',');
	if (serverList.size() == 1)
	{
		nacosDomain = _serverList;
	}
}

NamingProxy::~NamingProxy()
{
	httpCli = NULL;
}

void NamingProxy::registerService(const String &serviceName, const String &groupName, Instance instance) throw (NacosException)
{
	log_info("[REGISTER-SERVICE] %s registering service %s with instance: %s\n",
	namespaceId.c_str(), serviceName.c_str(), instance.toString());

	map<String, String> params;
	params[CommonParams::NAMESPACE_ID] = namespaceId;
	params[CommonParams::SERVICE_NAME] = serviceName;
	params[CommonParams::GROUP_NAME] = groupName;
	params[CommonParams::CLUSTER_NAME] = instance.clusterName;
	params["ip"] = instance.ip;
	params["port"] = NacosString::valueOf(instance.port);
	params["weight"] = NacosString::valueOf(instance.weight);
	params["enable"] = NacosString::valueOf(instance.enabled);
	params["healthy"] = NacosString::valueOf(instance.healthy);
	params["ephemeral"] = NacosString::valueOf(instance.ephemeral);
	//TODO:transfer metadata in JSON form
	//params["metadata"] = JSON.toJSONString(instance.getMetadata()));

	reqAPI(UtilAndComs::NACOS_URL_INSTANCE, params, HTTPCli::POST);
}

void NamingProxy::deregisterService(const String &serviceName, Instance instance) throw (NacosException)
{
	log_info("[DEREGISTER-SERVICE] %s deregistering service %s with instance: %s\n",
	namespaceId.c_str(), serviceName.c_str(), instance.toString());

	map<String, String> params;
	params[CommonParams::NAMESPACE_ID] = namespaceId;
	params[CommonParams::SERVICE_NAME] = serviceName;
	params[CommonParams::CLUSTER_NAME] = instance.clusterName;
	params["ip"] = instance.ip;
	params["port"] = NacosString::valueOf(instance.port);
	params["ephemeral"] = NacosString::valueOf(instance.ephemeral);

	reqAPI(UtilAndComs::NACOS_URL_INSTANCE, params, HTTPCli::DELETE);
}

String NamingProxy::reqAPI(const String &api, map<String, String> &params, int method) throw (NacosException)
{
    return reqAPI(api, params, serverList, method);
}

String NamingProxy::reqAPI(const String &api, map<String, String> &params, list<String> &servers, int method) throw (NacosException)
{
	params[CommonParams::NAMESPACE_ID] = getNamespaceId();

	if (servers.empty() && ParamUtils::isBlank(nacosDomain))
	{
		throw NacosException(0, "no server available");
	}

	String errmsg;
	if (!servers.empty())
	{
		size_t maxSvrSlot = servers.size();
		srand(time(NULL));
		size_t selectedServer = rand() % maxSvrSlot;

		for (size_t i = 0; i < servers.size(); i++)
		{
			String server = ParamUtils::getNthElem(servers, selectedServer);
			try
			{
				return callServer(api, params, server, method);
			}
			catch (NacosException e)
			{
				errmsg = e.what();
				log_error("request %s failed.", server.c_str());
			}
			catch (exception e)
			{
				errmsg = e.what();
				log_error("request %s failed.", server.c_str());
			}

			selectedServer = (selectedServer + 1) % servers.size();
		}

		throw NacosException(0, "failed to req API:" + api + " after all servers(" + ParamUtils::Implode(servers) + ") tried: "
		+ errmsg);
	}

	for (int i = 0; i < UtilAndComs::REQUEST_DOMAIN_RETRY_COUNT; i++)
	{
		try
		{
			return callServer(api, params, nacosDomain);
		}
		catch (exception e)
		{
			errmsg = e.what();
			log_error("[NA] req api:%s failed, server(%s), e = %s", api.c_str(), nacosDomain.c_str(), e.what());
		}
	}

	throw NacosException(0, "failed to req API:/api/" + api + " after all servers(" + ParamUtils::Implode(servers) + ") tried: " + errmsg);
}

String NamingProxy::callServer
(
	const String &api,
	map<String, String> &params,
	const String &curServer
) throw (NacosException)
{
	return callServer(api, params, nacosDomain, HTTPCli::GET);
}

String NamingProxy::callServer
(
	const String &api,
	map<String, String> &params,
	const String &curServer,
	int method
) throw (NacosException)
{
	String requestUrl;
	//Current server address doesn't have SERVER_ADDR_IP_SPLITER, which means
	if (!ParamUtils::contains(curServer, UtilAndComs::SERVER_ADDR_IP_SPLITER))
	{
		requestUrl = curServer + UtilAndComs::SERVER_ADDR_IP_SPLITER + serverPort;
	}

	requestUrl = HTTPCli::getPrefix() + requestUrl + api;

	HttpResult requestRes;
	list<String> headers;
	switch (method)
	{
	case HTTPCli::GET:
		requestRes = httpCli->httpGet(requestUrl, headers, params, UtilAndComs::ENCODING, 50000);//TODO:change 50000 to a constant
		break;
	case HTTPCli::POST:
		requestRes = httpCli->httpPost(requestUrl, headers, params, UtilAndComs::ENCODING, 50000);//TODO:change 50000 to a constant
		break;
	case HTTPCli::DELETE:
		requestRes = httpCli->httpDelete(requestUrl, headers, params, UtilAndComs::ENCODING, 50000);//TODO:change 50000 to a constant
		break;
	}

	if (requestRes.code == HTTP_OK)
	{
		return requestRes.content;
	}

	if (requestRes.code == HTTP_NOT_MODIFIED)
	{
		return NULLSTR;
	}
	//TODO:Metrics & Monitoring

	throw NacosException(NacosException::SERVER_ERROR, "failed to req API:" + requestUrl + " code:" + NacosString::valueOf(requestRes.code) + " errormsg:" + requestRes.content);
}

String NamingProxy::getNamespaceId()
{
	return namespaceId;
}

list<String> NamingProxy::builderHeaders()
{
	list<String> headers;
	headers.push_back("Client-Version");
	headers.push_back(UtilAndComs::VERSION);

	headers.push_back("User-Agent");
	headers.push_back(UtilAndComs::VERSION);

	headers.push_back("Accept-Encoding");
	headers.push_back("gzip,deflate,sdch");

	headers.push_back("Connection");
	headers.push_back("Keep-Alive");

	headers.push_back("RequestId");
	headers.push_back(UuidUtils::generateUuid());

	headers.push_back("Request-Module");
	headers.push_back("Naming");
	return headers;
}
