#include "init/init.h"
#include "Debug.h"
#include "http/HTTPCli.h"
#include "config/LocalConfigInfoProcessor.h"
#include "config/SnapShotSwitch.h"
#include "config/JVMUtil.h"
#include "utils/UtilAndComs.h"
//static Init initobj;//Implicitly call the constructors

bool SnapShotSwitch::isSnapShot = true;
bool JVMUtil::_isMultiInstance = false;
String LocalConfigInfoProcessor::LOCAL_FILEROOT_PATH = "";
String LocalConfigInfoProcessor::LOCAL_SNAPSHOT_PATH = "";

void Init::doInit()
{
	Debug::set_debug_level(DEBUG);
	HTTPCli::HTTP_GLOBAL_INIT();
	LocalConfigInfoProcessor::init();
	UtilAndComs::Init();
	log_debug("LOCAL_FILEROOT_PATH = %s\n", LocalConfigInfoProcessor::LOCAL_FILEROOT_PATH.c_str());
	log_debug("LOCAL_SNAPSHOT_PATH = %s\n", LocalConfigInfoProcessor::LOCAL_SNAPSHOT_PATH.c_str());
}

void Init::doDeinit()
{
	HTTPCli::HTTP_GLOBAL_DEINIT();
}
