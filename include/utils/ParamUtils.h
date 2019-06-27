#ifndef __PARMUTILS_H_
#define __PARMUTILS_H_
#include <map>
#include <vector>
#include "NacosString.h"
#include "NacosExceptions.h"

using namespace std;

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
	
	//A little trick here
	static void Explode(vector<String> &explodedList, const String &stringToExplode, const String separator)
	{
		Explode(explodedList, stringToExplode, separator.c_str()[0]);
	}

	static void Explode(vector<String> &explodedList, const String &stringToExplode, char separator)
	{
		size_t start_pos = 0;
		size_t cur_pos = 0;
		cur_pos = stringToExplode.find(separator, start_pos);

		//break the string with separator
		while (cur_pos != string::npos)
		{
			String cur_addr = stringToExplode.substr(start_pos, cur_pos - start_pos);
			explodedList.push_back(cur_addr);
			start_pos = cur_pos + 1;
			cur_pos = stringToExplode.find(separator, start_pos);
		}

		//deal with the last string
		String last_addr = stringToExplode.substr(start_pos);
		explodedList.push_back(last_addr);
	}
};

#endif