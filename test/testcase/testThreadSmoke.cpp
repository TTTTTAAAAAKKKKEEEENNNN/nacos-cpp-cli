#include <iostream>
#include "DebugAssertion.h"
#include "Debug.h"
#include "Thread.h"

void threadfn()
{
	log_info("Hello from threadfn\n");
}

bool testThreadSmoke()
{
	Thread t("testThread", threadfn);
	t.start();
	t.join();
	return true;
}