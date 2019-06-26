#include <iostream>
#include <stdlib.h>
#include <list>
#include "utils/ParamUtils.h"
#include "DebugAssertion.h"
#include "Debug.h"

using namespace std;

bool testStringExplode()
{
	cout << "in function testStringExplode" << endl;

	list<String> explodedList;
	String originalContent = "Hello|World|My|Name|Is";
	ParamUtils::Explode(explodedList, originalContent, '|');
	SHOULD_BE_TRUE(explodedList.size() == 5, "Exploding Hello|World|My|Name|Is with separator | should get a list with size 5.");

	return true;
}
