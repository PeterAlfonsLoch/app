#include "framework.h"


char g_strDebugPuts[1024];
int g_iDebugPuts;
// GCC 4.8 doesn't know that puts() is nothrow; we must give it a hint.
void debug_puts(const char*psz) throw()
{
   while(*psz)
   {
      g_strDebugPuts[g_iDebugPuts] = *psz;
      psz++;
      g_iDebugPuts++;
   }
   g_strDebugPuts[g_iDebugPuts] = '\n';
   g_iDebugPuts++;
   g_strDebugPuts[g_iDebugPuts] = '\0';
}

void foo()
{
   throw simple_exception(::get_thread_app());
}

void aura_auto_debug_teste() {
   return;
   try
   {
      if(true) {
         AUTO(debug_puts("two"));
         debug_puts("one"); // compiler knows this doesn't throw
      }
      if(true) {
         AUTO(debug_puts("three"));
         foo(); // might throw an exception
      }
   }
   catch(...)
   {
   }
   ::output_debug_string(g_strDebugPuts);
}



void teste_aura_cmp()
{
   //auto a = MAKE(PARAMETER);

   //return std::SPACESHIP(a,a);
}
