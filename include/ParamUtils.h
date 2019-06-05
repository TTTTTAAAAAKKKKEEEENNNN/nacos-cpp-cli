#ifndef __PARMUTILS_H_
#define __PARMUTILS_H_
#include <map>
#include "NacosString.h"
#include "NacosExceptions.h"

class ParamUtils
{
public:
	static bool isBlank(const String &content)
	{
		//TODO:Apply ParamUtils.Java's logic to here, support whitespaces in other countries/zones
		if (content.size() == 0)
		{
			return true;
		}
		
		for (size_t i = 0; i < content.size(); i++)
		{
			switch (content[i])
			{
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					continue;
				default:
					return false;
			}
		}
		
		return true;
	};
	
	static bool isValid(const String &content)
	{
		return false;
	};
	
	static void checkParam(const String &dataId, const String &group, const String &content) throw (NacosException)
	{
		if (isBlank(content))
		{
            throw NacosException(NacosException::CLIENT_INVALID_PARAM, "content invalid");
		}
	};
};

#endif