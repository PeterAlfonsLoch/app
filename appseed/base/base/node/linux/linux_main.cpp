#include "framework.h"


CLASS_DECL_LINUX int32_t ca2_main();

//CLASS_DECL_LINUX extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_LINUX fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_LINUX __cdecl _ca2_purecall()
{
    throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);


int xlib_error_handler(Display * d, XErrorEvent * e)
{

   if(e->request_code == 12) //
   {

      if(e->error_code == BadValue)
      {
      }

   }
   char sz[1024];
   XGetErrorText(d, e->error_code, sz, sizeof(sz));
   fputs(sz, stderr);

   abort();

}


//sp(::base::application)     win_application_create(sp(::base::application) pappSystem, const char * pszId);
//sp(::base::application)     win_instantiate_application(sp(::base::application) pappSystem, const char * pszId);
//int32_t                     win_application_procedure(sp(::base::application) pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  can be replaced as long as '::ca2::WinInit' is called first

extern char gen_InitAppState;

CLASS_DECL_LINUX bool __initialize(bool bDLL, DWORD dwVersion);






void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}
