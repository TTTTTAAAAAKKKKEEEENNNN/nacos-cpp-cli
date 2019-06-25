#include "config/LocalConfigInfoProcessor.h"
#include <stdio.h>
#include <list>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include "NacosExceptions.h"
#include "NacosString.h"
#include "ParamUtils.h"
#include "config/SnapShotSwitch.h"
#include "config/JVMUtil.h"
#include "config/ConcurrentDiskUtil.h"
#include "config/IOUtils.h"
#include "Constants.h"
#include "Debug.h"

String LocalConfigInfoProcessor::getFailover(const String &serverName, const String &dataId, const String &group, const String &tenant)
{
	String localPath = getFailoverFile(serverName, dataId, group, tenant);

	if (IOUtils::checkNotExistOrNotFile(localPath))
	{
		return NULLSTR;
	}

	try
	{
		return readFile(localPath);
	} catch (IOException ioe) {
		log_error("[%s] get failover error, file: %s, exception:%s", serverName.c_str(), localPath.c_str(), ioe.what());
		return NULLSTR;
	}
};

/**
 * ��ȡ���ػ����ļ����ݡ�NULL��ʾû�б����ļ����׳��쳣��
 */
String LocalConfigInfoProcessor::getSnapshot
(
	const String &name,
	const String &dataId,
	const String &group,
	const String &tenant
)
{
	if (!SnapShotSwitch::getIsSnapShot()) {
		return NULLSTR;
	}
	String file = getSnapshotFile(name, dataId, group, tenant);
	if (IOUtils::checkNotExistOrNotFile(file)) {
		return NULLSTR;
	}

	try {
		return readFile(file);
	} catch (IOException ioe) {
		log_error("[%s]+get snapshot error, file:%s what:%s\n",name.c_str() , file.c_str(), ioe.what());
		return NULLSTR;
	}
};

String LocalConfigInfoProcessor::readFile(const String &file) throw(IOException)
{
	if (IOUtils::checkNotExistOrNotFile(file))
	{
		return NULLSTR;
	}

	if (JVMUtil::isMultiInstance())
	{
		return ConcurrentDiskUtil::getFileContent(file, Constants::ENCODE);
	}
	else
	{
		return IOUtils::readStringFromFile(file, Constants::ENCODE);
	}
};

void LocalConfigInfoProcessor::saveSnapshot(const String &envName, const String &dataId, const String &group, const String &tenant, const String &config)
{
	if (!SnapShotSwitch::getIsSnapShot())
	{
		return;
	}

	String file = getSnapshotFile(envName, dataId, group, tenant);
	if (isNull(config))
	{
		int remove_result = remove(file.c_str());
		if (remove_result)//error happens when removing the file
		{
			log_error("[%s] delete snapshot error, remove() returns %d, errno = %d\n",
			envName.c_str(), remove_result, errno);
		}
	}
	else
	{
		String parentFile = IOUtils::getParentFile(file);
		if (IOUtils::checkNotExistOrNotDir(parentFile))
		{
			IOUtils::recursivelyCreate(parentFile);
			//LOGGER.error("[{}] save snapshot error", envName);
		}

		if (JVMUtil::isMultiInstance())
		{
			ConcurrentDiskUtil::writeFileContent(file, config, Constants::ENCODE);
		}
		else
		{
			IOUtils::writeStringToFile(file, config, Constants::ENCODE);
		}

		//LOGGER.error("[" + envName + "] save snapshot error, " + file, ioe);
	}
};

/**
 * ���snapshotĿ¼�����л����ļ���
 */
void LocalConfigInfoProcessor::cleanAllSnapshot()
{
	std::list<String> rootFile = IOUtils::listFiles(LOCAL_SNAPSHOT_PATH);

	for (std::list<String>::iterator it = rootFile.begin(); it != rootFile.end(); it++)
	{
		//endsWith("_nacos")
		if (it->length() >= 6 && (it->rfind("_nacos") == it->length() - 6))
		{
			IOUtils::cleanDirectory(LOCAL_SNAPSHOT_PATH + "/" + *it);
		}
	}
	//LOGGER.error("clean all snapshot error, " + ioe.toString(), ioe);
};

void LocalConfigInfoProcessor::cleanEnvSnapshot(const String &envName)
{
	String tmp = LOCAL_SNAPSHOT_PATH + "/" + envName + "_nacos";
	tmp += "/snapshot";
	//I think we should remove -tenant also, so for one envname, cache for all tenants within the environment will be purged
	String tmp_tenant = tmp + "-tenant";
	IOUtils::cleanDirectory(tmp);
	IOUtils::cleanDirectory(tmp_tenant);
	log_info("success delete %s-snapshot: %s\n", envName.c_str(), tmp.c_str());
};

String LocalConfigInfoProcessor::getFailoverFile(const String &serverName, const String &dataId, const String &group, const String &tenant)
{
	String Failoverfile = LOCAL_SNAPSHOT_PATH + "/" + serverName + "_nacos";
	Failoverfile += "/data";
	if (ParamUtils::isBlank(tenant)) {
		Failoverfile += "/config-data";
	} else {
		Failoverfile += "/config-data-tenant/";
		Failoverfile += tenant;
	}
	Failoverfile += "/" + group + "/" + dataId;
	return Failoverfile;
};

String LocalConfigInfoProcessor::getSnapshotFile(const String &envName, const String &dataId, const String &group, const String &tenant)
{
	String filename = LOCAL_SNAPSHOT_PATH + "/" + envName + "_nacos";
	if (isNull(tenant)) {
		filename += "/snapshot";
	} else {
		filename += "/snapshot-tenant/" + tenant;
	}
	
	filename += "/" + group + "/" + dataId;
	return filename;
};

void LocalConfigInfoProcessor::init()
{
	//TODO:Read settings from JM.LOG.PATH/JM.SNAPSHOT.PATH

	/*LOCAL_FILEROOT_PATH = System.getProperty("JM.LOG.PATH", System.getProperty("user.home")) + File.separator
		+ "nacos" + File.separator + "config";
	LOCAL_SNAPSHOT_PATH = System.getProperty("JM.SNAPSHOT.PATH", System.getProperty("user.home")) + File.separator
		+ "nacos" + File.separator + "config";*/

	struct passwd *pw = getpwuid(getuid());
	String homedir = pw->pw_dir;
	LOCAL_FILEROOT_PATH = homedir + Constants::FILE_SEPARATOR + "nacos" + Constants::FILE_SEPARATOR + "config";
	LOCAL_SNAPSHOT_PATH = homedir + Constants::FILE_SEPARATOR + "nacos" + Constants::FILE_SEPARATOR + "config";
	log_info("LOCAL_SNAPSHOT_PATH:%s\n", LOCAL_SNAPSHOT_PATH.c_str());
};