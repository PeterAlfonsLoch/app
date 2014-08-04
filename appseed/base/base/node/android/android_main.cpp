#include "framework.h"


CLASS_DECL_BASE int32_t ca2_main();

void CLASS_DECL_BASE __cdecl _ca2_purecall()
{
    throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





int32_t CLASS_DECL_BASE __android_main(::base::system * psystem, int32_t argc, char * argv[])
{

   if(!defer_base_init())
      return -1;

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



   return nReturnCode;

}


int32_t CLASS_DECL_BASE ca2_main(::base::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{
   try
   {

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
























