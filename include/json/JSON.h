#ifndef __JSON_H_
#define __JSON_H_
#include <map>
#include "NacosString.h"
#include "naming/BeatInfo.h"

/**
 * JSON
 *
 * @author Liu, Hanyu
 * Adapter from nacos-cpp-cli to a json parser
 */
class JSON {
public:
	static NacosString toJSONString(BeatInfo &beatInfo);
	static NacosString toJSONString(std::map<NacosString, NacosString> &mapinfo);
	static long getLong(const NacosString &jsonString, const NacosString &fieldname);
};


#endif