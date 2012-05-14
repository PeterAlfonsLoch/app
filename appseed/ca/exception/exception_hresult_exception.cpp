#include "framework.h"



hresult_exception::hresult_exception(HRESULT hr)
{
   m_hresult = hr;
}
   

hresult_exception::~hresult_exception()
{
}
