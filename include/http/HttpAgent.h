#ifndef __HTTP_AGENT_H_
#define __HTTP_AGENT_H_
#include "NacosExceptions.h"
#include "NacosString.h"
#include "http/HTTPCli.h"

/**
 * HttpAgent
 *
 * @author Liu, Hanyu
 */
class HttpAgent
{
public:
	/**
	* start to get nacos ip list
	* @return Nothing.
	* @throws NacosException on get ip list error.
	*/
	//virtual void start() throw (NacosException) = 0;

	/**
	* invoke http get method
	* @param path http path
	* @param headers http headers
	* @param paramValues http paramValues http
	* @param encoding http encode
	* @param readTimeoutMs http timeout
	* @return HttpResult http response
	* @throws NetworkException If an input or output exception occurred
	*/

	virtual HttpResult httpGet(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException) = 0;

	/**
	* invoke http post method
	* @param path http path
	* @param headers http headers
	* @param paramValues http paramValues http
	* @param encoding http encode
	* @param readTimeoutMs http timeout
	* @return HttpResult http response
	* @throws NetworkException If an input or output exception occurred
	*/
	virtual HttpResult httpPost(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException) = 0;

	/**
	* invoke http delete method
	* @param path http path
	* @param headers http headers
	* @param paramValues http paramValues http
	* @param encoding http encode
	* @param readTimeoutMs http timeout
	* @return HttpResult http response
	* @throws NetworkException If an input or output exception occurred
	*/
	virtual HttpResult httpDelete(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException) = 0;

	/**
	* get name
	* @return String
	*/
	//virtual String getName() const;

	/**
	* get namespace
	* @return String
	*/
	//virtual String getNamespace() const;

	/**
	* get tenant
	* @return String
	*/
	//virtual String getTenant() const;

	/**
	* get encode
	* @return String
	*/
	virtual String getEncode() const = 0;
	
	virtual ~HttpAgent() {};
};

#endif