#include "framework.h"

#include <crt_externs.h>
CLASS_DECL_BASE int32_t ca2_main();

//CLASS_DECL_BOOT extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BOOT fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_BASE __cdecl _ca2_purecall()
{
   throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);


uint32_t __run_system(void * p);


