#ifndef _LOC_CFG_INF_PROCESSOR_H_
#define _LOC_CFG_INF_PROCESSOR_H_
#include <stdio.h>
#include "NacosExceptions.h"
#include "NacosString.h"
#include "ParamUtils.h"
#include "config/SnapShotSwitch.h"
#include "config/IOUtils.h"

/**
 * Local Disaster Recovery Directory Tool
 *
 * @author Nacos
 */
class LocalConfigInfoProcessor
{
public:
	static String getFailover(const String &serverName, const String &dataId, const String &group, const String &tenant)
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
			log_error("[%s] get failover error, file: %s, exception:%s", serverName, localPath, ioe.what());
			return NULLSTR;
		}
	};

    /**
     * 获取本地缓存文件内容。NULL表示没有本地文件或抛出异常。
     */
    static String getSnapshot
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
        File file = getSnapshotFile(name, dataId, group, tenant);
        if (IOUtils::checkNotExistOrNotFile(localPath)) {
            return NULLSTR;
        }

        try {
            return readFile(file);
        } catch (IOException ioe) {
            log_error("[%s]+get snapshot error, file:%s what:%s\n",name.c_str() , file.c_str(), ioe.what());
            return NULLSTR;
        }
    }

	static String readFile(const String &file) throw(IOException)
	{
		if (IOUtils::checkNotExistOrNotFile(file))
		{
			return NULLSTR;
		}

		if (JVMUtil.isMultiInstance())
		{
			return ConcurrentDiskUtil::getFileContent(file, Constants::ENCODE);
		}
		else
		{
			return IOUtils::readStringFromFile(file, Constants::ENCODE);
		}
	}

	static void saveSnapshot(const String &envName, const String &dataId, const String &group, const String &tenant, const String &config)
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
				boolean isMdOk = parentFile.mkdirs();

				//LOGGER.error("[{}] save snapshot error", envName);
			}

			if (JVMUtil::isMultiInstance())
			{
				ConcurrentDiskUtil.writeFileContent(file, config,
				Constants.ENCODE);
			}
			else
			{
				IOUtils::writeStringToFile(file, config, Constants.ENCODE);
			}

			//LOGGER.error("[" + envName + "] save snapshot error, " + file, ioe);
		}
	}

    /**
     * 清除snapshot目录下所有缓存文件。
     */
    static void cleanAllSnapshot() {
        try {
            File rootFile = new File(LOCAL_SNAPSHOT_PATH);
            File[] files = rootFile.listFiles();
            if (files == null || files.length == 0) {
                return;
            }
            for (File file : files) {
                if (file.getName().endsWith("_nacos")) {
                    IOUtils.cleanDirectory(file);
                }
            }
        } catch (IOException ioe) {
            LOGGER.error("clean all snapshot error, " + ioe.toString(), ioe);
        }
    }

    static void cleanEnvSnapshot(const String &envName) {
        File tmp = new File(LOCAL_SNAPSHOT_PATH, envName + "_nacos");
        tmp = new File(tmp, "snapshot");
        try {
            IOUtils.cleanDirectory(tmp);
            LOGGER.info("success delete " + envName + "-snapshot");
        } catch (IOException e) {
            LOGGER.info("fail delete " + envName + "-snapshot, " + e.toString());
            e.printStackTrace();
        }
    }

	static String getFailoverFile(const String &serverName, const String &dataId, const String &group, const String &tenant)
	{
		String Failoverfile = LOCAL_SNAPSHOT_PATH + "/" + serverName + "_nacos";
		Failoverfile += "/data";
		if (ParamUtils.isBlank(tenant)) {
			Failoverfile += "/config-data";
		} else {
			Failoverfile += "/config-data-tenant/";
			Failoverfile += tenant;
		}
		Failoverfile += "/" + group + "/" + dataId;
		return Failoverfile;
	}

    static String getSnapshotFile(const String &envName, const String &dataId, const String &group, const String &tenant)
	{
		String filename = LOCAL_SNAPSHOT_PATH + "/" + envName + "_nacos";
        if (isNull(tenant)) {
            filename += "/snapshot";
        } else {
            filename += "/snapshot-tenant/" + tenant;
        }
		
		filename += "/" + group + "/" + dataId;
        return filename;
    }

    static String LOCAL_FILEROOT_PATH;
    static String LOCAL_SNAPSHOT_PATH;

    static {
        LOCAL_FILEROOT_PATH = System.getProperty("JM.LOG.PATH", System.getProperty("user.home")) + File.separator
            + "nacos" + File.separator + "config";
        LOCAL_SNAPSHOT_PATH = System.getProperty("JM.SNAPSHOT.PATH", System.getProperty("user.home")) + File.separator
            + "nacos" + File.separator + "config";
        LOGGER.info("LOCAL_SNAPSHOT_PATH:{}", LOCAL_SNAPSHOT_PATH);
    }

};
#endif