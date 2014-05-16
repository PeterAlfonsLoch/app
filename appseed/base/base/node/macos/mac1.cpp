#include "framework.h"
#include "mac1.h"


namespace mac
{
   
   int32_t function()
   {
      return 0;
   }
   
   
   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));
   }
   
   
} // namespace mac


void CLASS_DECL_mac __abort()
{
   __mac_term();
   
   abort();
   
}


#ifdef DEBUG

bool CLASS_DECL_mac __check_memory()
{
   
   return false;
   
}

#endif


LRESULT CALLBACK __window_procedure_base(oswindow, UINT, WPARAM, LPARAM);


#undef __window_procedure

LRESULT CALLBACK __window_procedure_base(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   
   return __window_procedure(hWnd, nMsg, wParam, lParam);
   
}


extern int32_t CLASS_DECL_mac __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);


void CLASS_DECL_mac __mac_term()
{

   
}




