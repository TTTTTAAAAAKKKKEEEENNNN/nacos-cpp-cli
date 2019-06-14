#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_
#include "NacosString.h"

/**
 * Constant
 *
 * @author Nacos
 */
class Constants {
public:
	const static String CLIENT_VERSION;

	const static int DATA_IN_BODY_VERSION;

	const static String DEFAULT_GROUP;

	const static String APPNAME;

	const static String UNKNOWN_APP;

	const static String DEFAULT_DOMAINNAME;

	const static String DAILY_DOMAINNAME;

	const static String NUL;

	const static String DATAID;

	const static String GROUP;

	const static String LAST_MODIFIED;

	const static String ACCEPT_ENCODING;

	const static String CONTENT_ENCODING;

	const static String PROBE_MODIFY_REQUEST;

	const static String PROBE_MODIFY_RESPONSE;

	const static String PROBE_MODIFY_RESPONSE_NEW;

	const static String USE_ZIP;

	const static String CONTENT_MD5;

	const static String CONFIG_VERSION;

	const static String IF_MODIFIED_SINCE;

	const static String SPACING_INTERVAL;

	const static String BASE_PATH;

	const static String CONFIG_CONTROLLER_PATH;

	/**
	 * second
	 */
	const static int ASYNC_UPDATE_ADDRESS_INTERVAL;

	/**
	 * second
	 */
	const static int POLLING_INTERVAL_TIME;

	/**
	 * millisecond
	 */
	const static int ONCE_TIMEOUT;

	/**
	 * millisecond
	 */
	const static int SO_TIMEOUT;

	/**
	 * millisecond
	 */
	const static int RECV_WAIT_TIMEOUT;

	const static String ENCODE;

	const static String MAP_FILE;

	const static int FLOW_CONTROL_THRESHOLD;

	const static int FLOW_CONTROL_SLOT;

	const static int FLOW_CONTROL_INTERVAL;

	const static String LINE_SEPARATOR;

	const static String WORD_SEPARATOR;

	const static String LONGPOLLING_LINE_SEPARATOR;

	const static String CLIENT_APPNAME_HEADER;
	const static String CLIENT_REQUEST_TS_HEADER;
	const static String CLIENT_REQUEST_TOKEN_HEADER;

	const static int ATOMIC_MAX_SIZE;

	const static String NAMING_INSTANCE_ID_SPLITTER;
	const static int NAMING_INSTANCE_ID_SEG_COUNT;
	const static String NAMING_HTTP_HEADER_SPILIER;

	const static String DEFAULT_CLUSTER_NAME;

	const static String DEFAULT_NAMESPACE_ID;

	const static int WRITE_REDIRECT_CODE;

	const static String SERVICE_INFO_SPLITER;

	const static String NULL_STRING;

	const static String FILE_SEPARATOR;
};


#endif