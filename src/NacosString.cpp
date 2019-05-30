#include "NacosString.h"
const String NacosString::nullstr = "";

//Returns true if str refers to nullstr
bool NacosString::isNullStr(const String &str)
{
	return &str == &nullstr;
}