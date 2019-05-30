#include <iostream>
#include "Debug.h"
#include "NacosString.h"

using namespace std;

//Use a special variable NULLSTR as null in Java to pass null parameter
//So when passing a null argument to a function, no need to construct a zero-length string (String(""))
void testStringEqual()
{
	cout << "In testStringEqual" << endl;
	String s2 = "";
	String s3 = "Nacos";
	if (isNull(NULLSTR))
	{
		cout << "NULLSTR is null\n" << endl;
	}
	
	if (isNull(s2))
	{
		cout << "s2 is null\n" << endl;
	}
	
	if (isNull(s3))
	{
		cout << "s3 is null\n" << endl;
	}
}