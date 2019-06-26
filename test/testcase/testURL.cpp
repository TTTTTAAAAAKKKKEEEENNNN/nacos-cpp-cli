#include <iostream>
#include <stdlib.h>
#include "utils/url.h"
#include "DebugAssertion.h"
#include "Debug.h"

using namespace std;

bool testURLEncodeAndDecode()
{
	cout << "in function testURLEncode" << endl;

	String originalContent = "Hello W! orld \\/,.%$@^%#*43543";
	String encoded = urlencode(originalContent);
	cout << "Encoded:" << encoded << endl;
	String decoded = urldecode(encoded);
	SHOULD_BE_TRUE(originalContent == decoded, "After encoding and decoding, the content should remain the same.");

	return true;
}
