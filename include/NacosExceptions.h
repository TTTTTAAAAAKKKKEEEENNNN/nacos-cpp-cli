#ifndef __EXCEPTIONS_H_
#define __EXCEPTIONS_H_
#include <exception>
#include "NacosString.h"

class NacosException : public std::exception
{
private:
	int _errcode;
	String _errmsg;
public:
	/**
	* server error（server异常，如超时）
	*/
    const static int SERVER_ERROR = 500;
	/**
	* invalid param（参数错误）
	*/
	const static int CLIENT_INVALID_PARAM = -400;

	NacosException(int errorcode, const char *errormsg) throw();
	NacosException(int errorcode, const String &errormsg) throw();
	~NacosException() throw() {};
	const char* what() const throw() { return _errmsg.c_str(); };
	const int errorcode() const throw() { return _errcode; };
};

class NetworkException : public std::exception
{
private:
	int _curlerrcode;
	String _errmsg;
public:
	NetworkException(int errorcode, const char *errormsg) throw() : _curlerrcode(errorcode), _errmsg(errormsg) {};
	NetworkException(int errorcode, const String &errormsg) throw() : _curlerrcode(errorcode), _errmsg(errormsg) {};
	~NetworkException() throw() {};
	const char* what() const throw() { return _errmsg.c_str(); };
	const int errorcode() const throw() { return _curlerrcode; };
};

class IOException : public std::exception
{
private:
	int _errcode;
	String _errmsg;
public:
	IOException(int errorcode, const char *errormsg) throw() : _errcode(errorcode), _errmsg(errormsg) {};
	IOException(int errorcode, const String &errormsg) throw() : _errcode(errorcode), _errmsg(errormsg) {};
	~IOException() throw() {};
	const char* what() const throw() { return _errmsg.c_str(); };
	const int errorcode() const throw() { return _errcode; };
};
#endif