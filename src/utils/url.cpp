#include "utils/url.h"
#include <curl/curl.h>

String urlencode(const String & content)
{
	String result;
	CURL *curl = curl_easy_init();
	char *output = NULL;
	if (curl)
	{
		output = curl_easy_escape(curl, content.c_str(), content.length());
	}

	if(output)
	{
		result.assign(output);
		curl_free(output);
	}
	
	curl_easy_cleanup(curl);
	return result;
}

String urldecode(const String & content)
{
	String result;
	CURL *curl = curl_easy_init();
	char *output = NULL;
	if (curl)
	{
		output = curl_easy_unescape(curl, content.c_str(), content.length(), NULL);
	}

	if(output)
	{
		result.assign(output);
		curl_free(output);
	}

	curl_easy_cleanup(curl);
	return result;
}