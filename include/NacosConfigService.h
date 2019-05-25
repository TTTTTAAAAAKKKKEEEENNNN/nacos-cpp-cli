#ifndef __NACOS_CFG_SVC_H_
#define __NACOS_CFG_SVC_H_
#include "ConfigService.h"
#include "HTTPCli.h"
#include "NacosString.h"
#include "ServerListManager.h"
#include "Properties.h"

class NacosConfigService : public ConfigService
{
private:
	//Variables
	String namesp;
	String encoding;
	HTTPCli *httpcli = NULL;
	ServerListManager *svrListMgr = NULL;

	//Private Methods
	NacosConfigService();
    String getConfigInner(const String &tenant, const String &dataId, const String &group, long timeoutMs) throw(NacosException);
	bool removeConfigInner(const String &tenant, const String &dataId, const String &group, const String &tag) throw(NacosException);
	bool publishConfigInner(const String &tenant, const String &dataId, const String &group, const String &tag, const String &appName, const String &betaIps, const String &content) throw (NacosException);
public:
	const static long POST_TIMEOUT = 3000L;
	//Public Methods
	String getConfig(const String &dataId, const String &group, long timeoutMs) throw (NacosException);
	bool publishConfig(const String &dataId, const String &group, const String &content) throw (NacosException);
	bool removeConfig(const String &dataId, const String &group) throw(NacosException);

	//ctors/dtor
	NacosConfigService(Properties &props) throw (NacosException);
	~NacosConfigService();
};

#endif