#include "framework.h"



hresult_exception::hresult_exception(sp(::ca2::application) papp, HRESULT hr) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
   m_hresult = hr;
}
   

hresult_exception::~hresult_exception()
{
}
