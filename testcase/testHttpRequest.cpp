#include "HTTPCli.h"
#include "Debug.h"
#include <iostream>
using namespace std;
#define DEFAULT_ENCODING "UTF-8"

void testNormalHttpRequest()
{
	cout << "in function testNormalHttpRequest" << endl;
	String path = "http://127.0.0.1:8848/nacos/v1/ns/operator/servers";
	String ENCODING = DEFAULT_ENCODING;
	std::list<String> headers;
	std::list<String> paramValues;
	HTTPCli httpcli;
	HttpResult callres;
	try
	{
		callres	= httpcli.httpGet(path,
			headers,
			paramValues,
			ENCODING,
			1000);
	}
	catch (NetworkException e)
	{
		cout <<
		"Request failed with curl code:"<<e.errorcode() << endl <<
		"Reason:" << e.what() << endl;
	}
	
	cout << "Http Request returned with code:" << callres.code << endl;
	cout << "Headers:" << endl;
	
	for (std::map<String, String >::iterator it = callres.headers.begin();
		it != callres.headers.end(); ++it)
	{
		cout << it->first << ":" << it->second << endl;
	}
	
	cout << "Content:" << callres.content << endl;
}

void testNoServerRequest()
{
	cout << "in function testNoServerRequest" << endl;
	String path = "http://127.0.0.1:9999/nacos/v1/ns/operator/servers";
	String ENCODING = DEFAULT_ENCODING;
	std::list<String> headers;
	std::list<String> paramValues;
	HTTPCli httpcli;
	HttpResult callres;
	try
	{
		callres	= httpcli.httpGet(path,
			headers,
			paramValues,
			ENCODING,
			1000);
	}
	catch (NetworkException e)
	{
		cout <<
		"Request failed with curl code:"<<e.errorcode() << endl <<
		"Reason:" << e.what() << endl;
	}
	
	cout << "Http Request returned with code:" << callres.code << endl;
	cout << "Headers:" << endl;
	
	for (std::map<String, String >::iterator it = callres.headers.begin();
		it != callres.headers.end(); ++it)
	{
		cout << it->first << ":" << it->second << endl;
	}
	
	cout << "Content:" << callres.content << endl;
}