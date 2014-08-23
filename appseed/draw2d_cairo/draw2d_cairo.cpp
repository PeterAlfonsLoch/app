#include "framework.h"


static mutex * s_pmutex = NULL;

mutex & cairo_mutex()
{

   return *s_pmutex;

}


void init_cairo_mutex(sp(::aura::application) papp)
{

    s_pmutex = new mutex(papp);

}



#ifdef METROWIN
[Platform::MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD dwReason,LPVOID lpReserved)
{

   //Sleep(30000);

   //   ASSERT(FALSE);

   xxdebug_box("draw2d_cairo.dll DllMain (0)","box",MB_OK);

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   //openssl_DllMain(hInstance, dwReason, lpReserved);


   if(dwReason == DLL_PROCESS_ATTACH)
   {

      OutputDebugStringW(L"draw2d_cairo.dll initializing!\n");

      xxdebug_box("draw2d_cairo.dll DllMain","box",MB_OK);

   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {

      HMODULE hmodule;

      try
      {

         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,"ca.dll",&hmodule) != FALSE)
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
      }


      OutputDebugStringW(L"draw2d_cairo.dll terminating!\n");


   }

   return 1;   // ok

}


