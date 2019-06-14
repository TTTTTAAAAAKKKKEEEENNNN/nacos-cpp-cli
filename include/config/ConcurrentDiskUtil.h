#ifndef __CONC_DISK_UTIL_H_
#define __CONC_DISK_UTIL_H_
#include "NacosString.h"
#include "NacosExceptions.h"

class ConcurrentDiskUtil
{
public:
    /**
     * get file content
     *
     * @param file        file
     * @param charsetName charsetName
     * @return content
     * @throws IOException IOException
     */
	static String getFileContent(const String &file, const String &charsetName) throw(IOException);

    /**
     * write file content
     *
     * @param file        file
     * @param content     content
     * @param charsetName charsetName
     * @return whether write ok
     * @throws IOException IOException
     */
    static bool writeFileContent(const String &path, const String &content,	const String &charsetName) throw (IOException);
};
#endif