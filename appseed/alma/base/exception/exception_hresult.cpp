#include "framework.h"



hresult_exception::hresult_exception(sp(::base::application) papp, HRESULT hr) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
      printf(":hresult(%d)", hr);
   m_hresult = hr;
}
   

hresult_exception::~hresult_exception()
{
}
