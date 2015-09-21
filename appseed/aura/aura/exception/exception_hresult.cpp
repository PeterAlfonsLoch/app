//#include "framework.h"



hresult_exception::hresult_exception(::aura::application * papp, HRESULT hr) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
   
   debug_print(":hresult(%d)",hr);

   m_hresult = hr;

}
   

hresult_exception::~hresult_exception()
{
}


#define ERRMSGBUFFERSIZE 256
CLASS_DECL_AURA int trace_hr(const char * psz,HRESULT hr)
{
   
   ::aura::application * m_pauraapp = ::get_thread_app();

   string strError = get_system_error_message(hr);
   
   strError.trim();

   TRACE("%s hr=%d:\"%s\"",psz,hr,strError);

   return 0;

}