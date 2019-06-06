#ifndef _LOC_CFG_INF_PROCESSOR_H_
#define _LOC_CFG_INF_PROCESSOR_H_
#include <sys/stat.h>
#include "NacosString.h"
#include "ParamUtils.h"

/**
 * Local Disaster Recovery Directory Tool
 *
 * @author Nacos
 */
class LocalConfigInfoProcessor
{
public:
	static bool checkNotExistOrNotFile(const String &serverName)
	{
		stat thestat = {0};
		stat(localPath.c_str(), &thestat);
		if (errno != 0 || !(thestat & S_IFREG))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	static String getFailover(const String &serverName, const String &dataId, const String &group, const String &tenant)
	{
		String localPath = getFailoverFile(serverName, dataId, group, tenant);

		if (checkNotExistOrNotFile(localPath))
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
	}

    /**
     * 获取本地缓存文件内容。NULL表示没有本地文件或抛出异常。
     */
    static public String getSnapshot(String name, String dataId, String group, String tenant) {
        if (!SnapShotSwitch.getIsSnapShot()) {
            return null;
        }
        File file = getSnapshotFile(name, dataId, group, tenant);
        if (!file.exists() || !file.isFile()) {
            return null;
        }

        try {
            return readFile(file);
        } catch (IOException ioe) {
            LOGGER.error("[" + name + "]+get snapshot error, " + file, ioe);
            return null;
        }
    }

	static private String readFile(const String &file) throws IOException
	{
		if (checkNotExistOrNotFile(file))
		{
			return NULLSTR;
		}

		if (JVMUtil.isMultiInstance()) {
		return ConcurrentDiskUtil.getFileContent(file, Constants.ENCODE);
		}
		else
		{
			FILE 
		}
	}

    static public void saveSnapshot(String envName, String dataId, String group, String tenant, String config) {
        if (!SnapShotSwitch.getIsSnapShot()) {
            return;
        }
        File file = getSnapshotFile(envName, dataId, group, tenant);
        if (null == config) {
            try {
                IOUtils.delete(file);
            } catch (IOException ioe) {
                LOGGER.error("[" + envName + "] delete snapshot error, " + file, ioe);
            }
        } else {
            try {
                File parentFile = file.getParentFile();
                if (!parentFile.exists()) {
                    boolean isMdOk = parentFile.mkdirs();
                    if (!isMdOk) {
                        LOGGER.error("[{}] save snapshot error", envName);
                    }
                }

                if (JVMUtil.isMultiInstance()) {
                    ConcurrentDiskUtil.writeFileContent(file, config,
                        Constants.ENCODE);
                } else {
                    IOUtils.writeStringToFile(file, config, Constants.ENCODE);
                }
            } catch (IOException ioe) {
                LOGGER.error("[" + envName + "] save snapshot error, " + file, ioe);
            }
        }
    }

    /**
     * 清除snapshot目录下所有缓存文件。
     */
    static public void cleanAllSnapshot() {
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

    static public void cleanEnvSnapshot(String envName) {
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

    static File getSnapshotFile(String envName, String dataId, String group, String tenant) {
        File tmp = new File(LOCAL_SNAPSHOT_PATH, envName + "_nacos");
        if (StringUtils.isBlank(tenant)) {
            tmp = new File(tmp, "snapshot");
        } else {
            tmp = new File(tmp, "snapshot-tenant");
            tmp = new File(tmp, tenant);
        }

        return new File(new File(tmp, group), dataId);
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