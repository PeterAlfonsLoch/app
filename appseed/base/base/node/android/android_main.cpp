#include "framework.h"


CLASS_DECL_BASE int32_t ca2_main();

//CLASS_DECL_BASE extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BASE fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_BASE __cdecl _ca2_purecall()
{
    throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





int32_t CLASS_DECL_BASE __android_main(int32_t argc, char * argv[])
{

   if(!defer_base_init())
      return -1;

   ::core::system * psystem = new ::core::system();

   int32_t nReturnCode = 0;


   ::android::main_init_data * pinitmaindata  = new ::android::main_init_data;


   pinitmaindata->m_hInstance             = NULL;
   pinitmaindata->m_hPrevInstance         = NULL;
   if(argc > 0)
   {
      pinitmaindata->m_vssCommandLine     = argv[0];
   }
   bool bColon = false;
   for(int32_t i = 1; i < argc; i++)
   {
      if(bColon || (bColon = (strcmp(argv[i], ":") == 0)))
      {
         pinitmaindata->m_vssCommandLine     += " ";
         pinitmaindata->m_vssCommandLine     += argv[i];

      }
      else
      {
         pinitmaindata->m_vssCommandLine     += " \"";
         pinitmaindata->m_vssCommandLine     += argv[i];
         pinitmaindata->m_vssCommandLine     += "\"";
      }
   }
   pinitmaindata->m_nCmdShow              = SW_SHOW;


   psystem->init_main_data(pinitmaindata);

   //simple_message_box(NULL, "box1", "box1", MB_ICONINFORMATION);

   nReturnCode = psystem->main();

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
      defer_core_term();
   }
   catch(...)
   {

   }

   return nReturnCode;

}


int32_t CLASS_DECL_BASE ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{
   try
   {

//      _set_purecall_handler(_ca2_purecall);

      ::core::system * psystem = new ::core::system();


      //Sleep(30 * 1000);


      ASSERT(hPrevInstance == NULL);

      int32_t nReturnCode = 0;

      ::android::main_init_data * pinitmaindata  = new ::android::main_init_data;

      pinitmaindata->m_hInstance             = hInstance;
      pinitmaindata->m_hPrevInstance         = hPrevInstance;
      pinitmaindata->m_vssCommandLine        = lpCmdLine;
      pinitmaindata->m_nCmdShow              = nCmdShow;


      psystem->init_main_data(pinitmaindata);


      nReturnCode = psystem->main();


      __android_term();


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

      set_heap_mutex(NULL);


      return nReturnCode;
   }
   catch(...)
   {
   }
   return -1;
}



void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}
