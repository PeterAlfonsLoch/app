#include "framework.h"


namespace user
{


   combo_box::combo_box(sp(::base::application) papp) :
      element(papp),
      ::user::scroll_view(papp),
      ::data::data_listener(papp),
      ::colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp)
   {

      m_iSel                  = -1;
      m_bCaseSensitiveMatch   = false;
      m_typeComboList         = System.type_info < simple_combo_list > ();
      m_estyle                = style_simply;
      m_bEdit                 = true;
      m_crText                = ARGB(255, 0, 0, 0);

   }

   combo_box::~combo_box()
   {
   }


   void combo_box::install_message_handling(::message::dispatch * pdispatch)
   {

      if(m_bEdit)
      {

         ::user::edit_plain_text::install_message_handling(pdispatch);

      }
      else
      {

         ::user::control::install_message_handling(pdispatch);

      }

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &combo_box::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &combo_box::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_SETFOCUS, pdispatch, this, &combo_box::_001OnSetFocus);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &combo_box::_001OnMouseMove);

   }


   void combo_box::_001OnDrawStaticText(::draw2d::graphics * pdc)
   {

      string strText;

      _001GetText(strText);

      rect rectClient;

      GetClientRect(rectClient);

      pdc->set_text_color(m_crText);

      rect rectText;

      get_element_rect(rectText, element_text);;

      int32_t iMargin = rectClient.height() / 8;

      rectText.deflate(iMargin, iMargin);

      pdc->SelectObject(GetFont());

      pdc->draw_text(strText, rectText, 0);

   }



   void combo_box::_001OnDrawVerisimple(::draw2d::graphics * pdc)
   {

      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001OnDraw(pdc);

      }
      else
      {

         _001OnDrawStaticText(pdc);

      }

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::brush_sp br(allocer());

//      int32_t iMargin = rectClient.height() / 8;

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      br->create_solid(ARGB(184, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectDropDown);

      ::draw2d::path_sp path(allocer());

      point_array pointa;

      get_simple_drop_down_open_arrow_path(pointa);

      if(pointa.get_count() >= 3)
      {

         path->add_line(pointa[0], pointa[1]);

         for(index i = 2; i < pointa.get_count(); i++)
         {

            path->add_line(pointa[i]);

         }

         path->add_line(pointa[0]);

      }

      br->create_solid(ARGB(210, 77, 184, 49));

      pdc->SelectObject(br);

      pdc->fill_path(path);



   }

   void combo_box::_001OnDrawSimply(::draw2d::graphics * pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::brush_sp br(allocer());

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001OnDraw(pdc);

      }
      else
      {

         pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

         br->create_solid(ARGB(84, 255, 255, 255));

         pdc->SelectObject(br);

         pdc->FillRectangle(rectClient);

         pdc->set_alpha_mode(::draw2d::alpha_mode_set);

         color ca;

         ca.set_rgb(RGB(227, 227, 210));

         ca.hls_rate(0.0, -0.33, -0.23);

         COLORREF crBorder = ca.get_rgb() | (0xff << 24);

         pdc->Draw3dRect(rectClient, crBorder, crBorder);

         _001OnDrawStaticText(pdc);

      }


      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);


