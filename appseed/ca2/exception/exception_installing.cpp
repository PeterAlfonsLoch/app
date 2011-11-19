#include "StdAfx.h"

installing_exception::installing_exception(const installing_exception & e) : 
   temporary_exception(e.m_strTip)
{
}

installing_exception::installing_exception(const char * pszTip) : 
   temporary_exception(pszTip)
{
}

installing_exception::~installing_exception()
{
}

