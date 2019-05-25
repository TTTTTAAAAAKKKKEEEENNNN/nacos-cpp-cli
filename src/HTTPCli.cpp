#include <string.h>
#include "HTTPCli.h"
#include "Debug.h"

using namespace std;

static size_t
receiveResponseCallback(
	void *contents,
	size_t size,
	size_t nmemb,
	void *userp
)
{
	size_t realsize = size * nmemb;
	String *strbuf = (String *)userp;

	strbuf->append((char*)contents, realsize);

	return realsize;
}

static size_t receiveHeaderCallback(
	void *contents,
	size_t size,
	size_t nmemb,
	void *userp
)
{
	char *content_s = (char*)contents;
	char *pos = strchr(content_s, ':');
	if (pos != NULL)//Skip status
	{
		std::map<String, String> *respheaders = (std::map<String, String> *)userp;
		String k = String(content_s, pos - content_s);
		String v = String(pos + 1);
		(*respheaders)[k] = v;
	}
	size_t realsize = size * nmemb;
	
	log_debug("Headercontents: %s", (char*)contents);

	return realsize;
}

HTTPCli::HTTPCli()
{
	/* init the curl session */ 
	curlHandle = curl_easy_init();
}

void HTTPCli::HTTPBasicSettings(CURL *curlHandle)
{
	curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, receiveResponseCallback);
	curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, receiveHeaderCallback);
}

String HTTPCli::encodingParams(list<String> &params)
{
	String encodedParms = "";
	for (list<String>::iterator it = params.begin(); it != params.end(); it++)
	{
		if (encodedParms.compare("") != 0)
		{
			encodedParms.append("&");
		}
		encodedParms.append(*it);
		it++;
		encodedParms.append("="+*it);
	}

	return encodedParms;
}

HttpResult HTTPCli::httpGet
(
	const String &path,
	list<String> &headers,
	list<String> &paramValues,
	String &encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	CURLcode curlres;

	String Url = path;
	String encodedParms = encodingParams(paramValues);
	
	if (encodedParms.compare("") != 0)
	{
		Url += "?" + encodedParms;
	}
	log_debug("Assembled URL with parms:%s\n", Url.c_str());
	
	/* specify URL to get */ 
	curl_easy_setopt(curlHandle, CURLOPT_URL, Url.c_str());

	//Setup common parameters
	HTTPBasicSettings(curlHandle);
	/* send all data to this function  */ 
	String strbuf = "";
	/* we pass our 'strbuf' struct to the callback function */
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void *)&strbuf);
	
	/* Get response headers from the response */
	std::map<String, String> respheaders;
	curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, (void *)&respheaders);
	
	//TODO:Time out in a more precise way
	curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT, readTimeoutMs / 1000);

	/*Add the request headers to the request*/
	struct curl_slist *headerlist = NULL;

	for (list<String>::iterator it = headers.begin(); it != headers.end(); it++)
	{
		headerlist = curl_slist_append(headerlist, it->c_str());
	}
	
	if (headerlist != NULL)
	{
		curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
	}


	/* get it! */ 
	curlres = curl_easy_perform(curlHandle);

	/*Since the headerlist is not needed anymore, free it to prevent mem leak*/
	if (headerlist != NULL)
	{
		curl_slist_free_all(headerlist);
		headerlist = NULL;
	}

	if(curlres != CURLE_OK) {
		log_error("curl_easy_perform() failed: %d - %s\n",
		curlres, curl_easy_strerror(curlres));
		throw NetworkException(curlres, curl_easy_strerror(curlres));
	}
	
	log_debug("%lu bytes retrieved\n", (unsigned long)strbuf.length());
	long response_code;
    curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &response_code);
	HttpResult httpresp = HttpResult(response_code, strbuf, respheaders);
	httpresp.curlcode = curlres;

	return httpresp;
}

