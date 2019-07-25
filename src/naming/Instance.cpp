#include "naming/Instance.h"
#include "utils/ParamUtils.h"
#include "Debug.h"

Instance::Instance()
{
	weight = 1.0D;
	healthy = true;
	enabled = true;
	ephemeral = true;
}

String Instance::toString()
{
	return "instanceId:" + instanceId + " ip:" + ip + " port:" + NacosString::valueOf(port) +
	" weight:" + NacosString::valueOf(weight) + " healthy:" + NacosString::valueOf(healthy) +
	" enabled:" + NacosString::valueOf(enabled) + " ephemeral:" + NacosString::valueOf(ephemeral) +
	" clusterName:" + clusterName + " serviceName:" + serviceName + " metadata:{" + ParamUtils::Implode(metadata) + "}";
}
