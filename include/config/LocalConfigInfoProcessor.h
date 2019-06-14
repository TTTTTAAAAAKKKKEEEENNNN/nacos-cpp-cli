#ifndef __LOC_CFG_INF_PROCESSOR_H_
#define __LOC_CFG_INF_PROCESSOR_H_

#include "NacosString.h"
#include "NacosExceptions.h"
/**
 * Local Disaster Recovery Directory Tool
 *
 * @author Nacos
 */
class LocalConfigInfoProcessor
{
public:
	static String getFailover(const String &serverName, const String &dataId, const String &group, const String &tenant);

    /**
     * 获取本地缓存文件内容。NULL表示没有本地文件或抛出异常。
     */
    static String getSnapshot(const String &name, const String &dataId, const String &group, const String &tenant);

	static String readFile(const String &file) throw(IOException);

	static void saveSnapshot(const String &envName, const String &dataId, const String &group, const String &tenant, const String &config);

    /**
     * 清除snapshot目录下所有缓存文件。
     */
	static void cleanAllSnapshot();

    static void cleanEnvSnapshot(const String &envName);

	static String getFailoverFile(const String &serverName, const String &dataId, const String &group, const String &tenant);

    static String getSnapshotFile(const String &envName, const String &dataId, const String &group, const String &tenant);

    static String LOCAL_FILEROOT_PATH;
    static String LOCAL_SNAPSHOT_PATH;

	static void init();
};
#endif