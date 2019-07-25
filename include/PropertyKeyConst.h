#ifndef __PROP_KEY_CONST_H_
#define __PROP_KEY_CONST_H_
#include "NacosString.h"

class PropertyKeyConst
{
public:
	static const String IS_USE_ENDPOINT_PARSING_RULE;
    
	static const String ENDPOINT;
    
	static const String ENDPOINT_PORT;
    
	static const String NAMESPACE;
    
	static const String ACCESS_KEY;
    
	static const String SECRET_KEY;
    
	static const String RAM_ROLE_NAME;
    
	static const String SERVER_ADDR;
    
	static const String CONTEXT_PATH;
    
	static const String CLUSTER_NAME;
    
	static const String ENCODE;
    
	static const String NAMING_LOAD_CACHE_AT_START;
    
	static const String NAMING_CLIENT_BEAT_THREAD_COUNT;
    
	static const String NAMING_POLLING_THREAD_COUNT;

	/*public static class SystemEnv {

		static const String ALIBABA_ALIWARE_ENDPOINT_PORT = "ALIBABA_ALIWARE_ENDPOINT_PORT";
        
		static const String ALIBABA_ALIWARE_NAMESPACE = "ALIBABA_ALIWARE_NAMESPACE";
        
		static const String ALIBABA_ALIWARE_ENDPOINT_URL = "ALIBABA_ALIWARE_ENDPOINT_URL";
	}*/
};

#endif