#include "framework.h"


namespace user
{


   combo_box::combo_box(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::edit_plain_text(papp)
   {

      m_iSel                  = -1;
      m_bCaseSensitiveMatch   = false;
      m_plist                 = NULL;
      m_typeComboList         = typeid(simple_combo_list);
      m_estyle                = style_simply;
      m_bEdit                 = true;

   }

   combo_box::~combo_box()
   {
   }


   void combo_box::install_message_handling(::gen::message::dispatch * pdispatch)
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

   }


   void combo_box::_001OnDrawStaticText(::ca::graphics * pdc)
   {

      string strText;

      _001GetText(strText);

      rect rectClient;

      GetClientRect(rectClient);

      ::ca::brush_sp br(get_app());

      br->create_solid(ARGB(84, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      br->create_solid(ARGB(255, 84, 84, 77));

      pdc->SelectObject(br);

      rect rectText;

      get_element_rect(rectText, element_text);;

      int32_t iMargin = rectClient.height() / 8;

      rectText.deflate(iMargin, iMargin);

      pdc->SelectObject(GetFont());

      pdc->draw_text(strText, rectText, 0);

   }



   void combo_box::_001OnDrawVerisimple(::ca::graphics * pdc)
   {

      pdc->set_alpha_mode(::ca::alpha_mode_blend);

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

      ::ca::brush_sp br(get_app());

      int32_t iMargin = rectClient.height() / 8;

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      br->create_solid(ARGB(184, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectDropDown);

      ::ca::graphics_path_sp path(get_app());

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

   void combo_box::_001OnDrawSimply(::ca::graphics * pdc)
   {

      pdc->set_alpha_mode(::ca::alpha_mode_blend);

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

      ::ca::brush_sp br(get_app());

      int32_t iMargin = rectClient.height() / 8;

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      rect r = rectDropDown;

      int32_t iColorRate;

      int32_t i = 0;

#ifdef WINDOWSEX

      simple_graphics g;

      g.reference_os_data((Gdiplus::Graphics *) pdc->get_os_data());

      for(int32_t radius = iMargin * 2 / 3; radius >= 1; radius--)
      {

         iColorRate = ((iMargin * 2 / 3) - radius) * 26 / (iMargin * 2 / 3);
         {
            if(i == 0)
            {
               COLORREF c(ARGB(230, 130, 130, 120));
               g.draw_round_top_left(r, c, radius, 1);
            }
            else if(i == 1)
            {
               COLORREF c(ARGB(230, 210, 210, 200));
               g.draw_round_top_left(r, c, radius, 1);
            }
            else
            {
               COLORREF c(ARGB(230, 230 - iColorRate, 230 - iColorRate, 220 - iColorRate));
               g.draw_round_top_left(r, c, radius, 1);
            }
         }
         {
            if(i == 0)
            {
               COLORREF c(ARGB(230, 130, 130, 120));
               g.draw_round_bottom_right(r, c, radius, 1);
            }
            else if(i == 1)
            {
               COLORREF c(ARGB(230, 210, 210, 200));
               g.draw_round_bottom_right(r, c, radius, 1);
            }
            else
            {
               COLORREF c(ARGB(230, 190 + iColorRate, 190 + iColorRate, 180 + iColorRate));
               g.draw_round_bottom_right(r, c, radius, 1);
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


      ::ca::graphics_path_sp path(get_app());

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


   void combo_box::_001OnDraw(::ca::graphics * pdc)
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

   void combo_box::_001GetText(string & str)
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

   void combo_box::_001SetText(const char * psz)
   {

      if(m_bEdit)
      {

         ::user::edit_plain_text::_001SetText(psz);

      }
      else
      {

         m_strText = psz;

         _001OnAfterChangeText();

      }



   }


   void combo_box::_001GetListText(index iSel, string & str) const
   {

   }


   index combo_box::_001FindListText(const string & str) const
   {

      count c = _001GetListCount();

      string strItem;

      for(index i = 0; i < c; i++)
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

   void combo_box::_001OnLButtonDown(gen::signal_object * pobj)
   {

      SCAST_PTR(gen::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if(hit_test(pt) == element_drop_down)
      {

         _001ToggleDropDown();

      }

   }


   void combo_box::_001OnLButtonUp(gen::signal_object * pobj)
   {

      SCAST_PTR(gen::message::mouse, pmouse, pobj);

   }

   void combo_box::_001OnSetFocus(gen::signal_object * pobj)
   {

      SCAST_PTR(gen::message::set_focus, pfocus, pobj);

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

         index iMonitor = System.get_best_intersection_monitor(rectWindow);

         rect rectMonitor;

         System.get_monitor_rect(iMonitor, rectMonitor);

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

            m_plist->PostMessage(WM_CLOSE, 0, 0);

            m_plist = NULL;

         }

      }


   }


   void combo_box::defer_create_combo_list()
   {

      if(m_plist == NULL)
      {

         ::ca::ca * pca = Application.alloc(m_typeComboList);

         m_plist = dynamic_cast < combo_list * > (pca);

         if(m_plist == NULL)
         {
            delete pca;
            throw resource_exception(get_app());
         }

         m_plist->m_pcombo = this;

      }

      if(!m_plist->IsWindow())
      {

         if(!m_plist->CreateEx(0, m_plist->GetIconWndClass(0, 0), "combo_list", 0, rect(0, 0, 0, 0), NULL, 0, NULL))
         {
            gen::del(m_plist);
            throw resource_exception(get_app());
         }

      }

      rect rectClient;

      GetClientRect(rectClient);

      m_plist->m_iItemHeight = min(24, rectClient.height());



   }

   void combo_box::_001SetCurSel(index iSel)
   {

      string strItem;

      _001GetListText(iSel, strItem);

      _001SetText(strItem);

      m_iSel = iSel;

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


      ::ca::font_sp fontxyz(get_app());

      rect rectClient;

      GetClientRect(rectClient);

      fontxyz->m_dFontSize = rectClient.height() * 0.4;
      fontxyz->m_eunitFontSize = ::ca::unit_pixel;
      fontxyz->m_bUpdated = false;

      SetFont(fontxyz);



   }

   void combo_box::_001OnAfterChangeText()
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


   void combo_box::_001OnInitialUpdate(gen::signal_object * pobj)
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

} // namespace user



