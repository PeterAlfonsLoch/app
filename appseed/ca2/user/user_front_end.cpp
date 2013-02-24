#include "framework.h"

namespace user
{

   ::userbase::menu * front_end::s_pmenu = NULL;
   HHOOK front_end::s_hhookMouse = NULL;
   int32_t front_end::s_iMouseHookCount    = 0;

   front_end::front_end()
   {

   }

   front_end::~front_end()
   {
   }


   //bool front_end::HookMenu(::userbase::menu * pmenu)
   //{
      /*if(s_pmenu != NULL)
      {
         UnhookMenu()
      }
      s_pmenu = pmenu;
      if(s_hhookMouse == NULL)
      {
         s_hhookMouse = SetWindowsHookEx(
                        WH_MOUSE,
                        MouseProc,
                        NULL,
                        0);
         if(s_hhookMouse != NULL)
         {
            s_iMouseHookCount = 1;
            return true;
         }
      }
      else
      {
         s_iMouseHookCount++;
         return true;
      }
      return false;*/
   //}

   //bool front_end::UnhookMenu(::userbase::menu * pmenu)
   //{
      /*if(s_pmenu == NULL)
         return false;
      s_pmenu->DestroyWindow();
      if(s_iMouseHookCount > 0)
      {
         s_iMouseHookCount--;
         if(s_iMouseHookCount == 0)
         {
            bool bResult = UnhookWindowsHookEx(s_hhookMouse);
            s_hhookMouse = NULL;
            return bResult != FALSE;
         }
         return true;
      }
      return false;*/
   ///}

   LRESULT CALLBACK front_end::MouseProc(
      int32_t      nCode,
      WPARAM   wparam,
      LPARAM   lparam)
   {
      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      /*if(nCode < 0)
      {
         return CallNextHookEx(s_hhookMouse, nCode, wparam, lparam);
      }
      if(wparam == WM_LBUTTONDOWN)
      {
         s_pmenu->OnMouseProc(wparam, lparam);
      }

      return CallNextHookEx(s_hhookMouse, nCode, wparam, lparam);*/
      return 0;
   }

} // namespace ca