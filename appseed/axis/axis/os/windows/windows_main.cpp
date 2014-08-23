#include "framework.h"
#include "sal.h"


CLASS_DECL_AURA int32_t ca2_main();


void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

   throw simple_exception(get_thread_app());

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}




CLASS_DECL_AURA int32_t __win_main(sp(::aura::system) psystem, ::windows::main_init_data * pmaininitdata)
{

   psystem->construct(NULL);

   if (pmaininitdata == NULL)
   {
      psystem->m_hinstance;
   }

   psystem->init_main_data(pmaininitdata);

   xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   set_main_thread(GetCurrentThread());

   set_main_thread_id(GetCurrentThreadId());

   if(!psystem->pre_run())
   {
      
      return psystem->m_iReturnCode;

   }

   int32_t nReturnCode = psystem->main();

   return nReturnCode;

}

