#include <iostream>
#include "NacosConfigService.h"
#include "PropertyKeyConst.h"
#include "Debug.h"

using namespace std;

void testGetConfig()
{
	cout << "in function testGetConfig" << endl;
	Properties props;
	props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1:8849";
	NacosConfigService *n = new NacosConfigService(props);
	String ss = "";
	try
	{
		ss = n->getConfig("","", 1000);
	}
	catch (NacosException e)
	{
		cout <<
		"Request failed with curl code:"<<e.errorcode() << endl <<
		"Reason:" << e.what() << endl;
	}

	cout << ss << endl;
	delete n;
	n = NULL;
}

void testGetConfigwithDefaultPort()
{
	cout << "in function testGetConfigwithDefaultPort" << endl;
	Properties props;
	props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1";
	NacosConfigService *n = new NacosConfigService(props);
	String ss = n->getConfig("k","", 1000);
	cout << ss << endl;
	delete n;
	n = NULL;
}

void testInvalidConfig()
{
	cout << "in function testInvalidConfig" << endl;
	Properties props;
	NacosConfigService *n = new NacosConfigService(props);
	String ss = n->getConfig("k","", 1000);
	cout << ss << endl;
	/*HTTPGlobalInit();
	HTTPResponse *resp =
	doSingleShotHttpRequest("http://127.0.0.1:8848/nacos/v1/ns/operator/servers", 0, NULL);
	decreaseRefHTTPResponse(resp);
	HTTPGlobalDeInit();*/
}