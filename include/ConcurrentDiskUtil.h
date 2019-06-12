#ifndef __CONC_DISK_UTIL_H_
#define __CONC_DISK_UTIL_H_
#include "NacosString.h"
#include "NacosExceptions.h"
#include "LocalConfigInfoProcessor.h"

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
	static String getFileContent(const String &path, const String &charsetName) throw(IOException)
	{
		if (LocalConfigInfoProcessor::checkNotExistOrNotFile(path))
		{
			//TODO:add errorcode
			throw IOException(99999, "checkNotExistOrNotFile failed, unable to access the file, maybe it doesn't exist.");
		}
		size_t toRead = getFileSize(file);
		FILE *fp = fopen(file.c_str(), "rb");
		if (fp == NULL)
		{
			char errbuf[100];
			sprintf(errbuf, "Failed to open file for read, errno: %d", errno);
			//TODO:add errorcode
			throw IOException(99999, errbuf);
		}
		flock(fileno(fp), LOCK_SH);
		char buf[toRead + 1];
		fread(buf, toRead, 1, fp);
		buf[toRead] = '\0';
		flock(fileno(fp), LOCK_UN);
		fclose(fp);
		return String(buf);
	}

    /**
     * write file content
     *
     * @param file        file
     * @param content     content
     * @param charsetName charsetName
     * @return whether write ok
     * @throws IOException IOException
     */
    static bool writeFileContent
	(
		const String &path,
		const String &content,
		const String &charsetName
	) throw (IOException)
	{
		FILE *fp = fopen(path.c_str(), "wb");
		if (fp == NULL)
		{
			char errbuf[100];
			sprintf(errbuf, "Failed to open file for write, errno: %d", errno);
			//TODO:add errorcode
			throw IOException(99999, errbuf);
		}
		flock(fileno(fp), LOCK_SH);
		fwrite(content.c_str(), content.size(), 1, fp);
		flock(fileno(fp), LOCK_UN);
		fclose(fp);
        return true;
    }
};
#endif