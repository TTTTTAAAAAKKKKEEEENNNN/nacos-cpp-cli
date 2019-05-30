#include "HTTPCli.h"
#include "Debug.h"

void testNormalHttpRequest();
void testNoServerRequest();
void testGetConfig();
void testGetConfigwithDefaultPort();
void testInvalidConfig();
void testDebug();
void testVaArgs();
void testVaArgs2();
void testlogPrint();
void testDeleteConfig();
void testPublishConfig();
void testStringEqual();

int main()
{
	Debug::set_debug_level(DEBUG);
	HTTPCli::HTTP_GLOBAL_INIT();
	testStringEqual();
	testlogPrint();
	testDebug();
	testVaArgs();
	testVaArgs2();

	testPublishConfig();
	testDeleteConfig();
	testNormalHttpRequest();
	testNoServerRequest();
	testGetConfig();
	testGetConfigwithDefaultPort();
	testInvalidConfig();

	HTTPCli::HTTP_GLOBAL_DEINIT();
	return 0;
}