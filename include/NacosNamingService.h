#ifndef __NACOS_NAM_SVC_H_
#define __NACOS_NAM_SVC_H_
#include "NamingService.h"
#include "naming/Instance.h"
#include "NacosString.h"

class NacosNamingService : public NamingService
{
public:
	NacosNamingService();
	void registerService(String serviceName, String groupName, Instance instance) throw (NacosException);
	void deregisterService(String serviceName, Instance instance) throw (NacosException);
};

#endif