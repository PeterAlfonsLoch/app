#include "framework.h"



___IOS_STATE gen_MacState;




/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int32_t CLASS_DECL_BASE __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);





void CLASS_DECL_BASE __ios_term()
{

}





LRESULT CALLBACK __window_procedure_base(oswindow, UINT, WPARAM, LPARAM);


#undef __window_procedure
LRESULT CALLBACK
__window_procedure_base(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   return __window_procedure(hWnd, nMsg, wParam, lParam);
}



// Note: in separate module so it can be replaced if needed


void CLASS_DECL_BASE __abort()
{
   //   TRACE(::ca2::trace::category_AppMsg, 0, "__abort called.\n");
   
   __ios_term();
   abort();
}




#ifdef DEBUG
bool CLASS_DECL_BASE __check_memory()
{
   return false;
}
#endif




