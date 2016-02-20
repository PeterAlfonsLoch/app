#include "framework.h"


static mutex * s_pmutex = NULL;

extern string_map < FT_Face > * g_pmapFontFace ;

extern string_to_int * g_pmapFontError ;

extern string_to_int * g_pmapFontError2 ;

extern string_map < cairo_font_face_t * > * g_pmapCairoFontFace ;

extern CLASS_DECL_AURA array<object * > * g_paAura;

#ifdef LINUX

extern mutex * g_pmutexFc;

extern string_to_string *      g_pmapFontPath;

#endif

mutex & cairo_mutex()
{

   return *s_pmutex;

}


void init_cairo_mutex(::aura::application * papp)
{

   s_pmutex = new mutex(papp);

   g_paAura->add(s_pmutex);

#ifdef LINUX

   g_pmutexFc = new mutex(papp);

   g_paAura->add(g_pmutexFc);

   g_pmapFontPath = new string_to_string();

   g_paAura->add(g_pmapFontPath);

#endif

   g_pmapFontFace = new string_map < FT_Face > ();

   g_paAura->add(g_pmapFontFace);

   g_pmapCairoFontFace = new string_map < cairo_font_face_t * > ();

   g_paAura->add(g_pmapCairoFontFace);

   g_pmapFontError = new string_to_int ();

   g_paAura->add(g_pmapFontError);

   g_pmapFontError2 = new string_to_int ();

   g_paAura->add(g_pmapFontError2);
}




#ifdef WINDOWS

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


#endif
