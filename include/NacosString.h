#ifndef __NACOS_STRING_H_
#define __NACOS_STRING_H_
#include <string>
#include <sstream>
#define String std::string
#define NULLSTR NacosString::nullstr
#define isNull NacosString::isNullStr

class NacosString
{
public:
	static const String nullstr;
	static bool isNullStr(const String &str);
	template <typename T>
	static String valueOf(T val)
	{
		std::ostringstream os;
		if (os << val)
		{
			return String(os.str().c_str());
		}

		return NULLSTR;
	}
	static const String TRUE;
	static const String FALSE;
};

#endif
