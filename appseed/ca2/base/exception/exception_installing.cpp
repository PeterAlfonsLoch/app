#include "framework.h"

installing_exception::installing_exception(const installing_exception & e) : 
   ca2(e.get_app()),
   ::call_stack(e.get_app()),
   ::base_exception(e.get_app()),
   temporary_exception(e.get_app(), e.m_strTip)
{
}

installing_exception::installing_exception(sp(::ca2::application) papp, const char * pszTip) : 
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   temporary_exception(papp, pszTip)
{
}

installing_exception::~installing_exception()
{
}

