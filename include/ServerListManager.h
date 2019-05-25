#ifndef __SERVER_LIST_MGR_H_
#define __SERVER_LIST_MGR_H_
#include <list>
#include "NacosString.h"
#include "Properties.h"
#include "NacosExceptions.h"

class ServerListManager
{
private:
	std::list<String> serverList;
	String contentPath;
	void initParams();
	void initSrvListWithAddress(String &address);
public:
	ServerListManager(std::list<String> &fixed);
	ServerListManager(Properties &props) throw(NacosException);
	String getContentPath() { return contentPath; };
	String getCurrentServerAddr();
};
#endif