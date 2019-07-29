#ifndef _ALL_IN_ONE_H_
#define _ALL_IN_ONE_H_
#include "http/HTTPCli.h"
#include "NacosString.h"
#include "Debug.h"

#define TEST_ITEM_START {
#define TEST_ITEM(testName, testfn) {(testName), (testfn)},
#define TEST_ITEM_END };

typedef bool (*TESTFN) ();

typedef struct tagTestData
{
	NacosString testName;
	TESTFN testFn;
} TestData;

#define SHOULD_BE_TRUE(assertion, message) \
do \
{ \
	if (!(assertion)) \
	{ \
		cout << (message) << "...:failed" << endl; \
		return false; \
	} \
	cout << (message) << "...:passed" << endl; \
} while(0);

#define SHOULD_BE_FALSE(assertion, message) SHOULD_BE_TRUE(!(assertion), (message))

#define ReleaseResource(x) \
do { \
	if ((x) != NULL) \
		delete (x); \
	x = NULL; \
} while (0)

#endif