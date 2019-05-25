#include <stdlib.h>
#include "ServerListManager.h"
#include "PropertyKeyConst.h"
#include "Parameters.h"
#include "Debug.h"

void ServerListManager::initParams()
{
	contentPath.assign(DEFAULT_CONTEXT_PATH);
}

void ServerListManager::initSrvListWithAddress(String &address)
{
	//If the address doesn't contain port, add 8848 as the default port for it
	if (address.find(':') == std::string::npos)
	{
		//TODO:dynamically read default port, don't use hard-coded value
		serverList.push_back( address + ":8848");
	}
	else
	{
		serverList.push_back(address);
	}
}


ServerListManager::ServerListManager(std::list<String> &fixed)
{
	initParams();
	for (std::list<String>::iterator it = fixed.begin(); it != fixed.end(); it++)
	{
		initSrvListWithAddress(*it);
	}
}

String ServerListManager::getCurrentServerAddr()
{
	//TODO:Currently we just choose a server randomly,
	//later we should sort it according to the java client and use cache
	size_t max_serv_slot = serverList.size();
	srand(time(NULL));
	int to_skip = rand() % max_serv_slot;
	std::list<String>::iterator it = serverList.begin();
	for (int skipper = 0; skipper < to_skip; skipper++)
	{
		it++;
	}
	
	return *it;
}

ServerListManager::ServerListManager(Properties &props) throw(NacosException)
{
	initParams();
	serverList.clear();
	//TODO:endpoint is not implemented
	if (props.count(PropertyKeyConst::SERVER_ADDR) <= 0)
	{
		throw NacosException(NacosException::CLIENT_INVALID_PARAM, "endpoint is blank");
	}
	
	String server_addr = props[PropertyKeyConst::SERVER_ADDR];
	size_t start_pos = 0;
	size_t cur_pos = 0;
	cur_pos = server_addr.find(',', start_pos);
	
	//break the string with ',' separator
	while (cur_pos != std::string::npos)
	{
		String cur_addr = server_addr.substr(start_pos, cur_pos - start_pos);
		initSrvListWithAddress(cur_addr);
		start_pos = cur_pos + 1;
		cur_pos = server_addr.find(',', start_pos);
	}
	
	//deal with the last string
	String last_addr = server_addr.substr(start_pos);
	initSrvListWithAddress(last_addr);
}