#ifdef WINDOWSEX

      int32_t iMargin = rectClient.height() / 8;

      rect r = rectDropDown;

      int32_t i = 0;

      int32_t iColorRate = 6;

      for(int32_t radius = iMargin * 2 / 3; radius >= 1; radius--)
      {

         iColorRate = ((iMargin * 2 / 3) - radius) * 26 / (iMargin * 2 / 3);
         {
            if(i == 0)
            {
               COLORREF ca(ARGB(230, 130, 130, 120));
               pdc->draw_round_top_left(r, ca, radius, 1);
            }
            else if(i == 1)
            {
               COLORREF ca(ARGB(230, 210, 210, 200));
               pdc->draw_round_top_left(r, ca, radius, 1);
            }
            else
            {
               COLORREF ca(ARGB(230, 230 - iColorRate, 230 - iColorRate, 220 - iColorRate));
               pdc->draw_round_top_left(r, ca, radius, 1);
            }
         }
         {
            if(i == 0)
            {
               COLORREF ca(ARGB(230, 130, 130, 120));
               pdc->draw_round_bottom_right(r, ca, radius, 1);
            }
            else if(i == 1)
            {
               COLORREF ca(ARGB(230, 210, 210, 200));
               pdc->draw_round_bottom_right(r, ca, radius, 1);
            }
            else
            {
               COLORREF ca(ARGB(230, 190 + iColorRate, 190 + iColorRate, 180 + iColorRate));
               pdc->draw_round_bottom_right(r, ca, radius, 1);
            }
         }

         r.inflate(-1, -1);

         i++;

      }

      rect rectDropIn(rectDropDown);

      rectDropIn.deflate(iMargin * 2 / 3, iMargin * 2 / 3);

      br->create_solid(ARGB(210, 230 - iColorRate, 230 - iColorRate, 220 - iColorRate));

      pdc->SelectObject(br);

      rectDropIn.right++;
      rectDropIn.bottom++;
      pdc->FillRectangle(rectDropIn);


      br->create_solid(ARGB(210, 77, 184, 49));


      ::draw2d::path_sp path(allocer());

      point_array pointa;

      get_simple_drop_down_open_arrow_path(pointa);

      if(pointa.get_count() >= 3)
      {

         path->add_line(pointa[0], pointa[1]);

         for(index i = 2; i < pointa.get_count(); i++)
         {

            path->add_line(pointa[i]);

         }

         path->add_line(pointa[0]);

      }

      br->create_solid(ARGB(210, 77, 184, 49));

      pdc->SelectObject(br);

      pdc->fill_path(path);

#else

      throw todo(get_app());

