#ifndef __IO_UTILS_H_
#define __IO_UTILS_H_
#include <list>
#include "NacosString.h"
#include "NacosExceptions.h"

class IOUtils
{
private:
public:
	static size_t getFileSize(const String &file);

	static String readStringFromFile(const String &file, const String &encoding) throw (IOException);

	static void writeStringToFile(const String &file, const String &data, const String &encoding) throw (IOException);

	//Returns true if:
	//a. the file doesn't exist
	//b. the file is not a regular file
	static bool checkNotExistOrNotFile(const String &pathname);

	//Returns true if:
	//a. the file doesn't exist
	//b. the file is not a directory
	static bool checkNotExistOrNotDir(const String &pathname);

	//TODO:To provide compability across different platforms
	static String getParentFile(const String &thefile);

	//Upon success, return true
	//Upon failure, return false
	static bool recursivelyRemove(const String &file);

	static bool cleanDirectory(const String &file);

	static void recursivelyCreate(const String &file);
	
	static String getCwd();

	static std::list<String> listFiles(const String &path);
};

#endif