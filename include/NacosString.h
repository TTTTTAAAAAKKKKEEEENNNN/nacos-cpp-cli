#ifndef __NACOS_STRING_H_
#define __NACOS_STRING_H_
#include <string>
#include <sstream>
#define NacosString std::string
#define NULLSTR NacosStringOps::nullstr
#define isNull NacosStringOps::isNullStr

class NacosStringOps
{
public:
	static const NacosString nullstr;
	static bool isNullStr(const NacosString &str);
	template <typename T>
	static NacosString valueOf(T val)
	{
		std::ostringstream os;
		if (os << val)
		{
			return NacosString(os.str().c_str());
		}

		return NULLSTR;
	}
	static const NacosString TRUE;
	static const NacosString FALSE;
};

#endif
