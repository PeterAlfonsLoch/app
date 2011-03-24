#include "StdAfx.h"

namespace userbase
{

   BOOL combo_box::create(DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd,
         UINT nID)
   {
      ::user::interaction* pWnd = this;
      return pWnd->create("COMBOBOX", NULL, dwStyle, rect, pParentWnd, nID);
   }

   combo_box::~combo_box()
   {
      DestroyWindow();
   }

   // Derived class is responsible for implementing these handlers
   //   for owner/self draw controls (except for the optional DeleteItem)
   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
      { ASSERT(FALSE); }
   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
      { ASSERT(FALSE); }
   int combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
      { ASSERT(FALSE); return 0; }
   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
      { /* default to nothing */ }

   BOOL combo_box::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,
      LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(wParam);
      switch (message)
      {
      case WM_DRAWITEM:
         ASSERT(pResult == NULL);       // no return value expected
         DrawItem((LPDRAWITEMSTRUCT)lParam);
         break;
      case WM_MEASUREITEM:
         ASSERT(pResult == NULL);       // no return value expected
         MeasureItem((LPMEASUREITEMSTRUCT)lParam);
         break;
      case WM_COMPAREITEM:
         ASSERT(pResult != NULL);       // return value expected
         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)lParam);
         break;
      case WM_DELETEITEM:
         ASSERT(pResult == NULL);       // no return value expected
         DeleteItem((LPDELETEITEMSTRUCT)lParam);
         break;
      default:
         // trans return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);
         return FALSE;
      }
      return TRUE;
   }

   void combo_box::GetLBText(int nIndex, string & rString)
   {
      ASSERT(IsWindow());
      GetLBText(nIndex, rString.GetBufferSetLength(GetLBTextLen(nIndex)));
      rString.ReleaseBuffer();
   }

   combo_box::combo_box()
      { }
   int combo_box::get_count()
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETCOUNT, 0, 0); }
   int combo_box::get_cur_sel()
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETCURSEL, 0, 0); }
   int combo_box::set_cur_sel(int nSelect)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   DWORD combo_box::GetEditSel()
      { ASSERT(IsWindow()); return DWORD(SendMessage( CB_GETEDITSEL, 0, 0)); }
   BOOL combo_box::LimitText(int nMaxChars)
      { ASSERT(IsWindow()); return (BOOL)SendMessage( CB_LIMITTEXT, nMaxChars, 0); }
   BOOL combo_box::SetEditSel(int nStartChar, int nEndChar)
      { ASSERT(IsWindow()); return (BOOL)SendMessage( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)); }
   DWORD_PTR combo_box::GetItemData(int nIndex)
      { ASSERT(IsWindow()); return SendMessage( CB_GETITEMDATA, nIndex, 0); }
   int combo_box::SetItemData(int nIndex, DWORD_PTR dwItemData)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData); }
   void * combo_box::GetItemDataPtr(int nIndex)
      { ASSERT(IsWindow()); return (LPVOID)GetItemData(nIndex); }
   int combo_box::SetItemDataPtr(int nIndex, void * pData)
      { ASSERT(IsWindow()); return SetItemData(nIndex, (DWORD_PTR)(LPVOID)pData); }
   int combo_box::GetLBText(int nIndex, LPTSTR lpszText)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETLBTEXT, nIndex, (LPARAM)lpszText); }
   int combo_box::GetLBTextLen(int nIndex)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETLBTEXTLEN, nIndex, 0); }
   void combo_box::ShowDropDown(BOOL bShowIt)
      { ASSERT(IsWindow()); SendMessage( CB_SHOWDROPDOWN, bShowIt, 0); }
   int combo_box::AddString(const char * lpszString)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_ADDSTRING, 0, (LPARAM)lpszString); }
   int combo_box::DeleteString(UINT nIndex)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_DELETESTRING, nIndex, 0);}
   int combo_box::InsertString(int nIndex, const char * lpszString)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_INSERTSTRING, nIndex, (LPARAM)lpszString); }
   void combo_box::ResetContent()
      { ASSERT(IsWindow()); SendMessage( CB_RESETCONTENT, 0, 0); }
   int combo_box::Dir(UINT attr, const char * lpszWildCard)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_DIR, attr, (LPARAM)lpszWildCard); }
   int combo_box::FindString(int nStartAfter, const char * lpszString)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_FINDSTRING, nStartAfter,
         (LPARAM)lpszString); }
   int combo_box::SelectString(int nStartAfter, const char * lpszString)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SELECTSTRING,
         nStartAfter, (LPARAM)lpszString); }
   void combo_box::clear()
      { ASSERT(IsWindow()); SendMessage( WM_CLEAR, 0, 0); }
   void combo_box::copy()
      { ASSERT(IsWindow()); SendMessage( WM_COPY, 0, 0); }
   void combo_box::Cut()
      { ASSERT(IsWindow()); SendMessage( WM_CUT, 0, 0); }
   void combo_box::Paste()
      { ASSERT(IsWindow()); SendMessage( WM_PASTE, 0, 0); }
   int combo_box::SetItemHeight(int nIndex, UINT cyItemHeight)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0)); }
   int combo_box::GetItemHeight(int nIndex)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETITEMHEIGHT, nIndex, 0L); }
   int combo_box::FindStringExact(int nIndexStart, const char * lpszFind)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind); }
   int combo_box::SetExtendedUI(BOOL bExtended )
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETEXTENDEDUI, bExtended, 0L); }
   BOOL combo_box::GetExtendedUI()
      { ASSERT(IsWindow()); return (BOOL)SendMessage( CB_GETEXTENDEDUI, 0, 0L); }
   void combo_box::GetDroppedControlRect(LPRECT lprect)
      { ASSERT(IsWindow()); SendMessage( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)lprect); }
   BOOL combo_box::GetDroppedState()
      { ASSERT(IsWindow()); return (BOOL)SendMessage( CB_GETDROPPEDSTATE, 0, 0L); }
   LCID combo_box::GetLocale()
      { ASSERT(IsWindow()); return (LCID)SendMessage( CB_GETLOCALE, 0, 0); }
   LCID combo_box::SetLocale(LCID nNewLocale)
      { ASSERT(IsWindow()); return (LCID)SendMessage( CB_SETLOCALE, (WPARAM)nNewLocale, 0); }
   int combo_box::GetTopIndex()
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETTOPINDEX, 0, 0); }
   int combo_box::SetTopIndex(int nIndex)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETTOPINDEX, nIndex, 0); }
   int combo_box::InitStorage(int nItems, UINT nBytes)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_INITSTORAGE, (WPARAM)nItems, nBytes); }
   void combo_box::SetHorizontalExtent(UINT nExtent)
      { ASSERT(IsWindow()); SendMessage( CB_SETHORIZONTALEXTENT, nExtent, 0); }
   UINT combo_box::GetHorizontalExtent()
      { ASSERT(IsWindow()); return (UINT)SendMessage( CB_GETHORIZONTALEXTENT, 0, 0); }
   int combo_box::SetDroppedWidth(UINT nWidth)
      { ASSERT(IsWindow()); return (int)SendMessage( CB_SETDROPPEDWIDTH, nWidth, 0); }
   int combo_box::GetDroppedWidth()
      { ASSERT(IsWindow()); return (int)SendMessage( CB_GETDROPPEDWIDTH, 0, 0); }


} // namespace userbase