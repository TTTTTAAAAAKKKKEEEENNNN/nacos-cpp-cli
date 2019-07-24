#include <math.h>
#include <stdio.h>
#include <sstream>
#include "NacosString.h"

const String NacosString::nullstr = "";
const String NacosString::TRUE = "true";
const String NacosString::FALSE = "false";

//Returns true if str refers to nullstr
bool NacosString::isNullStr(const String &str)
{
	return (&str == &nullstr) || (str == "");
}
