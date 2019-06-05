#include <iostream>
#include "NacosConfigService.h"
#include "PropertyKeyConst.h"
#include "DebugAssertion.h"
#include "Debug.h"

using namespace std;

bool testGetConfig()
{
	cout << "in function testGetConfig" << endl;
	Properties props;
	props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1:8848";
	NacosConfigService *n = new NacosConfigService(props);
	String ss = "";
	try
	{
		ss = n->getConfig("k", NULLSTR, 1000);
	}
	catch (NacosException e)
	{
		cout <<
		"Request failed with curl code:"<<e.errorcode() << endl <<
		"Reason:" << e.what() << endl;
		ReleaseResource(n);
		return false;
	}
	cout << ss << endl;

	ReleaseResource(n);
	return true;
}

bool testGetConfigwithDefaultPort()
{
	cout << "in function testGetConfigwithDefaultPort" << endl;
	Properties props;
	props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1";
	NacosConfigService *n = new NacosConfigService(props);
	String ss = n->getConfig("k", NULLSTR, 1000);
	cout << ss << endl;

	ReleaseResource(n);
	return true;
}

bool testInvalidConfig()
{
	cout << "in function testInvalidConfig" << endl;
	Properties props;
	NacosConfigService *n = NULL;
	
	String ss;
	try
	{
		n = new NacosConfigService(props);
		ss = n->getConfig("k", NULLSTR, 1000);
	}
	catch (NacosException e)
	{
		String errmsgShouldBe = "endpoint is blank";
		if (errmsgShouldBe == e.what())
		{
			ReleaseResource(n);
			return true;
		}
		else
		{
			ReleaseResource(n);
			return false;
		}
	}
	cout << ss << endl;

	ReleaseResource(n);
	return false;
}