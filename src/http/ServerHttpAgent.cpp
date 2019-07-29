#include <string.h>
#include "http/ServerHttpAgent.h"
#include "Debug.h"

using namespace std;

NacosString ServerHttpAgent::getEncode() const
{
	return encoding;
}

ServerHttpAgent::ServerHttpAgent
(
	HTTPCli *httpcli,
	const NacosString &_encoding,
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
	const NacosString &_encoding,
	ServerListManager *_svrListMgr,
	const NacosString &_namesp
)
{
	encoding = _encoding;
	httpCli = httpcli;
	svrListMgr = _svrListMgr;
	namesp = _namesp;
}

HttpResult ServerHttpAgent::httpGet
(
	const NacosString &path,
	std::list<NacosString> &headers,
	std::list<NacosString> &paramValues,
	const NacosString &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	NacosString serverAddr = svrListMgr->getCurrentServerAddr();

	NacosString url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpGet Assembled URL:%s\n", url.c_str());

	res = httpCli->httpGet(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}

HttpResult ServerHttpAgent::httpDelete
(
	const NacosString &path,
	std::list<NacosString> &headers,
	std::list<NacosString> &paramValues,
	const NacosString &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	NacosString serverAddr = svrListMgr->getCurrentServerAddr();

	NacosString url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpDelete Assembled URL:%s\n", url.c_str());

	res = httpCli->httpDelete(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}

HttpResult ServerHttpAgent::httpPost
(
	const NacosString &path,
	std::list<NacosString> &headers,
	std::list<NacosString> &paramValues,
	const NacosString &_encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	NacosString serverAddr = svrListMgr->getCurrentServerAddr();

	NacosString url = serverAddr + "/" + path;
	HttpResult res;
	log_debug("httpPost Assembled URL:%s\n", url.c_str());

	res = httpCli->httpPost(url, headers, paramValues, _encoding, readTimeoutMs);
	return res;
}
