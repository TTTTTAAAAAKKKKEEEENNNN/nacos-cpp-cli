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
	NacosException(int errorcode, const char *errormsg) throw();
	NacosException(int errorcode, const String &errormsg) throw();
	~NacosException() throw() {};
	const char* what() const throw() { return _errmsg.c_str(); };
	const int errorcode() const throw() { return _errcode; };

	static const int CLIENT_INVALID_PARAM = -400;
	/**
	* over client threshold（超过server端的限流阈值）
	*/
	static const int CLIENT_OVER_THRESHOLD = -503;

	/**
	* server error code
	* 400 403 throw exception to user
	* 500 502 503 change ip and retry
	*/

	/**
	* invalid param（参数错误）
	*/
	static const int INVALID_PARAM = 400;
	/**
	* no right（鉴权失败）
	*/
	static const int NO_RIGHT = 403;
	/**
	* conflict（写并发冲突）
	*/
	static const int CONFLICT = 409;
	/**
	* server error（server异常，如超时）
	*/
	static const int SERVER_ERROR = 500;
	/**
	* bad gateway（路由异常，如nginx后面的Server挂掉）
	*/
	static const int BAD_GATEWAY = 502;
	/**
	* over threshold（超过server端的限流阈值）
	*/
	static const int OVER_THRESHOLD = 503;
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
