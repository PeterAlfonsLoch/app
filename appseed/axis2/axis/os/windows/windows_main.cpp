#include "framework.h"
#include "sal.h"


CLASS_DECL_AXIS int32_t ca2_main();


void CLASS_DECL_AXIS __cdecl _ca2_purecall()
{

   throw simple_exception(get_thread_app());

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}




