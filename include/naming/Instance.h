#ifndef __INSTANCE_H_
#define __INSTANCE_H_
#include <map>
#include "NacosString.h"

class Instance
{
public:
	Instance();
	/**
	* unique id of this instance.
	*/
	String instanceId;

	/**
	* instance ip
	*/
	String ip;

	/**
	* instance port
	*/
	int port;

	/**
	* instance weight
	*/
	double weight;

	/**
	* instance health status
	*/
	bool healthy;

	/**
	* If instance is enabled to accept request
	*/
	bool enabled;

	/**
	* If instance is ephemeral
	*
	* @since 1.0.0
	*/
	bool ephemeral;

	/**
	* cluster information of instance
	*/
	String clusterName;

	/**
	* Service information of instance
	*/
	String serviceName;

	/**
	* user extended attributes
	*/
	std::map<String, String> metadata;

	String toString();
};

#endif