HttpResult HTTPCli::httpPost
(
	const String &path,
	list<String> &headers,
	list<String> &paramValues,
	String &encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	CURLcode curlres;

	String Url = path;
	String encodedParms = encodingParams(paramValues);
	
	if (encodedParms.compare("") != 0)
	{
		Url += "?" + encodedParms;
	}
	log_debug("Assembled URL with parms:%s\n", Url.c_str());
	
	/* specify URL to get */ 
	curl_easy_setopt(curlHandle, CURLOPT_URL, Url.c_str());

	curl_easy_setopt(curlHandle, CURLOPT_CUSTOMREQUEST, "POST");
	//Setup common parameters
	HTTPBasicSettings(curlHandle);

	String strbuf = "";
	/* we pass our 'strbuf' struct to the callback function */
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void *)&strbuf);
	
	/* Get response headers from the response */
	std::map<String, String> respheaders;
	curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, (void *)&respheaders);
	
	//TODO:Time out in a more precise way
	curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT, readTimeoutMs / 1000);

	/*Add the request headers to the request*/
	struct curl_slist *headerlist = NULL;

	for (list<String>::iterator it = headers.begin(); it != headers.end(); it++)
	{
		headerlist = curl_slist_append(headerlist, it->c_str());
	}
	
	if (headerlist != NULL)
	{
		curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
	}


	/* get it! */ 
	curlres = curl_easy_perform(curlHandle);

	/*Since the headerlist is not needed anymore, free it to prevent mem leak*/
	if (headerlist != NULL)
	{
		curl_slist_free_all(headerlist);
		headerlist = NULL;
	}

	if(curlres != CURLE_OK) {
		log_error("curl_easy_perform() failed: %d - %s\n",
		curlres, curl_easy_strerror(curlres));
		throw NetworkException(curlres, curl_easy_strerror(curlres));
	}
	
	log_debug("%lu bytes retrieved\n", (unsigned long)strbuf.length());
	long response_code;
    curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &response_code);
	HttpResult httpresp = HttpResult(response_code, strbuf, respheaders);
	httpresp.curlcode = curlres;

	return httpresp;
}

HttpResult HTTPCli::httpDelete
(
	const String &path,
	list<String> &headers,
	list<String> &paramValues,
	String &encoding,
	long readTimeoutMs
) throw (NetworkException)
{
	CURLcode curlres;

	String Url = path;
	String encodedParms = encodingParams(paramValues);
	
	if (encodedParms.compare("") != 0)
	{
		Url += "?" + encodedParms;
	}
	log_debug("Assembled URL with parms:%s\n", Url.c_str());
	
	/* specify URL to get */ 
	curl_easy_setopt(curlHandle, CURLOPT_URL, Url.c_str());
	
	//Setup common parameters
	HTTPBasicSettings(curlHandle);
	/* Set to DELETE, since this is a delete request*/
	curl_easy_setopt(curlHandle, CURLOPT_CUSTOMREQUEST, "DELETE");

	String strbuf = "";
	/* we pass our 'strbuf' struct to the callback function */
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void *)&strbuf);
	
	/* Get response headers from the response */
	std::map<String, String> respheaders;
	curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, (void *)&respheaders);
	
	//TODO:Time out in a more precise way
	curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT, readTimeoutMs / 1000);

	/*Add the request headers to the request*/
	struct curl_slist *headerlist = NULL;

	for (list<String>::iterator it = headers.begin(); it != headers.end(); it++)
	{
		headerlist = curl_slist_append(headerlist, it->c_str());
	}
	
	if (headerlist != NULL)
	{
		curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headerlist);
	}


	/* get it! */ 
	curlres = curl_easy_perform(curlHandle);

	/*Since the headerlist is not needed anymore, free it to prevent mem leak*/
	if (headerlist != NULL)
	{
		curl_slist_free_all(headerlist);
		headerlist = NULL;
	}

	if(curlres != CURLE_OK) {
		log_error("curl_easy_perform() failed: %d - %s\n",
		curlres, curl_easy_strerror(curlres));
		throw NetworkException(curlres, curl_easy_strerror(curlres));
	}
	
	log_debug("%lu bytes retrieved\n", (unsigned long)strbuf.length());
	long response_code;
    curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &response_code);
	HttpResult httpresp = HttpResult(response_code, strbuf, respheaders);
	httpresp.curlcode = curlres;

	return httpresp;
}

HTTPCli::~HTTPCli()
{
	if (curlHandle != NULL)
	{
		curl_easy_cleanup(curlHandle);
		curlHandle = NULL;
	}
}

void HTTPCli::HTTP_GLOBAL_INIT()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

void HTTPCli::HTTP_GLOBAL_DEINIT()
{
	curl_global_cleanup();
}
