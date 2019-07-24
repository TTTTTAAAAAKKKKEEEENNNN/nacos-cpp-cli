#ifndef __NAMING_PROXY_H_
#define __NAMING_PROXY_H_
#include <map>
#include <list>
#include "NacosString.h"
#include "NacosExceptions.h"
#include "http/HTTPCli.h"
#include "naming/Instance.h"

class NamingProxy
{
private:
	HTTPCli *httpCli = NULL;
	NamingProxy();
    String reqAPI(const String &api, std::map<String, String> &params, int method) throw (NacosException);
	String reqAPI(const String &api, std::map<String, String> &params, std::list<String> &servers, int method) throw (NacosException);
	String callServer(const String &api, std::map<String, String> &params, const String &curServer, int method) throw (NacosException);
	String callServer(const String &api, std::map<String, String> &params, const String &curServer) throw (NacosException);
	std::list<String> builderHeaders();
	String serverPort;
	String nacosDomain;
	String namespaceId;
	String endpoint;
	std::list<String> serverList;
public:
	NamingProxy(HTTPCli *httpcli, const String &namespaceId, const String &endpoint, const String &serverList);
	~NamingProxy();
	void registerService(const String &serviceName, const String &groupName, Instance instance) throw (NacosException);
	void deregisterService(const String &serviceName, Instance instance) throw (NacosException);
	String getNamespaceId();
};

#endif
