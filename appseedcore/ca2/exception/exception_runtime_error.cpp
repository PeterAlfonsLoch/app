#include "StdAfx.h"


runtime_error::runtime_error(const char * pszError) :
   error_exception(pszError)
{
}

runtime_error::~runtime_error()
{
}
