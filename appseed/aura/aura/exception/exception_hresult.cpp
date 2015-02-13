//#include "framework.h"



hresult_exception::hresult_exception(::aura::application * papp, HRESULT hr) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
      printf(":hresult(%d)", hr);
   m_hresult = hr;
}
   

hresult_exception::~hresult_exception()
{
}
