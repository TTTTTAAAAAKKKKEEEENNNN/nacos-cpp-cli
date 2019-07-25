#ifndef __NET_UTILS_H_
#define __NET_UTILS_H_
#include "NacosString.h"

class NetUtils
{
private:
	static String LOCAL_IP;
public:
    static String localIP();
	static void Init();
};

#endif
