#ifndef __HTTP_CLI_H_
#define __HTTP_CLI_H_

#include <list>
#include <map>
#include <pthread.h>
#include <curl/curl.h>
#include "NacosString.h"
#include "NacosExceptions.h"

class HttpResult {
public:
	long code;
	String content;
	std::map< String, String > headers;
	CURLcode curlcode;
	HttpResult(long _code, const String &_content, std::map< String, String > &_headers)
	: code(_code), content(_content)
	{
		headers.insert(_headers.begin(), _headers.end());
	}
	
	HttpResult(long _code, const String &_content): code(_code), content(_content) {}
	HttpResult() { code = -1; content.assign(""); headers.clear(); }
	
	HttpResult operator = (HttpResult asignee)
	{
		if (this != &asignee)
		{
			headers.insert(asignee.headers.begin(), asignee.headers.end());
			code = asignee.code;
			content = asignee.content;
			curlcode = asignee.curlcode;
		}

		return *this;
	}
};

class HTTPCli
{
private:
	//CURL *curlHandle;
	pthread_key_t pthreadKey;

	CURL *getCurlHandle();
	static void destroyCurlHandle(void* arg);
public:
	static String encodingParams(std::list<String> &params);
	static void assembleHeaders(std::list<String> &assembledHeaders, std::list<String> &headers);
	static void HTTPBasicSettings(CURL *curlHandle);
	static void HTTP_GLOBAL_INIT();
	static void HTTP_GLOBAL_DEINIT();
	HTTPCli();
	~HTTPCli();
	HttpResult httpGet(
		const String &path,
		std::list<String> &headers,
		std::list<String> &paramValues,
		const String &encoding,
		long readTimeoutMs
	) throw (NetworkException);
	HttpResult httpDelete(
		const String &path,
		std::list<String> &headers,
		std::list<String> &paramValues,
		const String &encoding,
		long readTimeoutMs
	) throw (NetworkException);
	HttpResult httpPost(
		const String &path,
		std::list<String> &headers,
		std::list<String> &paramValues,
		const String &encoding,
		long readTimeoutMs
	) throw (NetworkException);
};

#endif