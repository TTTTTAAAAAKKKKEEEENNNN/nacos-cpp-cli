#include "NacosExceptions.h"

NacosException::NacosException(int errorcode, const char *errormsg) throw()
{
	_errcode = errorcode;
	_errmsg.assign(errormsg);
}

NacosException::NacosException(int errorcode, const String &errormsg)  throw()
{
	_errcode = errorcode;
	_errmsg = errormsg;
}