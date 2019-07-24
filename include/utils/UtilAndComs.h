#ifndef __UTIL_N_COMS_H_
#define __UTIL_N_COMS_H_
#include "NacosString.h"

class UtilAndComs
{
public:
	static String VERSION;

	static String WEB_CONTEXT;

	static String NACOS_URL_BASE;

	static String NACOS_URL_INSTANCE;

	static String ENCODING;

	static String ENV_LIST_KEY;

	static String ALL_IPS;

	static String FAILOVER_SWITCH;

	static String DEFAULT_NAMESPACE_ID;

	static int REQUEST_DOMAIN_RETRY_COUNT;

	static String NACOS_NAMING_LOG_NAME;

	static String NACOS_NAMING_LOG_LEVEL;

	static String SERVER_ADDR_IP_SPLITER;

	static int DEFAULT_CLIENT_BEAT_THREAD_COUNT;//TODO:Calc this according to nr_processors of the host

	static int DEFAULT_POLLING_THREAD_COUNT;//TODO:Calc this according to nr_processors of the host

	static void Init();
};

#endif
