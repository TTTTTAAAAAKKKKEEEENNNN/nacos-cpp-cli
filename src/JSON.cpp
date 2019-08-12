#include <iostream>
#include "json/JSON.h"
#include "naming/beat/BeatInfo.h"
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

void JSON::Map2JSONObject(Value &jsonOb, map<NacosString, NacosString> &mapinfo)
{
	Document document;
	jsonOb.SetObject();
	for (map<NacosString, NacosString>::iterator it = mapinfo.begin(); it != mapinfo.end(); it++)
	{
		Value k;
		k.SetString(it->first.c_str(), document.GetAllocator());
		Value v;
		v.SetString(it->second.c_str(), document.GetAllocator());
		jsonOb.AddMember(k, v, document.GetAllocator());
	}
}

void JSON::JSONObject2Map(std::map<NacosString, NacosString> &mapinfo, const Value &jsonOb)
{
	for (Value::ConstMemberIterator iter = jsonOb.MemberBegin(); iter != jsonOb.MemberEnd(); ++iter)
	{
		NacosString name = iter->name.GetString();
		NacosString value = iter->value.GetString();
		mapinfo[name] = value;
	}
}

//Add key-value
void AddKV(Document &d, const NacosString &k, const NacosString &v)
{
	Value k_, v_;
	k_.SetString(k.c_str(), d.GetAllocator());
	v_.SetString(v.c_str(), d.GetAllocator());
	d.AddMember(k_, v_, d.GetAllocator());
}

//Add key-Object
void AddKO(Document &d, const NacosString &k, Value &o)
{
	Value k_;
	k_.SetString(k.c_str(), d.GetAllocator());
	d.AddMember(k_, o, d.GetAllocator());
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
	Value metadata;
	Map2JSONObject(metadata, beatInfo.metadata);
	AddKO(d, "metadata", metadata);
	
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

Instance JSON::Json2Instance(const Value &host)
{
	Instance theinstance;

	const Value &instanceId = host["instanceId"];
	theinstance.instanceId = instanceId.GetString();

	const Value &port = host["port"];
	theinstance.port = port.GetInt();

	const Value &ip = host["ip"];
	theinstance.ip = ip.GetString();

	const Value &weight = host["weight"];
	theinstance.weight = weight.GetDouble();

	const Value &metadata = host["metadata"];

	std::map<NacosString, NacosString> mtdata;
	JSONObject2Map(mtdata, metadata);

	theinstance.metadata = mtdata;

	return theinstance;
}

ServiceInfo JSON::JsonStr2ServiceInfo(const NacosString &jsonString)
{
	ServiceInfo si;
	Document d;
	d.Parse(jsonString.c_str());
	
	const Value &cacheMillis = d["cacheMillis"];
	si.setCacheMillis(cacheMillis.GetInt64());
	
	const Value &checkSum = d["checksum"];
	si.setChecksum(checkSum.GetString());
	
	const Value &lastRefTime = d["lastRefTime"];
	si.setLastRefTime(lastRefTime.GetInt64());
	
	const Value &clusters = d["clusters"];
	si.setClusters(clusters.GetString());

	const Value &hosts = d["hosts"];
	std::list<Instance> hostlist;
	for (SizeType i = 0; i < hosts.Size(); i++)
	{
		const Value &curhost = hosts[i];
		Instance curinstance = Json2Instance(curhost);
		hostlist.push_back(curinstance);
	}

	si.setHosts(hostlist);

	return si;
}
