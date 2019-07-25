#ifndef __NAM_SVC_H_
#define __NAM_SVC_H_
#include "naming/NamingService.h"
#include "naming/Instance.h"
#include "NacosString.h"
#include "NacosExceptions.h"

class NamingService
{
public:
	/**
	 * register a instance to service
	 *
	 * @param serviceName name of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @throw (NacosException) = 0
	 */
	//virtual void registerInstance(const String &serviceName, const String &ip, int port) throw (NacosException) = 0;

	/**
	 * register a instance to service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @throw (NacosException) = 0
	 */
	//virtual void registerInstance(const String &serviceName, const String &groupName, const String &ip, int port) throw (NacosException) = 0;

	/**
	 * register a instance to service with specified cluster name
	 *
	 * @param serviceName name of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @param clusterName instance cluster name
	 * @throw (NacosException) = 0
	 */
	//virtual void registerInstance(const String &serviceName, const String &ip, int port, const String &clusterName) throw (NacosException) = 0;

	/**
	 * register a instance to service with specified cluster name
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @param clusterName instance cluster name
	 * @throw (NacosException) = 0
	 */
	//virtual void registerInstance(const String &serviceName, const String &groupName, const String &ip, int port, const String &clusterName) throw (NacosException) = 0;

	/**
	 * register a instance to service with specified instance properties
	 *
	 * @param serviceName name of service
	 * @param instance    instance to register
	 * @throw (NacosException) = 0
	 */
	virtual void registerInstance(const String &serviceName, Instance instance) throw (NacosException) = 0;

	/**
	 * register a instance to service with specified instance properties
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param instance    instance to register
	 * @throw (NacosException) = 0
	 */
	virtual void registerInstance(const String &serviceName, const String &groupName, Instance instance) throw (NacosException) = 0;

	/**
	 * deregister instance from a service
	 *
	 * @param serviceName name of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @throw (NacosException) = 0
	 */
	//virtual void deregisterInstance(const String &serviceName, const String &ip, int port) throw (NacosException) = 0;

	/**
	 * deregister instance from a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @throw (NacosException) = 0
	 */
	//virtual void deregisterInstance(const String &serviceName, const String &groupName, const String &ip, int port) throw (NacosException) = 0;

	/**
	 * deregister instance with specified cluster name from a service
	 *
	 * @param serviceName name of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @param clusterName instance cluster name
	 * @throw (NacosException) = 0
	 */
	//virtual void deregisterInstance(const String &serviceName, const String &ip, int port, const String &clusterName) throw (NacosException) = 0;

	/**
	 * deregister instance with specified cluster name from a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param ip          instance ip
	 * @param port        instance port
	 * @param clusterName instance cluster name
	 * @throw (NacosException) = 0
	 */
	//virtual void deregisterInstance(const String &serviceName, const String &groupName, const String &ip, int port, const String &clusterName) throw (NacosException) = 0;

	/**
	 * deregister instance with full instance information
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param instance    instance information
	 * @throw (NacosException) = 0
	 */
	virtual void deregisterInstance(const String &serviceName, const String &groupName, Instance instance) throw (NacosException) = 0;

	/**
	 * get all instances of a service
	 *
	 * @param serviceName name of service
	 * @return A list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName) throw (NacosException) = 0;

	/**
	 * get all instances of a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @return A list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, const String &groupName) throw (NacosException) = 0;

	/**
	 * Get all instances of a service
	 *
	 * @param serviceName name of service
	 * @param subscribe   if subscribe the service
	 * @return A list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get all instances of a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param subscribe   if subscribe the service
	 * @return A list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, const String &groupName, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get all instances within specified clusters of a service
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @return A list of qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, std::list<String> clusters) throw (NacosException) = 0;

	/**
	 * Get all instances within specified clusters of a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @return A list of qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, const String &groupName, std::list<String> clusters) throw (NacosException) = 0;

	/**
	 * Get all instances within specified clusters of a service
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @param subscribe   if subscribe the service
	 * @return A list of qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, std::list<String> clusters, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get all instances within specified clusters of a service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @param subscribe   if subscribe the service
	 * @return A list of qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> getAllInstances(const String &serviceName, const String &groupName, std::list<String> clusters, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get qualified instances of service
	 *
	 * @param serviceName name of service
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, bool healthy) throw (NacosException) = 0;

	/**
	 * Get qualified instances of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, const String &groupName, bool healthy) throw (NacosException) = 0;

	/**
	 * Get qualified instances of service
	 *
	 * @param serviceName name of service
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @param subscribe   if subscribe the service
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, bool healthy, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get qualified instances of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @param subscribe   if subscribe the service
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, const String &groupName, bool healthy, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get qualified instances within specified clusters of service
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, std::list<String> clusters, bool healthy) throw (NacosException) = 0;

	/**
	 * Get qualified instances within specified clusters of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, const String &groupName, std::list<String> clusters, bool healthy) throw (NacosException) = 0;

	/**
	 * Get qualified instances within specified clusters of service
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @param subscribe   if subscribe the service
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, std::list<String> clusters, bool healthy, bool subscribe) throw (NacosException) = 0;

	/**
	 * Get qualified instances within specified clusters of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @param healthy     a flag to indicate returning healthy or unhealthy instances
	 * @param subscribe   if subscribe the service
	 * @return A qualified list of instance
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<Instance> selectInstances(const String &serviceName, const String &groupName, std::list<String> clusters, bool healthy, bool subscribe) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, const String &groupName) throw (NacosException) = 0;

	/**
	 * select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param subscribe   if subscribe the service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, bool subscribe) throw (NacosException) = 0;

	/**
	 * select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param subscribe   if subscribe the service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, const String &groupName, bool subscribe) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param clusters    a list of clusters should the instance belongs to
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, std::list<String> clusters) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    a list of clusters should the instance belongs to
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, const String &groupName, std::list<String> clusters) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param clusters    a list of clusters should the instance belongs to
	 * @param subscribe   if subscribe the service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, std::list<String> clusters, bool subscribe) throw (NacosException) = 0;

	/**
	 * Select one healthy instance of service using predefined load balance strategy
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    a list of clusters should the instance belongs to
	 * @param subscribe   if subscribe the service
	 * @return qualified instance
	 * @throw (NacosException) = 0
	 */
	//virtual Instance selectOneHealthyInstance(const String &serviceName, const String &groupName, std::list<String> clusters, bool subscribe) throw (NacosException) = 0;

