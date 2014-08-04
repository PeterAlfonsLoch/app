#include "framework.h"
#include "sal.h"


CLASS_DECL_BASE int ca2_main();


//CLASS_DECL_BOOT extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BOOT fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_BASE __cdecl _ca2_purecall()
{
    throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);


//::base::application *     win_application_create(::base::application * pappSystem, const char * pszId);
//::base::application *     win_instantiate_application(::base::application * pappSystem, const char * pszId);
//int                     win_application_procedure(::base::application * pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as '::ca2::WinInit' is called first


int CLASS_DECL_BASE win_main(::base::system * psystem, ::Platform::Array < ::Platform::String ^ > ^ args)
{

   //UNREFERENCED_PARAMETER(lpCmdLine);




//   ::CoInitialize(NULL);


   if(!main_initialize())
      return -1;


   _set_purecall_handler(_ca2_purecall);


   int nReturnCode = 0;


   ::metrowin::main_init_data * pinitmaindata  = new ::metrowin::main_init_data;

   pinitmaindata->m_hInstance             = NULL;
   pinitmaindata->m_hPrevInstance         = NULL;
   pinitmaindata->m_vssCommandLine        = "";
   pinitmaindata->m_nCmdShow              = 0;

   //pinitmaindata->m_hInstance             = hInstance;
   //pinitmaindata->m_hPrevInstance         = hPrevInstance;
   //pinitmaindata->m_vssCommandLine        = ::str::international::unicode_to_utf8(::GetCommandLineW());
   //pinitmaindata->m_nCmdShow              = nCmdShow;

   
   psystem->init_main_data(pinitmaindata);

   //MessageBox(NULL, "box1", "box1", MB_ICONINFORMATION);

   nReturnCode = psystem->main();


   try
   {
      main_finalize();
   }
   catch(...)
   {
   }

   try
   {
      __win_term();
   }
   catch(...)
   {
   }


   try
   {
      delete psystem;
   }
   catch(...)
   {
   }

   psystem = NULL;


   try
   {
//      delete __get_module_state()->m_pmapHWND;
   }
   catch(...)
   {
   }
/*   try
   {
      delete __get_module_state()->m_pmapHDC;
   }
   catch(...)
   {
   }*/
/*   try
   {
      delete __get_module_state()->m_pmapHGDIOBJ;
   }
   catch(...)
   {
   }*/
//      delete __get_module_state()->m_pmapHMENU;

   try
   {
      __get_module_state()->m_pmapHWND     = NULL;
   }
   catch(...)
   {
   }
/*   try
   {
      __get_module_state()->m_pmapHDC      = NULL;
   }
   catch(...)
   {
   }*/
/*   try
   {
      __get_module_state()->m_pmapHGDIOBJ  = NULL;
   }
   catch(...)
   {
   }*/


//   set_heap_mutex(NULL);

   return nReturnCode;


}


int CLASS_DECL_BASE ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int nCmdShow)
{
   try
   {

      _set_purecall_handler(_ca2_purecall);

      ::core::system * psystem = new ::core::system();


      //Sleep(30 * 1000);


      ASSERT(hPrevInstance == NULL);

      int nReturnCode = 0;

      ::metrowin::main_init_data * pinitmaindata  = new ::metrowin::main_init_data;

      pinitmaindata->m_hInstance             = hInstance;
      pinitmaindata->m_hPrevInstance         = hPrevInstance;
      pinitmaindata->m_vssCommandLine        = lpCmdLine;
      pinitmaindata->m_nCmdShow              = nCmdShow;


      psystem->init_main_data(pinitmaindata);


      nReturnCode = psystem->main();


      __win_term();


      try
      {
         delete psystem;
      }
      catch(...)
      {
      }

      psystem = NULL;

      try
      {
//         delete __get_module_state()->m_pmapHWND;
      }
      catch(...)
      {
      }
/*      try
      {
         delete __get_module_state()->m_pmapHDC;
      }
      catch(...)
      {
      }*/
/*      try
      {
         delete __get_module_state()->m_pmapHGDIOBJ;
      }
      catch(...)
      {
      }*/
//      delete __get_module_state()->m_pmapHMENU;
      try
      {
         __get_module_state()->m_pmapHWND     = NULL;
      }
      catch(...)
      {
      }
/*      try
      {
         __get_module_state()->m_pmapHDC      = NULL;
      }
      catch(...)
      {
      }
      try
      {
         __get_module_state()->m_pmapHGDIOBJ  = NULL;
      }
      catch(...)
      {
      }*/

//      set_heap_mutex(NULL);


      return nReturnCode;
   }
   catch(...)
   {
   }
   return -1;
}



void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}
