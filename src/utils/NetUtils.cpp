#include "utils/NetUtils.h"

String NetUtils::LOCAL_IP;

void NetUtils::Init()
{
	LOCAL_IP = "127.0.0.1";//TODO:read local ip;
}

String NetUtils::localIP()
{
	return LOCAL_IP;
}
