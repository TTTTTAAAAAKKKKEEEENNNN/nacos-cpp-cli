#ifndef __SVR_HTTP_AGENT_H_
#define __SVR_HTTP_AGENT_H_
#include "NacosExceptions.h"
#include "NacosString.h"
#include "http/HTTPCli.h"
#include "http/HttpAgent.h"
#include "ServerListManager.h"

/**
 * ServerHttpAgent
 *
 * @author Liu, Hanyu
 */
class ServerHttpAgent : public HttpAgent
{
private:
	//Variables
	String namesp;
	String encoding;
	HTTPCli *httpCli = NULL;
	ServerListManager *svrListMgr = NULL;
public:
	ServerHttpAgent(HTTPCli *httpcli, const String &_encoding, ServerListManager *_svrListMgr, const String &_namesp);
	ServerHttpAgent(HTTPCli *httpcli, const String &encoding, ServerListManager *_svrListMgr);
	HttpResult httpGet(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException);
	HttpResult httpPost(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException);
	HttpResult httpDelete(const String &path, std::list<String> &headers, std::list<String> &paramValues, const String &encoding, long readTimeoutMs) throw (NetworkException);
	String getEncode() const;
	virtual ~ServerHttpAgent() { httpCli = NULL; svrListMgr = NULL; };
};

#endif