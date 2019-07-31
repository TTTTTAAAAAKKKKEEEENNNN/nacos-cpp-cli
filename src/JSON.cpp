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
	d.SetObject();
	for (map<NacosString, NacosString>::iterator it = mapinfo.begin(); it != mapinfo.end(); it++)
	{
		Value k;
		k.SetString(it->first.c_str(), d.GetAllocator());
		Value v;
		v.SetString(it->second.c_str(), d.GetAllocator());
		d.AddMember(k, v, d.GetAllocator());
	}


	return documentToString(d);
}

void AddKV(Document &d, const NacosString &k, const NacosString &v)
{
	Value k_, v_;
	k_.SetString(k.c_str(), d.GetAllocator());
	v_.SetString(v.c_str(), d.GetAllocator());
	d.AddMember(k_, v_, d.GetAllocator());
}

NacosString JSON::toJSONString(BeatInfo &beatInfo)
{
	Document d;
	d.SetObject();
	AddKV(d, "port", NacosStringOps::valueOf(beatInfo.port));
	AddKV(d, "ip", beatInfo.ip);
	AddKV(d, "weight", NacosStringOps::valueOf(beatInfo.weight));
	AddKV(d, "serviceName", beatInfo.serviceName);
	AddKV(d, "cluster", beatInfo.cluster);
	AddKV(d, "scheduled", NacosStringOps::valueOf(beatInfo.scheduled));
	AddKV(d, "metadata", toJSONString(beatInfo.metadata));
	
	//d["port"] = NacosStringOps::valueOf(beatInfo.port);
	//d["ip"] = beatInfo.ip;
	//d["weight"] = NacosStringOps::valueOf(beatInfo.weight);
	//d["serviceName"] = beatInfo.serviceName;
	//d["cluster"] = beatInfo.cluster;
	//d["scheduled"] = beatInfo.scheduled;
	//d["metadata"] = toJSONString(beatInfo.metadata);
	return documentToString(d);
}

long JSON::getLong(const NacosString &jsonString, const NacosString &fieldname)
{
	Document d;
	d.Parse(jsonString.c_str());
	Value& s = d[fieldname.c_str()];
	return s.GetInt64();
}