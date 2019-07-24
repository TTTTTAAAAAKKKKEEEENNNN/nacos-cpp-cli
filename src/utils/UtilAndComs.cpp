#include "utils/UtilAndComs.h"

String UtilAndComs::VERSION = "Nacos-Java-Client:v1.0.0";

String UtilAndComs::WEB_CONTEXT = "/nacos";

String UtilAndComs::NACOS_URL_BASE = WEB_CONTEXT + "/v1/ns";

String UtilAndComs::NACOS_URL_INSTANCE = NACOS_URL_BASE + "/instance";

String UtilAndComs::ENCODING = "UTF-8";

String UtilAndComs::ENV_LIST_KEY = "envList";

String UtilAndComs::ALL_IPS = "000--00-ALL_IPS--00--000";

String UtilAndComs::FAILOVER_SWITCH = "00-00---000-VIPSRV_FAILOVER_SWITCH-000---00-00";

String UtilAndComs::DEFAULT_NAMESPACE_ID = "public";

int UtilAndComs::REQUEST_DOMAIN_RETRY_COUNT = 3;

String UtilAndComs::NACOS_NAMING_LOG_NAME = "com.alibaba.nacos.naming.log.filename";

String UtilAndComs::NACOS_NAMING_LOG_LEVEL = "com.alibaba.nacos.naming.log.level";

String UtilAndComs::SERVER_ADDR_IP_SPLITER = ":";

int UtilAndComs::DEFAULT_CLIENT_BEAT_THREAD_COUNT = 1;//TODO:Calc this according to nr_processors of the host

int UtilAndComs::DEFAULT_POLLING_THREAD_COUNT = 1;//TODO:Calc this according to nr_processors of the host

//Underlying logic:
/*int UtilAndComs::DEFAULT_CLIENT_BEAT_THREAD_COUNT = Runtime.getRuntime()
.availableProcessors() > 1 ? Runtime.getRuntime().availableProcessors() / 2
: 1;

int UtilAndComs::DEFAULT_POLLING_THREAD_COUNT = Runtime.getRuntime()
.availableProcessors() > 1 ? Runtime.getRuntime().availableProcessors() / 2
: 1;*/

void UtilAndComs::Init()
{

}
