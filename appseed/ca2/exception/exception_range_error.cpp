#include "StdAfx.h"


range_error::range_error(const char * pszError) :
   error_exception(pszError)
{
}

range_error::~range_error()
{
}
