#include "framework.h"


int c_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{

      initialize_primitive_heap();

      if(!os_initialize())
         return FALSE;

      ::OutputDebugStringW(L"::ca2:: c.dll :: initializing!\n");

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      
      ::OutputDebugStringW(L"::ca2:: c.dll :: terminating!\n");

      os_finalize();

      finalize_primitive_heap();


	}
	return 1;   // ok
}



/*extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}

*/

extern "C"
BOOL WINAPI DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}


extern "C" void __chkstk()
{
}





#ifdef MEROWINWS

CLASS_DECL_c vsstring get_system_error_message(DWORD dwError)
{
   wstring wstr;
   wstr.alloc(64 * 1024 / sizeof(wchar_t));
   FormatMessageW(
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      0,
      (LPWSTR) (LPCWSTR) wstr,
      wstr.get_storage_size(),
      NULL);
   vsstring str(wstr);
   return str;
}



#else

CLASS_DECL_c vsstring get_system_error_message(DWORD dwError)
{
   LPWSTR lpBuffer;
   FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      0,
      (LPWSTR) &lpBuffer,
      1,
      NULL);
   vsstring str;
   str.attach(utf16_to_8(lpBuffer));
   LocalFree(lpBuffer);
   return str;
}

#endif