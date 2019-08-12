#include <iostream>
#include "DebugAssertion.h"
#include "init/init.h"

using namespace std;

bool testNormalHttpRequest();
bool testNoServerRequest();
bool testGetConfig();
bool testGetConfigwithDefaultPort();
bool testInvalidConfig();
bool testDebug();
bool testVaArgs();
bool testVaArgs2();
bool testlogPrint();
bool testDeleteConfig();
bool testPublishConfig();
bool testStringEqual();
bool testAddListener();
bool testReadWriteFile();
bool testGetFileSize();
bool testFileExists();
bool testCreateAndRemove();
bool testCleanDirectory();
bool testSaveSnapshot();
bool testCleanTestenvCacheAndGetTestenv();
bool testCleanPrdCacheAndGetPrdenv();
bool testCleanAllCache();
bool testMD5();
bool testURLEncodeAndDecode();
bool testStringExplode();
bool testNamingProxySmokeTest();
bool testNamingServiceRegister();
bool testRapidJsonIntroduce();
bool testSerialize();
bool testThreadSmoke();
bool testThreadPoolSmoke();
bool testString2ServiceInfo();
bool testMalformedJson2ServiceInfo();

TestData testList1[] =
TEST_ITEM_START
TEST_ITEM("Normal http test", testNormalHttpRequest)
TEST_ITEM("No server request, should fail", testNoServerRequest)
TEST_ITEM("Publish config to server", testPublishConfig)
TEST_ITEM("Get config from server", testGetConfig)
TEST_ITEM("Get config from server (with default port)", testGetConfigwithDefaultPort)
TEST_ITEM("Connect the server with invalid config, should throw an exception", testInvalidConfig)
TEST_ITEM("Test printing logs", testDebug)
TEST_ITEM("Test printing logs with va_args", testVaArgs)
TEST_ITEM("Test printing logs with va_args2", testVaArgs2)
TEST_ITEM("Test printing logs", testlogPrint)
TEST_ITEM("Delete config from server", testDeleteConfig)
TEST_ITEM("Test for string characteristics", testStringEqual)
TEST_ITEM("Read&Write file test", testReadWriteFile)
TEST_ITEM("GetFileSize, should work well", testGetFileSize)
TEST_ITEM("Check whether file exists or not", testFileExists)
TEST_ITEM("Create&Remove file", testCreateAndRemove)
TEST_ITEM("Create a directory with subdirectories, and clean it", testCleanDirectory)
TEST_ITEM("Save snapshot", testSaveSnapshot)
TEST_ITEM("Save cache in test and prod env, then clean test env, should only get config from prod env", testCleanTestenvCacheAndGetTestenv)
TEST_ITEM("Save cache in test and prod env, then clean prod env, should only get config from test env", testCleanPrdCacheAndGetPrdenv)
TEST_ITEM("Save cache in test and prod env, then clean all, should not get any data", testCleanAllCache)
TEST_ITEM("Test MD5", testMD5)
TEST_ITEM("Test urlencode/urldecode of libcurl", testURLEncodeAndDecode)
TEST_ITEM("Test explode function", testStringExplode)
TEST_ITEM("Test Listener function for nacos", testAddListener)
TEST_ITEM("Test basic function of NamingProxy's registerService", testNamingProxySmokeTest)
TEST_ITEM("Check whether rapidjson is introduced into the project successfully", testRapidJsonIntroduce)
TEST_ITEM("Check if the serialization succeeds", testSerialize)
TEST_ITEM("Smoke test for Thread", testThreadSmoke)
TEST_ITEM("Smoke test for ThreadPool", testThreadPoolSmoke)
TEST_ITEM("Test basic function of NacosNamingService's registerService", testNamingServiceRegister)
TEST_ITEM_END

TestData testList[] =
TEST_ITEM_START
TEST_ITEM("Test serialization/deserialization of Business Object", testString2ServiceInfo)
TEST_ITEM("Test serialization/deserialization of malformed Business Object", testMalformedJson2ServiceInfo)
TEST_ITEM_END

int main()
{
	Init::doInit();
	for (size_t i = 0; i < sizeof(testList) / sizeof(TestData); i++)
	{
		cout << "===========================" << endl;
		TestData *curtest = &testList[i];
		TESTFN testfunction = curtest->testFn;
		cout << "Testing " << curtest->testName << " ..." << endl;
		bool pass = testfunction();
		if (!pass)
		{
			cout << "FAILED" << endl;
		}
		else
		{
			cout << "PASSED!" << endl;
		}
	}
	cout << "===========================" << endl;

	Init::doDeinit();
	return 0;
}