#endif

   }


   void combo_box::_001OnDraw(::draw2d::graphics * pdc)
   {

      //if(m_estyle == style_simply)
      if(m_plist == NULL)
      {

         _001OnDrawSimply(pdc);

      }
      else
      {

         _001OnDrawVerisimple(pdc);

      }

   }

   void combo_box::_001GetText(string & str) const
   {

      if(m_bEdit)
      {

         if(m_iSel < 0)
         {

            ::user::edit_plain_text::_001GetText(str);

         }
         else
         {

            _001GetListText(m_iSel, str);

         }

      }
      else
      {

         if(m_iSel < 0)
         {

            str = m_strText;

         }
         else
         {

            _001GetListText(m_iSel, str);

         }

      }

   }

   void combo_box::_001SetText(const string & str, ::action::context actioncontext)
   {

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001SetText(str, actioncontext);

      }
      else
      {

         m_strText = str;

         _001OnAfterChangeText(actioncontext);

      }



   }


   void combo_box::_001GetListText(index iSel, string & str) const
   {

   }


   index combo_box::_001FindListText(const string & str) const
   {

      ::count ca = _001GetListCount();

      string strItem;

      for(index i = 0; i < ca; i++)
      {

         _001GetListText(i, strItem);

         if(m_bCaseSensitiveMatch)
         {

            if(str.Compare(strItem) == 0)
               return i;

         }
         else
         {

            if(str.CompareNoCase(strItem) == 0)
               return i;

         }

      }

      return -1;

   }


   index combo_box::_001GetListCount() const
   {

      return 0;

   }


   bool combo_box::get_element_rect(LPRECT lprect, e_element eelement) const
   {

      if(eelement == element_drop_down)
      {

         rect rectClient;

         ((combo_box *) this)->GetClientRect(rectClient);

         int32_t iMargin = rectClient.height() / 8;

         rect rectDropDown;

         rectDropDown = rectClient;

         int32_t iW = rectClient.height() * 5 / 8;

         rectDropDown.right      -= iMargin;
         rectDropDown.bottom     -= iMargin;
         rectDropDown.top        += iMargin;
         rectDropDown.left       =  rectDropDown.right - iW;

         *lprect = rectDropDown;

         return true;

      }
      else if(eelement == element_text)
      {

         rect rectClient;

         ((combo_box *) this)->GetClientRect(rectClient);

         int32_t iMargin = rectClient.height() / 8;

         int32_t iW = rectClient.height() * 5 / 8;

         rect rectText = rectClient;

         rectText.deflate(iMargin, iMargin);

         rectText.right -= (iW + iMargin);

         *lprect = rectText;

         return true;

      }

      return false;

   }

   void combo_box::get_simple_drop_down_open_arrow_path(point_array & pointa) const
   {

      rect rectClient;

      ((combo_box *) this)->GetClientRect(rectClient);

      int32_t iMargin = rectClient.height() / 8;

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      pointa.add(rectDropDown.left + iMargin, rectDropDown.top + iMargin * 2);
      pointa.add(rectDropDown.right - iMargin, rectDropDown.top + iMargin * 2);
      pointa.add((rectDropDown.right + rectDropDown.left) / 2, rectDropDown.bottom - iMargin * 2);

   }



   ::user::control::e_element combo_box::hit_test(point pt) const
   {

      rect rectElement;

      if(get_element_rect(rectElement, element_drop_down))
      {
         if(rectElement.contains(pt))
            return element_drop_down;
      }

      if(get_element_rect(rectElement, element_text))
      {
         if(rectElement.contains(pt))
            return element_text;
      }

      return element_none;

   }

   void combo_box::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if(hit_test(pt) == element_drop_down)
      {

         _001ToggleDropDown();

         pmouse->m_bRet = true;

      }

   }

   void combo_box::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if (hit_test(pt) == element_drop_down)
      {

         pmouse->m_ecursor = ::visual::cursor_arrow;

         pmouse->m_bRet = true;

      }

   }


   void combo_box::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if (hit_test(pt) == element_drop_down)
      {

         pmouse->m_bRet = true;

      }

   }

   void combo_box::_001OnSetFocus(signal_details * pobj)
   {

//      SCAST_PTR(::message::set_focus, pfocus, pobj);

   }

   void combo_box::_001ToggleDropDown()
   {


      defer_create_combo_list();

      _001ShowDropDown(!m_plist->IsWindowVisible());


   }


   void combo_box::_001ShowDropDown(bool bShow)
   {


      if(bShow)
      {

         defer_create_combo_list();

         size sizeFull;

         m_plist->query_full_size(sizeFull);

         rect rectWindow;

         GetWindowRect(rectWindow);

         rect rectMonitor;

         Session.get_best_monitor(rectMonitor, rectWindow);

         bool bDown = true;

         if(sizeFull.cy > (rectMonitor.bottom - rectWindow.bottom))
         {
            bDown = false;
         }

         size sizeList;

         rect rectList;

         rectList = rectMonitor;

         sizeList.cx = min(sizeFull.cx, rectMonitor.width());

         {

            sizeList.cx = max(sizeList.cx, rectWindow.width());

         }

         if(sizeList.cx < rectWindow.width())
         {

            rectList.left = rectWindow.left;

         }
         else if(sizeList.cx < rectMonitor.width())
         {

            rectList.left = min(rectMonitor.right - sizeList.cx, ((rectWindow.left + rectWindow.right) / 2) - sizeList.cx / 2);

         }

         rectList.right = rectList.left + sizeList.cx;

         if(bDown)
         {

            rectList.top = rectWindow.bottom + 1;

            sizeList.cy = min(sizeFull.cy, (rectMonitor.bottom - rectWindow.bottom));
            sizeList.cy -= sizeList.cy % m_plist->_001GetItemHeight();


            rectList.bottom = rectList.top + sizeList.cy;




         }
         else
         {
            rectList.bottom = rectWindow.top - 1;

            sizeList.cy = min(sizeFull.cy, (rectWindow.top - rectMonitor.top));
            sizeList.cy -= sizeList.cy % m_plist->_001GetItemHeight();

            rectList.top = rectList.bottom - sizeList.cy;

         }

         m_plist->SetWindowPos(ZORDER_TOPMOST, rectList.left, rectList.top, rectList.width(), rectList.height(), SWP_SHOWWINDOW);

         m_plist->SetActiveWindow();

         m_plist->SetFocus();


      }
      else
      {



         if(m_plist != NULL)
         {

            m_plist->ShowWindow(SW_HIDE);

            m_plist->post_message(WM_CLOSE);

            m_plist.release();

         }

      }


   }


   void combo_box::defer_create_combo_list()
   {

      if(m_plist == NULL)
      {

         sp(element) pca = Application.alloc(m_typeComboList);

         m_plist =  (pca);

         if(m_plist == NULL)
         {
            pca.release();
            throw resource_exception(get_app());
         }

         m_plist->m_pcombo = this;

      }

      if(!m_plist->IsWindow())
      {

         if(!m_plist->CreateEx(0, NULL, "combo_list", 0, rect(0, 0, 0, 0), NULL, 0, NULL))
         {
            m_plist.release();
            throw resource_exception(get_app());
         }

      }

      rect rectClient;

      GetClientRect(rectClient);

      m_plist->SetFont(GetFont());

      m_plist->set_text_color(m_crText);

      m_plist->m_iItemHeight = min(24, rectClient.height());



   }

   void combo_box::_001SetCurSel(index iSel, ::action::context actioncontext)
   {

      if (m_iSel != iSel)
      {

         m_iSel = iSel;

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_after_change_cur_sel;
         ev.m_actioncontext = actioncontext;
         //if(!get_parent()->BaseOnControlEvent(&ev))
         BaseOnControlEvent(&ev);

      }

      string strItem;

      _001GetListText(iSel, strItem);

      _001SetText(strItem, actioncontext);

   }


   index combo_box::_001GetCurSel()
   {

      return m_iSel;

   }

   void combo_box::layout()
   {

      if(m_bEdit)
      {

         ::user::edit_plain_text::layout();

      }


/*      ::draw2d::font_sp fontxyz(allocer());

      rect rectClient;

      GetClientRect(rectClient);

      fontxyz->m_dFontSize = rectClient.height() * 0.4;
      fontxyz->m_eunitFontSize = ::draw2d::unit_pixel;
      fontxyz->m_bUpdated = false;

      SetFont(fontxyz);*/



   }

   void combo_box::_001OnAfterChangeText(::action::context actioncontext)
   {

      string str;

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001GetText(str);

      }
      else
      {

         str = m_strText;

      }

      m_iSel = _001FindListText(str);

   }


   void combo_box::_001OnInitialUpdate(signal_details * pobj)
   {

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001OnInitialUpdate(pobj);

      }
      else
      {

         ::user::control::_001OnInitialUpdate(pobj);

      }


   }




   bool combo_box::create(sp(::user::interaction) pParentWnd, id id)
   {

      if (!::user::edit_plain_text::create(pParentWnd, id))
         return false;

      return true;

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

   bool combo_box::OnChildNotify(::message::base * pbase)
   {

      switch (pbase->m_uiMessage)
      {
      case WM_DRAWITEM:
#ifdef WINODWSEX
         DrawItem((LPDRAWITEMSTRUCT)pbase->m_lparam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_MEASUREITEM:
#ifdef WINODWSEX
         MeasureItem((LPMEASUREITEMSTRUCT)pbase->m_lparam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_COMPAREITEM:
#ifdef WINODWSEX
         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pbase->m_lparam);
#else
         throw todo(get_app());
#endif
         break;
      case WM_DELETEITEM:
#ifdef WINODWSEX
         DeleteItem((LPDELETEITEMSTRUCT)pbase->m_lparam);
#else
         throw todo(get_app());
#endif
         break;
      default:
         return ::user::interaction::OnChildNotify(pbase);
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

      return NULL;

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

   index combo_box::AddString(const char * lpszString, uint_ptr dwItemData)
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


   void combo_box::_001SetCurSelByData(uint_ptr ui, ::action::context actioncontext)
   {

      ::count c = _001GetListCount();

      index iSel = -1;
      
      for (index i = 0; i < c; i++)
      {

         if (GetItemData(i) == ui)
         {

            iSel = i;

            break;

         }

      }

      if (iSel < 0)
         return;


      _001SetCurSel(iSel, actioncontext);

   }


   void combo_box::SetFont(::draw2d::font* pFont, bool bRedraw)
   {

      edit_plain_text::SetFont(pFont, bRedraw);

      if (m_plist != NULL)
      {

         m_plist->SetFont(pFont, bRedraw);

      }

   }


   void combo_box::set_text_color(COLORREF crText)
   {

      edit_plain_text::set_text_color(crText);

      if (m_plist != NULL)
      {

         m_plist->m_crText = crText;

      }

   }


} // namespace user





