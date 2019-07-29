#include "naming/NacosNamingService.h"
#include "utils/NamingUtils.h"
#include "utils/UtilAndComs.h"
#include "PropertyKeyConst.h"


void NacosNamingService::initNamespace(Properties &props)
{
	if (props.count(PropertyKeyConst::NAMESPACE) == 0)//TODO:implement initNamespace
	{
		namesp = UtilAndComs::DEFAULT_NAMESPACE_ID;
	}
	else
	{
		namesp = props[PropertyKeyConst::NAMESPACE];
	}
}

void NacosNamingService::initEndpoint(Properties &properties)
{
    //TODO:implement initEndpoint

}

NacosNamingService::NacosNamingService(Properties &props)
{
	serverList = props[PropertyKeyConst::SERVER_ADDR];

	initNamespace(props);
	initEndpoint(props);
	httpCli = new HTTPCli();
	serverProxy = new NamingProxy(httpCli, namesp, endpoint, serverList);
}

NacosNamingService::~NacosNamingService()
{
	if (httpCli != NULL)
	{
		delete httpCli;
	}
	httpCli = NULL;

	if (serverProxy != NULL)
	{
		delete serverProxy;
	}
	serverProxy = NULL;
}

void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	const NacosString &ip,
	int port
) throw (NacosException)
{
	registerInstance(serviceName, ip, port, Constants::DEFAULT_CLUSTER_NAME);
}

void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	const NacosString &groupName,
	const NacosString &ip,
	int port
) throw (NacosException)
{
	registerInstance(serviceName, groupName, ip, port, Constants::DEFAULT_CLUSTER_NAME);
}

void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	const NacosString &ip,
	int port,
	const NacosString &clusterName
) throw (NacosException)
{
	registerInstance(serviceName, Constants::DEFAULT_GROUP, ip, port, clusterName);
}

void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	const NacosString &groupName,
	const NacosString &ip,
	int port,
	const NacosString &clusterName
) throw (NacosException)
{
	Instance instance;
	instance.ip = ip;
	instance.port = port;
	instance.weight = 1.0D;
	instance.clusterName = clusterName;
	
	registerInstance(serviceName, groupName, instance);
}
void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	Instance instance
) throw (NacosException)
{
	registerInstance(serviceName, Constants::DEFAULT_GROUP, instance);
}

void NacosNamingService::registerInstance
(
	const NacosString &serviceName,
	const NacosString &groupName,
	Instance instance
) throw (NacosException)
{

	//TODO:use a thread to send heartbeat to config server
	/*if (instance.isEphemeral())
	{
		BeatInfo beatInfo = new BeatInfo();
		beatInfo.setServiceName(NamingUtils.getGroupedName(serviceName, groupName));
		beatInfo.setIp(instance.getIp());
		beatInfo.setPort(instance.getPort());
		beatInfo.setCluster(instance.getClusterName());
		beatInfo.setWeight(instance.getWeight());
		beatInfo.setMetadata(instance.getMetadata());
		beatInfo.setScheduled(false);

		beatReactor.addBeatInfo(NamingUtils.getGroupedName(serviceName, groupName), beatInfo);
	}*/

	serverProxy->registerService(NamingUtils::getGroupedName(serviceName, groupName), groupName, instance);
}

void NacosNamingService::deregisterInstance
(
	const NacosString &serviceName,
	const NacosString &groupName,
	Instance instance
) throw (NacosException)
{
	//TODO:beatReactor->removeBeatInfo(NamingUtils.getGroupedName(serviceName, groupName), instance.getIp(), instance.getPort());
	serverProxy->deregisterService(NamingUtils::getGroupedName(serviceName, groupName), instance);
}
