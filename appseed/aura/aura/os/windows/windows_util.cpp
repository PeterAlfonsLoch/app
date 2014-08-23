#include "framework.h"
#include <malloc.h>


// interesting function
/*bool CLASS_DECL_AURA __custom_log_font(UINT nIDS, LOGFONTW* pLogFont)
{
   ENSURE_ARG(pLogFont != NULL);
   ASSERT(nIDS != 0);

   char szFontInfo[256];
   if (!::core::LoadString(nIDS, szFontInfo,_countof(szFontInfo)))
      return FALSE;

   LPTSTR lpszSize = _tcschr(szFontInfo, '\n');
   if (lpszSize != NULL)
   {
      // get point size and convert to pixels
      pLogFont->lfHeight = _ttoi(lpszSize+1);
      pLogFont->lfHeight =
         MulDiv(pLogFont->lfHeight, afxData.cyPixelsPerInch, 72);
      *lpszSize = '\0';
   }
   ::core::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
   return TRUE;
}*/

bool CLASS_DECL_AURA __is_combo_box_control(oswindow oswindow, UINT nStyle)
{
   if (oswindow == NULL)
      return FALSE;
   // do cheap style compare first
   if ((UINT)(::GetWindowLong(oswindow, GWL_STYLE) & 0x0F) != nStyle)
      return FALSE;

   // do expensive classname compare next
   char szCompare[_countof("combobox")+1];
   ::GetClassName(oswindow, szCompare, _countof(szCompare));
   return ::__invariant_stricmp(szCompare, "combobox") == 0;
}

bool CLASS_DECL_AURA __compare_class_name(oswindow oswindow, const char * lpszClassName)
{
   ASSERT(::IsWindow(oswindow));
   char szTemp[32];
   ::GetClassName(oswindow, szTemp, _countof(szTemp));
   return ::__invariant_stricmp(szTemp, lpszClassName) == 0;
}

oswindow CLASS_DECL_AURA __child_window_from_point(oswindow oswindow, POINT pt)
{
   ASSERT(oswindow != NULL);

   // check child windows
   ::ClientToScreen(oswindow, &pt);
   ::oswindow oswindow_Child = ::GetWindow(oswindow, GW_CHILD);
   for (; oswindow_Child != NULL; oswindow_Child = ::GetWindow(oswindow_Child, GW_HWNDNEXT))
   {
      if (__get_dialog_control_id(oswindow_Child) != (WORD)0 &&
         (::GetWindowLong(oswindow_Child, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point hits the child interaction_impl
         rect rect;
         ::GetWindowRect(oswindow_Child, rect);
         if (rect.contains(pt))
            return oswindow_Child;
      }
   }

   return NULL;    // not found
}

