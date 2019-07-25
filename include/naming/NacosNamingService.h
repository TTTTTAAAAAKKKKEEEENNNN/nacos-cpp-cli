#ifndef __NACOS_NAM_SVC_H_
#define __NACOS_NAM_SVC_H_
#include "naming/NamingService.h"
#include "naming/Instance.h"
#include "naming/NamingProxy.h"
#include "http/HTTPCli.h"
#include "NacosString.h"
#include "Properties.h"

class NacosNamingService : public NamingService
{
private:
	HTTPCli *httpCli;
    NamingProxy *serverProxy;
    //TODO: add BeatReactor *beatReactor;
	NacosNamingService();
	String namesp;

	String endpoint;

	String serverList;

	String cacheDir;

	String logName;

	//HostReactor hostReactor;

	//EventDispatcher eventDispatcher;

	void initNamespace(Properties &props);
	void initEndpoint(Properties &properties);
public:
	NacosNamingService(Properties &props);
	void registerInstance(const String &serviceName, Instance instance) throw (NacosException);
	void registerInstance(const String &serviceName, const String &groupName, Instance instance) throw (NacosException);
	void deregisterInstance(const String &serviceName, const String &groupName, Instance instance) throw (NacosException);
};

#endif