	/**
	 * Subscribe service to receive events of instances alteration
	 *
	 * @param serviceName name of service
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void subscribe(const String &serviceName, EventListener listener) throw (NacosException) = 0;

	/**
	 * Subscribe service to receive events of instances alteration
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void subscribe(const String &serviceName, const String &groupName, EventListener listener) throw (NacosException) = 0;

	/**
	 * Subscribe service to receive events of instances alteration
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void subscribe(const String &serviceName, std::list<String> clusters, EventListener listener) throw (NacosException) = 0;

	/**
	 * Subscribe service to receive events of instances alteration
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void subscribe(const String &serviceName, const String &groupName, std::list<String> clusters, EventListener listener) throw (NacosException) = 0;

	/**
	 * Unsubscribe event listener of service
	 *
	 * @param serviceName name of service
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void unsubscribe(const String &serviceName, EventListener listener) throw (NacosException) = 0;

	/**
	 * unsubscribe event listener of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void unsubscribe(const String &serviceName, const String &groupName, EventListener listener) throw (NacosException) = 0;

	/**
	 * Unsubscribe event listener of service
	 *
	 * @param serviceName name of service
	 * @param clusters    list of cluster
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void unsubscribe(const String &serviceName, std::list<String> clusters, EventListener listener) throw (NacosException) = 0;

	/**
	 * Unsubscribe event listener of service
	 *
	 * @param serviceName name of service
	 * @param groupName   group of service
	 * @param clusters    list of cluster
	 * @param listener    event listener
	 * @throw (NacosException) = 0
	 */
	//virtual void unsubscribe(const String &serviceName, const String &groupName, std::list<String> clusters, EventListener listener) throw (NacosException) = 0;

	/**
	 * Get all service names from server
	 *
	 * @param pageNo   page index
	 * @param pageSize page size
	 * @return list of service names
	 * @throw (NacosException) = 0
	 */
	//virtual ListView<String> getServicesOfServer(int pageNo, int pageSize) throw (NacosException) = 0;

	/**
	 * Get all service names from server
	 *
	 * @param pageNo    page index
	 * @param pageSize  page size
	 * @param groupName group name
	 * @return list of service names
	 * @throw (NacosException) = 0
	 */
	//virtual ListView<String> getServicesOfServer(int pageNo, int pageSize, const String &groupName) throw (NacosException) = 0;

	/**
	 * Get all service names from server with selector
	 *
	 * @param pageNo   page index
	 * @param pageSize page size
	 * @param selector selector to filter the resource
	 * @return list of service names
	 * @throw (NacosException) = 0
	 * @since 0.7.0
	 */
	//virtual ListView<String> getServicesOfServer(int pageNo, int pageSize, AbstractSelector selector) throw (NacosException) = 0;

	/**
	 * Get all service names from server with selector
	 *
	 * @param pageNo    page index
	 * @param pageSize  page size
	 * @param groupName group name
	 * @param selector  selector to filter the resource
	 * @return list of service names
	 * @throw (NacosException) = 0
	 */
	//virtual ListView<String> getServicesOfServer(int pageNo, int pageSize, const String &groupName, AbstractSelector selector) throw (NacosException) = 0;

	/**
	 * Get all subscribed services of current client
	 *
	 * @return subscribed services
	 * @throw (NacosException) = 0
	 */
	//virtual std::list<ServiceInfo> getSubscribeServices() throw (NacosException) = 0;

	/**
	 * get server health status
	 *
	 * @return is server healthy
	 */
	//virtual String getServerStatus() = 0;
	
	virtual ~NamingService();
};

#endif