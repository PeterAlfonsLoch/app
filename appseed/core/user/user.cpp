#include "framework.h"




namespace user
{

   CLASS_DECL_ca2 sp(::user::interaction) create_virtual_window(sp(base_application) papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
                                                             int32_t X, int32_t Y, int32_t nWidth, int32_t nHeight, sp(::user::interaction) pguieParent, id id, HINSTANCE hInstance, LPVOID lpParam);


   CLASS_DECL_ca2 sp(::user::interaction) create_virtual_window(sp(base_application) papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
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










   sp(::user::interaction) get_parent_owner(sp(::user::interaction) oswindow)
   {
      // check for permanent-owned ::core::window first
      sp(::user::interaction) pWnd = oswindow;
      if(pWnd == NULL)
         return NULL;
      return pWnd->get_owner();
   }

















      bool is_descendant(sp(::user::interaction) oswindow_Parent, sp(::user::interaction) oswindow_Child)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {
      if(!oswindow_Child->IsWindow())
         return FALSE;
      if(!oswindow_Parent->IsWindow())
         return FALSE;
      ASSERT(oswindow_Parent->IsWindow());
      ASSERT(oswindow_Child->IsWindow());

      do
      {
         if (oswindow_Parent == oswindow_Child)
            return TRUE;

         oswindow_Child = ::user::get_parent_owner(oswindow_Child);
      } while (oswindow_Child != NULL);

      return FALSE;
   }




} // namespace user




