#include "framework.h"
#include "sal.h"


extern CLASS_DECL_BASE oswindow_map * g_pwindowmap;


CLASS_DECL_BASE int32_t ca2_main();

//CLASS_DECL_BASE extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BASE fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_BASE __cdecl _ca2_purecall()
{
   throw simple_exception(get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);


//sp(::base::application)     win_application_create(sp(::base::application) pappSystem, const char * pszId);
//sp(::base::application)     win_instantiate_application(sp(::base::application) pappSystem, const char * pszId);
//int32_t                     win_application_procedure(sp(::base::application) pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as '::core::WinInit' is called first



//int32_t CLASS_DECL_BASE ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
//{
//   try
//   {
//
//      _set_purecall_handler(_ca2_purecall);
//
//      ::plane::system * psystem = new ::plane::system();
//
//
//      //Sleep(30 * 1000);
//
//
//      ASSERT(hPrevInstance == NULL);
//
//      int32_t nReturnCode = 0;
//
//      ::windows::main_init_data * pinitmaindata  = new ::windows::main_init_data;
//
//      pinitmaindata->m_hInstance             = hInstance;
//      pinitmaindata->m_hPrevInstance         = hPrevInstance;
//      pinitmaindata->m_vssCommandLine        = lpCmdLine;
//      pinitmaindata->m_nCmdShow              = nCmdShow;
//
//
//      psystem->init_main_data(pinitmaindata);
//
//
//      nReturnCode = psystem->main();
//
//
//      __win_term();
//
//
//      try
//      {
//         delete psystem;
//      }
//      catch(...)
//      {
//      }
//
//      psystem = NULL;
//
//      try
//      {
//         delete __get_module_state()->m_pmapHWND;
//      }
//      catch(...)
//      {
//      }
///*      try
//      {
//         delete __get_module_state()->m_pmapHDC;
//      }
//      catch(...)
//      {
//      }*/
///*      try
//      {
//         delete __get_module_state()->m_pmapHGDIOBJ;
//      }
//      catch(...)
//      {
//      }*/
////      delete __get_module_state()->m_pmapHMENU;
//      try
//      {
//         __get_module_state()->m_pmapHWND     = NULL;
//      }
//      catch(...)
//      {
//      }
///*      try
//      {
//         __get_module_state()->m_pmapHDC      = NULL;
//      }
//      catch(...)
//      {
//      }
//      try
//      {
//         __get_module_state()->m_pmapHGDIOBJ  = NULL;
//      }
//      catch(...)
//      {
//      }*/
//
//      return nReturnCode;
//
//   }
//   catch(...)
//   {
//   }
//   return -1;
//}



void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}


CLASS_DECL_BASE int_bool __win_init()
{

   ::CoInitializeEx(NULL,COINIT_MULTITHREADED);

   if (!main_initialize())
      return FALSE;

   //Sleep(15 * 1000);

   _set_purecall_handler(_ca2_purecall);

   return TRUE;

}


CLASS_DECL_BASE int32_t __win_main(sp(::base::system) psystem, ::windows::main_init_data * pmaininitdata)
{

   psystem->construct();

   if (pmaininitdata == NULL)
   {
      psystem->m_hinstance;
   }

   psystem->init_main_data(pmaininitdata);

   xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   set_main_thread(GetCurrentThread());

   set_main_thread_id(GetCurrentThreadId());

   int32_t nReturnCode = psystem->main();

   return nReturnCode;

}

