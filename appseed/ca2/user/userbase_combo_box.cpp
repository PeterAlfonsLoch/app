#include "framework.h"


namespace user
{


   combo_box::combo_box(sp(::ca::application) papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::edit_plain_text(papp),
      ::user::combo_box(papp)
   {

   }

   combo_box::~combo_box()
   {

      DestroyWindow();

   }


   bool combo_box::create(sp(::user::interaction) pParentWnd, id id)
   {
      sp(::user::interaction) pWnd = this;
      return pWnd->create(pParentWnd, id);
   }

#ifdef WINDOWSEX
    //Derived class is responsible for implementing these handlers
      //for owner/self draw controls (except for the optional DeleteItem)
   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
      { ASSERT(FALSE); }
   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
      { ASSERT(FALSE); }
   int32_t combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
      { ASSERT(FALSE); return 0; }
   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
      { /* default to nothing */ }
#endif

   bool combo_box::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,
      LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(wParam);
      switch (message)
      {
      case WM_DRAWITEM:
#ifdef WINODWSEX
         ASSERT(pResult == ::null());       // no return value expected
         DrawItem((LPDRAWITEMSTRUCT)lParam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_MEASUREITEM:
#ifdef WINODWSEX
         ASSERT(pResult == ::null());       // no return value expected
         MeasureItem((LPMEASUREITEMSTRUCT)lParam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_COMPAREITEM:
#ifdef WINODWSEX
         ASSERT(pResult != ::null());       // return value expected
         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)lParam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_DELETEITEM:
#ifdef WINODWSEX
         ASSERT(pResult == ::null());       // no return value expected
         DeleteItem((LPDELETEITEMSTRUCT)lParam);
#else
         throw todo(get_app());
#endif
         break;
      default:
         // trans return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);
         return FALSE;
      }
      return TRUE;
   }

   void combo_box::GetLBText(index nIndex, string & rString)
   {
      ASSERT(IsWindow());
      GetLBText(nIndex, rString.GetBufferSetLength(GetLBTextLen(nIndex)));
      rString.ReleaseBuffer();
   }

   //::count combo_box::get_count()
     // { ASSERT(IsWindow()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index combo_box::get_cur_sel()
     // { ASSERT(IsWindow()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index combo_box::set_cur_sel(index nSelect)
     // { ASSERT(IsWindow()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool combo_box::GetEditSel(strsize & nStartChar, strsize & nEndChar)
   {
/*      ASSERT(IsWindow()); uint32_t dw = uint32_t(send_message( CB_GETEDITSEL, 0, 0));
      nStartChar = LOWORD(dw);
      nEndChar = LOWORD(dw);*/
      return TRUE;
   }
   bool combo_box::LimitText(strsize nMaxChars)
   {
      //ASSERT(IsWindow());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != FALSE;
      return true;
   }

   bool combo_box::SetEditSel(strsize nStartChar, strsize nEndChar)
   {
      //ASSERT(IsWindow());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != FALSE;
      return true;
   }

   uint_ptr combo_box::GetItemData(index nIndex)
   {

      //ASSERT(IsWindow());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   index combo_box::SetItemData(index nIndex, uint_ptr dwItemData)
   {

      //ASSERT(IsWindow());

      //return (index)send_message( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

      return -1;

   }

   void * combo_box::GetItemDataPtr(index nIndex)
   {

      //ASSERT(IsWindow()); return (LPVOID)GetItemData(nIndex);

      return ::null();

   }

   index combo_box::SetItemDataPtr(index nIndex, void * pData)
   {

      //ASSERT(IsWindow());

      //return SetItemData(nIndex, (uint_ptr)(LPVOID)pData);

      return -1;

   }

   index combo_box::GetLBText(index nIndex, LPSTR lpszText)
   {

      //ASSERT(IsWindow());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)lpszText);

      return -1;

   }

   strsize combo_box::GetLBTextLen(index nIndex)
   {

      //ASSERT(IsWindow());

      //return (strsize)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }

   void combo_box::ShowDropDown(bool bShowIt)
   {

      //ASSERT(IsWindow());

      //send_message( CB_SHOWDROPDOWN, bShowIt, 0);

   }

   index combo_box::AddString(const char * lpszString)
   {

      //ASSERT(IsWindow());

      //return (index) send_message( CB_ADDSTRING, 0, (LPARAM)lpszString);

      return -1;

   }

   index combo_box::DeleteString(index nIndex)
   {

      //ASSERT(IsWindow());

      //return (index) send_message( CB_DELETESTRING, nIndex, 0);

      return -1;

   }

   index combo_box::InsertString(index nIndex, const char * lpszString)
   {

      //ASSERT(IsWindow());

      //return (int32_t)send_message( CB_INSERTSTRING, nIndex, (LPARAM)lpszString);

      return -1;

   }

   void combo_box::ResetContent()
   {

      //ASSERT(IsWindow());

      //send_message( CB_RESETCONTENT, 0, 0);

   }

   index combo_box::Dir(index attr, const char * lpszWildCard)
   {

//      ASSERT(IsWindow());

//      return (index)send_message( CB_DIR, attr, (LPARAM)lpszWildCard);

      return -1;

   }

   index combo_box::FindString(index nStartAfter, const char * lpszString)
   {

//      ASSERT(IsWindow());

//      return (index)send_message( CB_FINDSTRING, nStartAfter, (LPARAM)lpszString);

      return -1;

   }

   index combo_box::SelectString(index nStartAfter, const char * lpszString)
   {

//      ASSERT(IsWindow());

//      return (index)send_message( CB_SELECTSTRING, nStartAfter, (LPARAM)lpszString);

      return -1;

   }

   void combo_box::clear()
   {

      //ASSERT(IsWindow());

      //send_message(WM_CLEAR, 0, 0);

   }

   void combo_box::copy()
   {

      //ASSERT(IsWindow());

      //send_message(WM_COPY, 0, 0);

   }

   void combo_box::Cut()
   {

      //ASSERT(IsWindow());

      //send_message( WM_CUT, 0, 0);

   }

   void combo_box::Paste()
   {

      //ASSERT(IsWindow());

      //send_message( WM_PASTE, 0, 0);

   }

   int32_t combo_box::SetItemHeight(index nIndex, UINT cyItemHeight)
   {

      //ASSERT(IsWindow());

      //return (int32_t)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }

   int32_t combo_box::GetItemHeight(index nIndex)
   {

      //ASSERT(IsWindow());

      //return (int32_t)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }

   index combo_box::FindStringExact(index nIndexStart, const char * lpszFind)
   {

      //ASSERT(IsWindow());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);

      return -1;

   }

   int32_t combo_box::SetExtendedUI(bool bExtended)
   {

      //ASSERT(IsWindow());

      //return (int32_t)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }

   bool combo_box::GetExtendedUI()
   {

      //ASSERT(IsWindow());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }

   void combo_box::GetDroppedControlRect(LPRECT lprect)
   {

      //ASSERT(IsWindow());

      //send_message( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)lprect);

   }

   bool combo_box::GetDroppedState()
   {

      //ASSERT(IsWindow());

      //return send_message( CB_GETDROPPEDSTATE, 0, 0L) != 0;

      return false;

   }

   LCID combo_box::GetLocale()
   {

      //ASSERT(IsWindow());

      //return (LCID)send_message( CB_GETLOCALE, 0, 0);

      return -1; // everywhere

   }

   LCID combo_box::SetLocale(LCID nNewLocale)
   {

      //ASSERT(IsWindow());

      //return (LCID)send_message( CB_SETLOCALE, (WPARAM)nNewLocale, 0);

      return nNewLocale; // set where it is

   }

   index combo_box::GetTopIndex()
   {

      //ASSERT(IsWindow());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }

   index combo_box::SetTopIndex(index nIndex)
   {

      //ASSERT(IsWindow());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }

   ::count combo_box::InitStorage(::count nItems, UINT nBytes)
   {

      //ASSERT(IsWindow());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void combo_box::SetHorizontalExtent(UINT nExtent)
   {

      //ASSERT(IsWindow());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }

   UINT combo_box::GetHorizontalExtent()
   {

      //ASSERT(IsWindow());

      //return (UINT)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }

   int32_t combo_box::SetDroppedWidth(UINT nWidth)
   {

//      ASSERT(IsWindow());

//      return (int32_t)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

         return -1;

   }

   int32_t combo_box::GetDroppedWidth()
   {

//      ASSERT(IsWindow());

//      return (int32_t)send_message( CB_GETDROPPEDWIDTH, 0, 0);

         return -1;

   }


} // namespace user




