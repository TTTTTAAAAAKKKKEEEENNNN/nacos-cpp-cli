#include <iostream>
#include "DebugAssertion.h"
#include "config/IOUtils.h"
#include "Debug.h"

#define ENCODING "UTF-8"

using namespace std;

bool testReadWriteFile()
{
	cout << "in function testReadWriteFile" << endl;
	
	String cwd = IOUtils::getCwd();
	String tmpPath = cwd + "/tmp";
	IOUtils::recursivelyCreate(tmpPath);
	String writeFile = tmpPath + "/testfile";
	IOUtils::writeStringToFile(writeFile, "nacos-cpp-cli-test", ENCODING);

	String content = IOUtils::readStringFromFile(writeFile, ENCODING);
	SHOULD_BE_TRUE(content == "nacos-cpp-cli-test", "String \"nacos-cpp-cli-test\" is written to file, should be the same when reading");
	return true;
}

bool testGetFileSize()
{
	cout << "in function testGetFileSize" << endl;
	
	String cwd = IOUtils::getCwd();
	String tmpPath = cwd + "/tmp";
	IOUtils::recursivelyCreate(tmpPath);
	String writeFile = tmpPath + "/testfile";
	IOUtils::writeStringToFile(writeFile, "nacos-cpp-cli-test", ENCODING);

	size_t sz = IOUtils::getFileSize(writeFile);
	SHOULD_BE_TRUE(sz == 18, "String \"nacos-cpp-cli-test\" is written to file, size should be 18");
	return true;
}

bool testFileExists()
{
	cout << "in function testFileExists" << endl;

	String cwd = IOUtils::getCwd();
	String tmpPath = cwd + "/tmp";
	String writeFile = tmpPath + "/testfile";
	IOUtils::recursivelyRemove(tmpPath);

	cout << "Cwd:" << cwd << endl;
	SHOULD_BE_TRUE(IOUtils::checkNotExistOrNotFile(cwd), "The source folder should be a folder, not a file");
	SHOULD_BE_FALSE(IOUtils::checkNotExistOrNotDir(cwd), "The source folder should be a folder");

	IOUtils::recursivelyCreate(tmpPath);
	IOUtils::writeStringToFile(writeFile, "nacos-cpp-cli-test", ENCODING);
	SHOULD_BE_FALSE(IOUtils::checkNotExistOrNotFile(writeFile), "Created a file named \"testfile\" with content \"nacos-cpp-cli-test\"");
	return true;
}


bool testCreateAndRemove()
{
	cout << "in function testFileExists" << endl;

	String cwd = IOUtils::getCwd();
	String tmpPath = cwd + "/tmp/123/456/789/2312/afda/4__dsa/dd_";
	String rmpath = cwd + "/tmp/123";
	IOUtils::recursivelyCreate(tmpPath);
	SHOULD_BE_FALSE(IOUtils::checkNotExistOrNotDir(tmpPath), "We have created a dir, it should exist");
	IOUtils::recursivelyRemove(rmpath);
	SHOULD_BE_TRUE(IOUtils::checkNotExistOrNotFile(cwd + "/tmp"), "Removed everything except the tmp folder");
	String easterEgg = cwd + "/tmp/Liao/Sijia";
	IOUtils::recursivelyCreate(easterEgg);
	return true;
}

bool testCleanDirectory()
{
	cout << "in function testCleanDirectory" << endl;

	String cwd = IOUtils::getCwd();
	String tmpPath = cwd + "/tmp/testcleandir/456/789/2312/afda/4__dsa/dd_";
	String cleanPath = cwd + "/tmp/testcleandir";
	IOUtils::recursivelyCreate(tmpPath);
	SHOULD_BE_FALSE(IOUtils::checkNotExistOrNotDir(tmpPath), "We have created a dir, it should exist");
	IOUtils::cleanDirectory(cleanPath);
	SHOULD_BE_TRUE(IOUtils::checkNotExistOrNotDir(tmpPath), "Subdirectories of the dir is cleaned, it should not exist");
	SHOULD_BE_FALSE(IOUtils::checkNotExistOrNotDir(cleanPath), "The dir is cleaned, but itself should exist");
	return true;
}