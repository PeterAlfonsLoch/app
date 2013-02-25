#include "framework.h"


namespace user
{


   combo_list::combo_list()
   {
      
      oprop("combo_list") = true;

      m_pcombo = NULL;

   }

   combo_list::~combo_list()
   {
   }


   void combo_list::install_message_handling(::ca::message::dispatch * pdispatch)
   {

      ::user::control::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_KILLFOCUS, pdispatch, this, &combo_list::_001OnKillFocus);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pdispatch, this, &combo_list::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_ACTIVATE, pdispatch, this, &combo_list::_001OnActivate);
      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE, pdispatch, this, &combo_list::_001OnMouseActivate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &combo_list::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_MBUTTONDOWN, pdispatch, this, &combo_list::_001OnMButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN, pdispatch, this, &combo_list::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &combo_list::_001OnMouseMove);

   }


   void combo_list::_001OnDraw(::ca::graphics * pdc)
   {
      
      if(m_pcombo == NULL)
         return;

      if(m_pcombo->m_estyle == ::user::combo_box::style_simply)
      {

         _001OnDrawSimply(pdc);

      }
      else
      {

         _001OnDrawVerisimple(pdc);

      }

   }

   void combo_list::_001OnDrawVerisimple(::ca::graphics * pdc)
   {

      count c = m_pcombo->_001GetListCount();
      
      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::ca::brush_sp br(get_app());

      br->create_solid(ARGB(230, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top + _001GetItemHeight();

      point ptCursor;

      Session.get_cursor_pos(&ptCursor);

      ScreenToClient(&ptCursor);

      br->create_solid(ARGB(255, 84, 84, 77));

      int32_t dSize = (int32_t) ( _001GetItemHeight() * 0.7);

      pdc->m_fontxyz.m_dFontSize = dSize;
      pdc->m_fontxyz.m_eunitFontSize = ::ca::unit_pixel;
      pdc->m_fontxyz.m_bUpdated = false;

      pdc->SelectObject(br);

      for(index i = 0; i < c; i++)
      {
         rectItem.top = rectItem.bottom;
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(i != m_pcombo->m_iSel)
         {
            if(rectItem.contains(ptCursor))
            {
               ::ca::pen_sp pen(get_app());
               pen->create_solid(pdc, m_iItemHeight / 8, ARGB(230, 77, 184, 63));
               pdc->SelectObject(pen);
               pdc->DrawRectangle(rectItem);
            }
            m_pcombo->_001GetListText(i, strItem);
            pdc->draw_text(strItem, rectItem, 0);
         }
      }

      if(m_pcombo->m_iSel >= 0)
      {
         rectItem.top = (LONG) (rectClient.top + (_001GetItemHeight() * (1 + m_pcombo->m_iSel)));
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(rectItem.contains(ptCursor))
         {
            br->create_solid(ARGB(123, 123, 149, 108));
         }
         else
         {
            br->create_solid(ARGB(184, 77, 184, 63));
         }
         pdc->SelectObject(br);
         pdc->FillRectangle(rectItem);
         br->create_solid(ARGB(255, 255, 255, 240));
         m_pcombo->_001GetListText(m_pcombo->m_iSel, strItem);
         pdc->SelectObject(br);
         pdc->draw_text(strItem, rectItem, 0);
      }


   }


   void combo_list::_001OnDrawSimply(::ca::graphics * pdc)
   {

      count c = m_pcombo->_001GetListCount();
      
      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::ca::brush_sp br(get_app());

      br->create_solid(ARGB(230, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top + _001GetItemHeight();

      point ptCursor;

      Session.get_cursor_pos(&ptCursor);

      ScreenToClient(&ptCursor);

      br->create_solid(ARGB(255, 84, 84, 77));

      int32_t dSize = (int32_t) (_001GetItemHeight() * 0.7);

      pdc->m_fontxyz.m_dFontSize = dSize;
      pdc->m_fontxyz.m_eunitFontSize = ::ca::unit_pixel;
      pdc->m_fontxyz.m_bUpdated = false;

      pdc->SelectObject(br);

      for(index i = 0; i < c; i++)
      {
         rectItem.top = rectItem.bottom;
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(i != m_pcombo->m_iSel)
         {
            if(rectItem.contains(ptCursor))
            {
               ::ca::pen_sp pen(get_app());
               pen->create_solid(pdc, m_iItemHeight / 8, ARGB(230, 77, 184, 63));
               pdc->SelectObject(pen);
               pdc->DrawRectangle(rectItem);
            }
            m_pcombo->_001GetListText(i, strItem);
            pdc->draw_text(strItem, rectItem, 0);
         }
      }

      if(m_pcombo->m_iSel >= 0)
      {
         rectItem.top = (LONG) (rectClient.top + (_001GetItemHeight() * (1 + m_pcombo->m_iSel)));
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(rectItem.contains(ptCursor))
         {
            br->create_solid(ARGB(123, 123, 149, 108));
         }
         else
         {
            br->create_solid(ARGB(184, 77, 184, 63));
         }
         pdc->SelectObject(br);
         pdc->FillRectangle(rectItem);
         br->create_solid(ARGB(255, 255, 255, 240));
         m_pcombo->_001GetListText(m_pcombo->m_iSel, strItem);
         pdc->SelectObject(br);
         pdc->draw_text(strItem, rectItem, 0);
      }


   }

   void combo_list::query_full_size(LPSIZE lpsize) const
   {

      ::ca::graphics_sp pdc(get_app());


      pdc->CreateCompatibleDC(NULL);

      ::ca::dib_sp tameshi(get_app());

      tameshi->create(100, 100);

      pdc->SelectObject(tameshi->get_bitmap());
      
      int32_t dSize = (int32_t) (_001GetItemHeight() * 0.7);

      pdc->m_fontxyz.m_dFontSize = dSize;

      pdc->m_fontxyz.m_eunitFontSize = ::ca::unit_pixel;

      pdc->m_fontxyz.m_bUpdated = false;

      string strItem;

      size sz;

      lpsize->cx = 0;

      ::count c = m_pcombo->_001GetListCount();

      for(index i = 0; i < c; i++)
      {
         
         m_pcombo->_001GetListText(i, strItem);
         
         sz = pdc->GetTextExtent(strItem);

         if(sz.cx > lpsize->cx)
         {

            lpsize->cx = sz.cx;

         }

      }

      lpsize->cy = (LONG) (_001GetItemHeight() * (m_pcombo->_001GetListCount() + 1));

   }

   int32_t combo_list::_001GetItemHeight() const
   {
      
      return m_iItemHeight;

   }


   const char * combo_list::GetIconWndClass(uint32_t dwDefaultStyle, const char * pszMatter)
   {

   #ifdef WINDOWSEX

      HICON hIcon = (HICON) ::LoadImage(
         NULL,
         Application.dir().matter(pszMatter, "icon.ico"), IMAGE_ICON,
         16, 16,
         LR_LOADFROMFILE);

      //if(hIcon != NULL)
      {
         CREATESTRUCT cs;
         memset(&cs, 0, sizeof(CREATESTRUCT));
         cs.style = dwDefaultStyle;
         pre_create_window(cs);
            // will fill lpszClassName with default WNDCLASS name
            // ignore instance handle from pre_create_window.

         WNDCLASS wndcls;
         if (cs.lpszClass != NULL &&
            GetClassInfo(System.m_hInstance, cs.lpszClass, &wndcls) &&
            wndcls.hIcon != hIcon)
         {
            // register a very similar WNDCLASS
            return System.RegisterWndClass(wndcls.style,
               wndcls.hCursor, wndcls.hbrBackground, hIcon);
         }
      }
   #else

      throw not_implemented(get_app());

   #endif
      return NULL;        // just use the default
   }


   bool combo_list::pre_create_window(CREATESTRUCT & cs)
   {

      if (cs.lpszClass == NULL)
      {
         // COLOR_WINDOW background
   #ifdef WINDOWSEX
         VERIFY(System.DeferRegisterClass(__WNDFRAMEORVIEW_REG, &cs.lpszClass));
   #endif
      }

      if (cs.style & WS_BORDER)
      {
   #ifdef WINDOWSEX
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
   #endif
         cs.style &= ~WS_BORDER;
      }

      cs.dwExStyle |= WS_EX_LAYERED;
      cs.dwExStyle |= WS_EX_TOOLWINDOW;
      cs.dwExStyle |= WS_EX_TOPMOST;
      //cs.dwExStyle |= WS_EX_NOACTIVATE;

      return TRUE;
   }

   void combo_list::_001OnKillFocus(::ca::signal_object * pobj)
   {



   }

   void combo_list::_001OnActivate(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::activate, pactivate, pobj);

      ::user::interaction* pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if(pactivate->m_nState == WA_INACTIVE)
      {
      
         point ptCursor;
      
         Session.get_cursor_pos(&ptCursor);

         m_pcombo->ScreenToClient(&ptCursor);

         if(m_pcombo->hit_test(ptCursor) != element_drop_down)
         {

            m_pcombo->_001ShowDropDown(false);

         }


         ::user::interaction * pframe = oprop("deactivate_together").ca < ::user::interaction >();

         if(pActive != pframe)
         {

            ::uinteraction::frame::WorkSet * pset = oprop("deactivate_together_set").ca < ::uinteraction::frame::WorkSet > ();

            pset->SetActiveFlag(FALSE);

         }



      }

         //m_pcombo->_001ShowDropDown(false);

      //}

   }

   void combo_list::_001OnMouseActivate(::ca::signal_object * pobj)
   {

//      SCAST_PTR(::ca::message::mouse_activate, pactivate, pobj);


   }

   void combo_list::_001OnLButtonDown(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.contains(pt))
      {

         e_element eelement;

         index iItem = hit_test(pt, eelement);

         if(eelement == element_item)
         {
            
            m_pcombo->_001SetCurSel(iItem);

         }

      }

      m_pcombo->_001ShowDropDown(false);

      pobj->m_bRet = true;

   }

   void combo_list::_001OnMButtonDown(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.contains(pt))
      {

      }
      else
      {
         m_pcombo->_001ShowDropDown(false);
      }

      pobj->m_bRet = true;

   }

   void combo_list::_001OnRButtonDown(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.contains(pt))
      {

      }
      else
      {
         m_pcombo->_001ShowDropDown(false);
      }

      pobj->m_bRet = true;

   }


   void combo_list::_001OnMouseMove(::ca::signal_object * pobj)
   {

//      SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;


   }


   void combo_list::_001OnClose(::ca::signal_object * pobj)
   {
      
      PostMessage(WM_DESTROY, 0, 0);

   }

   index combo_list::hit_test(point pt, e_element & eelement)
   {

      count c = m_pcombo->_001GetListCount();

      rect rectClient;

      GetClientRect(rectClient);

      rect rectItem;

      rectItem = rectClient;

      for(int32_t i = 0; i < c; i++)
      {

         rectItem.top = rectClient.top + (_001GetItemHeight() * (1 + i));
         rectItem.bottom = rectItem.top + _001GetItemHeight();

         if(rectItem.contains(pt))
         {
            
            eelement = element_item;

            return i;

         }


      }

      rectItem.top = rectClient.top;
      rectItem.bottom = rectItem.top + _001GetItemHeight();

      if(rectItem.contains(pt))
      {
            
         eelement = element_search_edit;

         return 0;

      }

      eelement = element_none;

      return -1;

   }


} // namespace user




