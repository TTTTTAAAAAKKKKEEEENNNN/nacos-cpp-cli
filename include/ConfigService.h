#ifndef __CFG_SVC_H_
#define __CFG_SVC_H_
#include "NacosExceptions.h"
#include "NacosString.h"
#include "listen/Listener.h"

class ConfigService
{
public:
	/**
	 * Get config
	 *
	 * @param dataId    dataId
	 * @param group     group
	 * @param timeoutMs read timeout
	 * @return config value
	 * @throws NacosException NacosException
	 */
	virtual String getConfig(const String &dataId, const String &group, long timeoutMs) throw(NacosException) = 0;

	/**
	 * Add a listener to the configuration, after the server modified the
	 * configuration, the client will use the incoming listener callback.
	 * Recommended asynchronous processing, the application can implement the
	 * getExecutor method in the ManagerListener, provide a thread pool of
	 * execution. If provided, use the main thread callback, May block other
	 * configurations or be blocked by other configurations.
	 *
	 * @param dataId   dataId
	 * @param group    group
	 * @param listener listener
	 * @throws NacosException NacosException
	 */
	virtual void addListener(const String &dataId, const String &group, Listener *listener) throw(NacosException) = 0;

	/**
	 * Publish config.
	 *
	 * @param dataId  dataId
	 * @param group   group
	 * @param content content
	 * @return Whether publish
	 * @throws NacosException NacosException
	 */
	virtual bool publishConfig(const String &dataId, const String &group, const String &content) throw(NacosException) = 0;

	/**
	 * Remove config
	 *
	 * @param dataId dataId
	 * @param group  group
	 * @return whether remove
	 * @throws NacosException NacosException
	 */
	virtual bool removeConfig(const String &dataId, const String &group) throw(NacosException) = 0;

	/**
	 * Remove listener
	 *
	 * @param dataId   dataId
	 * @param group    group
	 * @param listener listener
	 */
	//virtual void removeListener(String dataId, String group, Listener listener) = 0;

	/**
	 * Get server status
	 *
	 * @return whether health
	 */
	//virtual String getServerStatus() = 0;

	virtual ~ConfigService() {};
};

#endif