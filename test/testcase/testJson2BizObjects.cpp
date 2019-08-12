#include <iostream>
#include "DebugAssertion.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "naming/beat/BeatInfo.h"
#include "json/JSON.h"

using namespace std;

bool testString2ServiceInfo()
{
	cout << "in function testString2ServiceInfo" << endl;
	const char* json =
	"{"
	"	\"dom\": \"nacos.test.1\","
	"	\"cacheMillis\": 1000,"
	"	\"useSpecifiedURL\": false,"
	"	\"hosts\": [{"
	"		\"valid\": true,"
	"		\"marked\": false,"
	"		\"instanceId\": \"10.10.10.10-8888-DEFAULT-nacos.test.1\","
	"		\"port\": 8888,"
	"		\"ip\": \"10.10.10.10\","
	"		\"weight\": 1.0,"
	"		\"metadata\": {}"
	"	}],"
	"	\"checksum\": \"3bbcf6dd1175203a8afdade0e77a27cd1528787794594\","
	"	\"lastRefTime\": 1528787794594,"
	"	\"env\": \"\","
	"	\"clusters\": \"\""
	"}";
	
	cout << "Deserializing the following string into an object:"<< endl << json << endl;
	ServiceInfo si = JSON::JsonStr2ServiceInfo(json);
	
	SHOULD_BE_TRUE(si.getHosts().size() == 1, "There is 1 host in the json object");
	SHOULD_BE_TRUE(si.getClusters() == "", "obj.cluster == \"\"");
	Instance i = si.getHosts().front();
	SHOULD_BE_TRUE(i.instanceId == "10.10.10.10-8888-DEFAULT-nacos.test.1", "The first instance's ID is 10.10.10.10-8888-DEFAULT-nacos.test.1");
	return true;
}

bool testMalformedJson2ServiceInfo()
{
	cout << "in function testMalformedJson2ServiceInfo" << endl;
	const char* json =
	"{"
	"	\"dom\": \"nacos.test.1\","
	"	\"cacheMillis\": 1000,"
	"	\"useSpecifiedURL\": false,"
	"	\"hosts\": [{"
	"		\"valid\": true,"
	"		\"marked\": false,"
	"		\"instanceId\": \"10.10.10.10-8888-DEFAULT-nacos.test.1\","
	"		\"port\": 8888,"
	"		\"ip\": \"10.10.10.10\","
	"		\"weight\": 1.0,"
	"		\"metadata\": {}"
	"	}],"
	"	\"checksum\": \"3bbcf6dd1175203a8afdade0e77a27cd1528787794594\","
	"	\"lastRefTime\": 152878779459499999999999999999999999999999999999999,"
	"	\"env\": \"\","
	"	\"clusters\": \"\""
	"}";
	
	cout << "Deserializing the following string into an object:"<< endl << json << endl;
	ServiceInfo si;
	try
	{
		si = JSON::JsonStr2ServiceInfo(json);
	}
	catch (...)
	{
		cout << "Caught exception" << endl;
	}
	SHOULD_BE_TRUE(si.getHosts().size() == 1, "There is 1 host in the json object");
	SHOULD_BE_TRUE(si.getClusters() == "", "obj.cluster == \"\"");
	Instance i = si.getHosts().front();
	SHOULD_BE_TRUE(i.instanceId == "10.10.10.10-8888-DEFAULT-nacos.test.1", "The first instance's ID is 10.10.10.10-8888-DEFAULT-nacos.test.1");
	return true;
}