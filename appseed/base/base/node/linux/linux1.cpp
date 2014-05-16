#include "framework.h"


namespace linux
{

   int32_t function()
   {
      return 0;
   }


   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));
   }

} // namespace linux


#undef __window_procedure
LRESULT CALLBACK
__window_procedure_base(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   return __window_procedure(hWnd, nMsg, wParam, lParam);
}


LRESULT CALLBACK __window_procedure_base(oswindow, UINT, WPARAM, LPARAM);




void CLASS_DECL_LINUX __lnx_term()
{



}











