#ifndef __LISTENER_H_
#define __LISTENER_H_
#include "NacosString.h"

class Listener
{
public:
	virtual void receiveConfigInfo(const String &configInfo) = 0;
	virtual ~Listener() {};
};

#endif