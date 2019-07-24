#include <string.h>
#include "http/ServerHttpAgent.h"
#include "Debug.h"

using namespace std;

String ServerHttpAgent::getEncode() const
{
	return encoding;
}

ServerHttpAgent::ServerHttpAgent
(
	HTTPCli *httpcli,
	const String &_encoding,
	ServerListManager *_svrListMgr
)
{
	encoding = _encoding;
	httpCli = httpcli;
	svrListMgr = svrListMgr;
}

ServerHttpAgent::ServerHttpAgent
(
	HTTPCli *httpcli,
	const String &_encoding,
	ServerListManager *_svrListMgr,
	const String &_namesp
)
{
	encoding = _encoding;
	httpCli = httpcli;
	svrListMgr = _svrListMgr;
	namesp = _namesp;
}

HttpResult ServerHttpAgent::httpGet
(
	const String &path,
	std::list<String> &headers,
	std::list<String> &paramValues,
	const String &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	String serverAddr = svrListMgr->getCurrentServerAddr();

	String url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpGet Assembled URL:%s\n", url.c_str());

	res = httpCli->httpGet(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}

HttpResult ServerHttpAgent::httpDelete
(
	const String &path,
	std::list<String> &headers,
	std::list<String> &paramValues,
	const String &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	String serverAddr = svrListMgr->getCurrentServerAddr();

	String url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpDelete Assembled URL:%s\n", url.c_str());

	res = httpCli->httpDelete(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}

HttpResult ServerHttpAgent::httpPost
(
	const String &path,
	std::list<String> &headers,
	std::list<String> &paramValues,
	const String &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	String serverAddr = svrListMgr->getCurrentServerAddr();

	String url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpPost Assembled URL:%s\n", url.c_str());

	res = httpCli->httpPost(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}
