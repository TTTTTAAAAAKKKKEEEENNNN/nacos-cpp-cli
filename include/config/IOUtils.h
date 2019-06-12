#ifndef __IO_UTILS_H_
#define __IO_UTILS_H_
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include<unistd.h>
#include "NacosString.h"

class IOUtils {
private:
public:
	static size_t getFileSize(const String &file)
	{
		struct stat statbuf;

		if (stat(file.c_str(), &statbuf) == -1)
		{
			return 0;
		}

		return statbuf.st_size;
	}

	static String readStringFromFile(const String &file, const String &encoding) throw (IOException)
	{
		size_t toRead = getFileSize(file);
		FILE *fp = fopen(file.c_str(), "rb");
		char buf[toRead + 1];
		fread(buf, toRead, 1, fp);
		buf[toRead] = '\0';
		fclose(fp);
		return String(buf);
	};

	static void writeStringToFile(const String &file, const String &data, const String &encoding) throw (IOException)
	{
		FILE *fp = fopen(file.c_str(), "wb");
		fwrite(data.c_str(), data.size(), 1, fp);
		fclose(fp);
	};

	//Returns true if:
	//a. the file doesn't exist
	//b. the file is not a regular file
	static bool checkNotExistOrNotFile(const String &pathname)
	{
		struct stat thestat = {0};
		stat(pathname.c_str(), &thestat);
		if (errno != 0 || !S_ISREG(thestat.st_mode))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	//Returns true if:
	//a. the file doesn't exist
	//b. the file is not a directory
	static bool checkNotExistOrNotDir(const String &pathname)
	{
		struct stat thestat = {0};
		stat(pathname.c_str(), &thestat);
		if (errno != 0 || !S_ISDIR(thestat.st_mode))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	//TODO:To provide compability across different platforms
	static String getParentFile(const String &thefile)
	{
		size_t parentFilePos = thefile.rfind('/');
		//Invalid Directory/Filename, returning empty
		if (parentFilePos == std::string::npos || parentFilePos == 0)
		{
			return NULLSTR;
		}
		String parentFile = thefile.substr(0, parentFilePos - 1);
		return parentFile;
	};

	//Upon success, return true
	//Upon failure, return false
	static bool recursivelyRemove(const String &file)
	{
		struct stat thestat;

		if (stat(file.c_str(), &thestat) == -1)
		{
			log_error("Failed to stat() file, errno: %d\n", errno);
			return false;
		}

		if (S_ISDIR(thestat.st_mode))
		{
			DIR *curdir = opendir(file.c_str());
			struct dirent *direntp = readdir(curdir);
			while (direntp != NULL)
			{
				if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
				{
					//skip this dir and parent
					direntp = readdir(curdir);
					continue;
				}
				struct stat subfilestat;
				String subfilepath = file + "/" + direntp->d_name;

				if (stat(subfilepath.c_str(), &subfilestat) == -1)
				{
					log_error("Failed to stat() file, errno: %d\n", errno);
					closedir(curdir);
					return false;
				}
				if (S_ISREG(subfilestat.st_mode))
				{
					remove(subfilepath.c_str());
				}
				else if (S_ISDIR(subfilestat.st_mode))
				{
					recursivelyRemove(subfilepath);
				}
				//get to the next entry
				direntp = readdir(curdir);
			}
			closedir(curdir);
			remove(file.c_str());
		}
		else if (S_ISREG(thestat.st_mode))
		{
			remove(file.c_str());
		}

		return true;
	};

	static void recursivelyCreate(const String &file)
	{
		String parentFile = getParentFile(file);
		if (!isNull(parentFile))
		{
			recursivelyCreate(parentFile);
		}

		if (checkNotExistOrNotDir(file))
		{
			mkdir(file.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
	};
	
	static String getCwd()
	{
		char temp[PATH_MAX];
		return ( getcwd(temp, sizeof(temp)) ? String( temp ) : String("") );
	}
};

#endif