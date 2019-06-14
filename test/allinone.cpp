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
TEST_ITEM_END

TestData testList[] =
TEST_ITEM_START
//TEST_ITEM("Test Listener function for nacos", testAddListener)
//TEST_ITEM("Read&Write file test", testReadWriteFile)
//TEST_ITEM("GetFileSize, should work well", testGetFileSize)
//TEST_ITEM("Check whether file exists or not", testFileExists)
TEST_ITEM("Create&Remove file", testCreateAndRemove)
TEST_ITEM_END

int main()
{
	Init::doInit();
	for (size_t i = 0; i < sizeof(testList) / sizeof(TestData); i++)
	{
		cout << "===========================" << endl;
		TestData *curtest = &testList[i];
		TESTFN testfunction = curtest->testFn;
		cout << "Testing " << curtest->testName << " ...";
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