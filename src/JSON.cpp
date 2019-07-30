#include <iostream>
#include "json/JSON.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "naming/BeatInfo.h"
#include "NacosString.h"


/**
 * JSON
 *
 * @author Liu, Hanyu
 * Adapter from nacos-cpp-cli to a json parser
 */
using namespace std;
using namespace rapidjson;

NacosString documentToString(Document &d)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	NacosString result = buffer.GetString();
	return result;
}

NacosString JSON::toJSONString(map<NacosString, NacosString> &mapinfo)
{
	Document d;
	for (map<NacosString, NacosString>::iterator it = mapinfo.begin(); it != mapinfo.end(); it++)
	{
		d[it->first.c_str()] = it->second.c_str();
	}


	return documentToString(d);
}
 
NacosString JSON::toJSONString(BeatInfo &beatInfo)
{
	Document d;

	d["port"] = NacosStringOps::valueOf(beatInfo.port);
	d["ip"] = beatInfo.ip;
	d["weight"] = NacosStringOps::valueOf(beatInfo.weight);
	d["serviceName"] = beatInfo.serviceName;
	d["cluster"] = beatInfo.cluster;
	d["scheduled"] = beatInfo.scheduled;
	d["metadata"] = toJSONString(beatInfo.metadata);
	return documentToString(d);
}

long JSON::getLong(NacosString &jsonString, NacosString &fieldname)
{
	Document d;
	d.Parse(jsonString.c_str());
	Value& s = d[fieldname];
	return s.GetLong();
}