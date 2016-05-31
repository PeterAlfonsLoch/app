//#include "framework.h"

extern int __abi___threading_model;

extern void _on_ace_thread_attach();
extern void _on_ace_thread_detach();

#ifdef METROWIN
[MTAThread]
#endif
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugString(L"::ca2:: metrowin.dll :: initializing!\n");
      

      __abi___threading_model = 0; // avoid further changes

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

//      HMODULE hmodule;
   
      /*try
      {
      
         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, "ca.dll", &hmodule) != FALSE)
         {

            try
            {
                  
               ::FreeLibrary(hmodule);

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {
      } */

      ::OutputDebugStringW(L"::ca2:: metrowin.dll :: terminating!\n");

   }
   else if(dwReason == DLL_THREAD_ATTACH)
   {
      //_on_ace_thread_attach();
      
   }
   else if(dwReason == DLL_THREAD_DETACH)
   {
      //_on_ace_thread_detach();
   }



   return 1;   // ok

}




