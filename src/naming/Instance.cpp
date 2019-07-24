#include "naming/Instance.h"
#include "Debug.h"


String Instance::toString()
{
	return "instanceId:" + instanceId + " ip:" + ip;
	/*int port;
	double weight = 1.0D;
	bool healthy = true;
	bool enabled = true;
	bool ephemeral = true;
	String clusterName;
	String serviceName;
	std::map<String, String> metadata;*/
}