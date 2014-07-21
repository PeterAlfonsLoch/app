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


   void combo_list::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::control::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_KILLFOCUS, pdispatch, this, &combo_list::_001OnKillFocus);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pdispatch, this, &combo_list::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_ACTIVATE, pdispatch, this, &combo_list::_001OnActivate);
      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE, pdispatch, this, &combo_list::_001OnMouseActivate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &combo_list::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &combo_list::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MBUTTONDOWN, pdispatch, this, &combo_list::_001OnMButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN, pdispatch, this, &combo_list::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &combo_list::_001OnMouseMove);

   }


   void combo_list::_001OnDraw(::draw2d::graphics * pdc)
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

   void combo_list::_001OnDrawVerisimple(::draw2d::graphics * pdc)
   {

      ::count ca = m_pcombo->_001GetListCount();

      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(230, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      {

         color ca;

         ca.set_rgb(RGB(227, 227, 210));

         ca.hls_rate(0.0, -0.33, -0.23);

         COLORREF crBorder = ca.get_rgb() | (0xff << 24);

         pdc->Draw3dRect(rectClient, crBorder, crBorder);

      }

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top + _001GetItemHeight();

      point ptCursor;

      session().get_cursor_pos(&ptCursor);

      ScreenToClient(&ptCursor);

      br->create_solid(ARGB(255, 84, 84, 77));

//      int32_t dSize = (int32_t) ( _001GetItemHeight() * 0.7);

  //    GetFont()->m_dFontSize = dSize;
    //  GetFont()->m_eunitFontSize = ::draw2d::unit_pixel;
//      GetFont()->m_bUpdated = false;

      pdc->selectFont(GetFont());

      pdc->SelectObject(br);

      for(index i = 0; i < ca; i++)
      {
         rectItem.top = rectItem.bottom;
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(i != m_pcombo->m_iSel)
         {
            if(rectItem.contains(ptCursor))
            {
               ::draw2d::pen_sp pen(allocer());
               pen->create_solid(m_iItemHeight / 8, ARGB(230, 77, 184, 63));
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


   void combo_list::_001OnDrawSimply(::draw2d::graphics * pdc)
   {

      ::count ca = m_pcombo->_001GetListCount();

      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(230, 255, 255, 255));

      pdc->SelectObject(br);

      pdc->FillRectangle(rectClient);

      {

         color ca;

         ca.set_rgb(RGB(227, 227, 210));

         ca.hls_rate(0.0, -0.33, -0.23);

         COLORREF crBorder = ca.get_rgb() | (0xff << 24);

         pdc->Draw3dRect(rectClient, crBorder, crBorder);

      }

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top + _001GetItemHeight();

      point ptCursor;

      session().get_cursor_pos(&ptCursor);

      ScreenToClient(&ptCursor);

      br->create_solid(ARGB(255, 84, 84, 77));

      //int32_t dSize = (int32_t) (_001GetItemHeight() * 0.7);

      //GetFont()->m_dFontSize = dSize;
      //GetFont()->m_eunitFontSize = ::draw2d::unit_pixel;
      //GetFont()->m_bUpdated = false;

      pdc->selectFont(GetFont());

      pdc->SelectObject(br);

      for(index i = 0; i < ca; i++)
      {
         rectItem.top = rectItem.bottom;
         rectItem.bottom = rectItem.top + _001GetItemHeight();
         if(i != m_pcombo->m_iSel)
         {
            if(rectItem.contains(ptCursor))
            {
               ::draw2d::pen_sp pen(allocer());
               pen->create_solid(m_iItemHeight / 8, ARGB(230, 77, 184, 63));
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

      if (!((combo_list *)this)->IsWindow())
         return;

      ::draw2d::graphics_sp pdc(((combo_list *) this)->allocer());


      pdc->CreateCompatibleDC(NULL);

      ::draw2d::dib_sp tameshi(((combo_list *) this)->allocer());

      tameshi->create(100, 100);

      pdc->SelectObject(tameshi->get_bitmap());

    //  int32_t dSize = (int32_t) (_001GetItemHeight() * 0.7);
////
//      ((combo_list *) this)->GetFont()->m_dFontSize = dSize;
//
//      ((combo_list *) this)->GetFont()->m_eunitFontSize = ::draw2d::unit_pixel;
//
//      ((combo_list *) this)->GetFont()->m_bUpdated = false;
//
      pdc->selectFont(((combo_list *) this)->GetFont());

      string strItem;

      size sz;

      lpsize->cx = 0;

      ::count ca = m_pcombo->_001GetListCount();

      for(index i = 0; i < ca; i++)
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




   bool combo_list::pre_create_window(CREATESTRUCT & cs)
   {

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

   void combo_list::_001OnKillFocus(signal_details * pobj)
   {



   }

   void combo_list::_001OnActivate(signal_details * pobj)
   {

      SCAST_PTR(::message::activate, pactivate, pobj);

      sp(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther.m_p : this);

      if(pactivate->m_nState == WA_INACTIVE)
      {

         point ptCursor;

         session().get_cursor_pos(&ptCursor);

         m_pcombo->ScreenToClient(&ptCursor);

         if(m_pcombo->hit_test(ptCursor) != element_drop_down)
         {

            m_pcombo->_001ShowDropDown(false);

         }


         sp(::user::interaction) pframe = oprop("deactivate_together").cast < ::user::interaction >();

         if(pActive != pframe)
         {

            ::user::uinteraction::frame::WorkSet * pset = oprop("deactivate_together_set").cast < ::user::uinteraction::frame::WorkSet > ();

            if(pset != NULL)
            {

               pset->SetActiveFlag(FALSE);

            }

         }



      }

         //m_pcombo->_001ShowDropDown(false);

      //}

   }

   void combo_list::_001OnMouseActivate(signal_details * pobj)
   {

//      SCAST_PTR(::message::mouse_activate, pactivate, pobj);


   }

   void combo_list::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_bRet = true;

   }

   void combo_list::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

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

            m_pcombo->_001SetCurSel(iItem, ::action::source_user);

         }

      }

      m_pcombo->_001ShowDropDown(false);

      pobj->m_bRet = true;

   }

   void combo_list::_001OnMButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

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

   void combo_list::_001OnRButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

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


   void combo_list::_001OnMouseMove(signal_details * pobj)
   {

//      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;


   }


   void combo_list::_001OnClose(signal_details * pobj)
   {

      post_message(WM_DESTROY);

   }
   

   index combo_list::hit_test(point pt, e_element & eelement)
   {

      ::count ca = m_pcombo->_001GetListCount();

      rect rectClient;

      GetClientRect(rectClient);

      rect rectItem;

      rectItem = rectClient;

      for(int32_t i = 0; i < ca; i++)
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




