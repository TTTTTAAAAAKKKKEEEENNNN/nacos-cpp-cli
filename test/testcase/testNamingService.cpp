#include <iostream>
#include <stdlib.h>
#include "naming/NamingProxy.h"
#include "naming/Instance.h"
#include "Constants.h"
#include "utils/UtilAndComs.h"
#include "http/HTTPCli.h"
#include "DebugAssertion.h"
#include "Debug.h"
#include "NacosString.h"

using namespace std;

bool testNamingProxy()
{
	cout << "in function testNamingProxy" << endl;
	String servers = "127.0.0.1:8848";
	HTTPCli *httpcli = new HTTPCli();
	NamingProxy *namingProxy = new NamingProxy(httpcli, UtilAndComs::DEFAULT_NAMESPACE_ID, NULLSTR/*endpoint*/, servers);
	Instance theinstance;
	theinstance.instanceId = "TestInstance";
	theinstance.ip = "127.0.0.1";
	theinstance.port = 3333;
	theinstance.clusterName = "TestCluster";
	theinstance.serviceName = "TestService";
	namingProxy->registerService("TestServiceName", Constants::DEFAULT_GROUP, theinstance);
	return true;
}

bool testNamingProxyFailOver()
{
	cout << "in function testNamingProxyFailOver" << endl;
}
