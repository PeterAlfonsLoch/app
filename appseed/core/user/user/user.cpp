#include "framework.h"




namespace user
{

   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(sp(base_application) papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
                                                             int32_t X, int32_t Y, int32_t nWidth, int32_t nHeight, sp(::user::interaction) pguieParent, id id, HINSTANCE hInstance, LPVOID lpParam);


   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(sp(base_application) papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
      int32_t X, int32_t Y, int32_t nWidth, int32_t nHeight, sp(::user::interaction) pguieParent, id id, HINSTANCE hInstance, LPVOID lpParam)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpClassName);
      UNREFERENCED_PARAMETER(lpWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(X);
      UNREFERENCED_PARAMETER(Y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(hInstance);
      UNREFERENCED_PARAMETER(lpParam);
      sp(::user::interaction) pguie = new ::user::interaction(papp);
      if(pguie->create(pguieParent, id))
      {
         return pguie;
      }
      pguie.release();
      return NULL;
   }





} // namespace user




