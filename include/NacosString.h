#ifndef __NACOS_STRING_H_
#define __NACOS_STRING_H_
#include <string>
#define String std::string
#define NULLSTR NacosString::nullstr
#define isNull NacosString::isNullStr

class NacosString
{
public:
	static const String nullstr;
	static bool isNullStr(const String &str);
};

#endif