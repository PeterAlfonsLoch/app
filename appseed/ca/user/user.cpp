#include "framework.h"


namespace user
{


   CLASS_DECL_ca ::user::interaction * create_virtual_window(::ca::application * papp, DWORD dwExStyle, const char * lpClassName, const char * lpWindowName, DWORD dwStyle,
      int32_t X, int32_t Y, int32_t nWidth, int32_t nHeight, ::user::interaction * pguieParent, id id, HINSTANCE hInstance, LPVOID lpParam)
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
      ::user::interaction * pguie = new ::user::interaction(papp);
      if(pguie->create(pguieParent, id))
      {
         return pguie;
      }
      delete pguie;
      return NULL;
   }










   ::user::interaction * get_parent_owner(::user::interaction * oswindow)
   {
      // check for permanent-owned ::ca::window first
      ::user::interaction* pWnd = oswindow;
      if(pWnd == NULL)
         return NULL;
      return pWnd->get_owner();
   }

















      bool is_descendant(::user::interaction * oswindow_Parent, ::user::interaction * oswindow_Child)
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




