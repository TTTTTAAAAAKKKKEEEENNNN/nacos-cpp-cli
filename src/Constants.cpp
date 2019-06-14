#include "Constants.h"

/**
 * Constant
 *
 * @author Nacos
 */

const String Constants::CLIENT_VERSION = "3.0.0";

const int Constants::DATA_IN_BODY_VERSION = 204;

const String Constants::DEFAULT_GROUP = "DEFAULT_GROUP";

const String Constants::APPNAME = "AppName";

const String Constants::UNKNOWN_APP = "UnknownApp";

const String Constants::DEFAULT_DOMAINNAME = "commonconfig.config-host.taobao.com";

const String Constants::DAILY_DOMAINNAME = "commonconfig.taobao.net";

const String Constants::NUL = "";

const String Constants::DATAID = "dataId";

const String Constants::GROUP = "group";

const String Constants::LAST_MODIFIED = "Last-Modified";

const String Constants::ACCEPT_ENCODING = "Accept-Encoding";

const String Constants::CONTENT_ENCODING = "Content-Encoding";

const String Constants::PROBE_MODIFY_REQUEST = "Listening-Configs";

const String Constants::PROBE_MODIFY_RESPONSE = "Probe-Modify-Response";

const String Constants::PROBE_MODIFY_RESPONSE_NEW = "Probe-Modify-Response-New";

const String Constants::USE_ZIP = "true";

const String Constants::CONTENT_MD5 = "Content-MD5";

const String Constants::CONFIG_VERSION = "Config-Version";

const String Constants::IF_MODIFIED_SINCE = "If-Modified-Since";

const String Constants::SPACING_INTERVAL = "client-spacing-interval";

const String Constants::BASE_PATH = "/v1/cs";

const String Constants::CONFIG_CONTROLLER_PATH = BASE_PATH + "/configs";

/**
* second
*/
const int Constants::ASYNC_UPDATE_ADDRESS_INTERVAL = 300;

/**
* second
*/
const int Constants::POLLING_INTERVAL_TIME = 15;

/**
* millisecond
*/
const int Constants::ONCE_TIMEOUT = 2000;

/**
* millisecond
*/
const int Constants::SO_TIMEOUT = 60000;

/**
* millisecond
*/
const int Constants::RECV_WAIT_TIMEOUT = ONCE_TIMEOUT * 5;

const String Constants::ENCODE = "UTF-8";

const String Constants::MAP_FILE = "map-file.js";

const int Constants::FLOW_CONTROL_THRESHOLD = 20;

const int Constants::FLOW_CONTROL_SLOT = 10;

const int Constants::FLOW_CONTROL_INTERVAL = 1000;

const String Constants::LINE_SEPARATOR = "\x1";

const String Constants::WORD_SEPARATOR = "\x2";

const String Constants::LONGPOLLING_LINE_SEPARATOR = "\r\n";

const String Constants::CLIENT_APPNAME_HEADER = "Client-AppName";
const String Constants::CLIENT_REQUEST_TS_HEADER = "Client-RequestTS";
const String Constants::CLIENT_REQUEST_TOKEN_HEADER = "Client-RequestToken";

const int Constants::ATOMIC_MAX_SIZE = 1000;

const String Constants::NAMING_INSTANCE_ID_SPLITTER = "#";
const int Constants::NAMING_INSTANCE_ID_SEG_COUNT = 4;
const String Constants::NAMING_HTTP_HEADER_SPILIER = "\\|";

const String Constants::DEFAULT_CLUSTER_NAME = "DEFAULT";

const String Constants::DEFAULT_NAMESPACE_ID = "public";

const int Constants::WRITE_REDIRECT_CODE = 307;

const String Constants::SERVICE_INFO_SPLITER = "@@";

const String Constants::NULL_STRING = "null";

const String Constants::FILE_SEPARATOR = "/";