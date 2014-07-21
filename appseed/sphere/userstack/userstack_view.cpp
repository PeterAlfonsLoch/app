#include "framework.h"


namespace userstack
{


   view::view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_winactionarea(papp),
      m_font(allocer()),
      m_dibBk(papp),
      m_mutexDraw(papp)
   {
      m_font->create_point_font("Geneva", 8.4);
      m_bDestroy = false;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
      m_ppaneview = NULL;
   }

   view::~view()
   {
   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::impact::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::draw2d::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   #ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


   bool view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::user::impact::pre_create_window(cs);
   }
   void view::_001OnInitialUpdate(signal_details * pobj)
   {
      ::user::impact::_001OnInitialUpdate(pobj);



   }

   void view::on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }

   void view::_001OnDestroy(signal_details * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);

   }



   void view::_001OnPaint(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);


   }


   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {


   }

   void view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(888888, 1977, NULL);

      sp(frame) pframe = GetTypedParent < frame > ();

      pframe->m_pview = this;
      pframe->m_pdocument = get_document();


      string strImageDir = Session.dir().userdata("image");
      Session.dir().rls(strImageDir, &m_straImagePath);

      for(int32_t i = 0; i < m_straImagePath.get_size();)
      {
         if(Session.dir().is(m_straImagePath[i]))
         {
            m_straImagePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }



      SetTimer(TimerBackView, 83, NULL);  // max. 12 fps
      SetTimer(21977, 1984 * 11, NULL);  // max. 12 fps

      check_apps();

      m_dibBk.load_from_matter("casweden1.png");


      m_dibV.load_from_matter("wild_mountains_and_valleys-123.png");
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");
      m_dib_winactionarea.load_from_matter("winactionarea.png");

      if(!PlaneSession.m_bShowPlatform)
      {
         return;
      }

      m_ppaneview = (create_view(System.type_info < pane_view > (), get_document(), this, 102));


   }

   void view::_001OnContextMenu(signal_details * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
//      point point = pcontextmenu->GetPoint();

   }

   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(signal_details * pobj)
   {
      
      SCAST_PTR(::message::mouse, pmouse, pobj);
   
      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }

   void view::pre_translate_message(signal_details * pobj)
   {
      ::user::impact::pre_translate_message(pobj);
   }

   sp(::user::object) view::get_document()
   {
      return  (::user::scroll_view::get_document());
   }

   void view::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
      switch(ptimer->m_nIDEvent)
      {
      case TimerBackView:
         {
            //gcom::backview::Interface::ImageChangePostEvent(gcom::backview::event_timer);
         }
         break;
      }

      if(ptimer->m_nIDEvent == 21977)
      {
         check_apps();
      }
      else if(ptimer->m_nIDEvent == 888888)
      {
         PlaneSession.check_topic_file_change();
      }

   }


   void view::GetAreaThumbRect(LPRECT lprect, int32_t iArea)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(iArea == m_iV)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_i_veriwell)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_veriwell_h;
         lprect->left = 1 + m_iVW + 5;
         lprect->right = lprect->left + m_i_veriwell_w;
      }
      else if(iArea == m_i_winactionarea)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_winactionarea_h;
         lprect->left = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right = lprect->left + m_i_winactionarea_w;
      }
   }


   void view::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
   }

   void view::check_apps()
   {
   //   if(::IsDebuggerPresent())
     //    return;
      //if(!m_bEnsureApps)
        // return;
#ifdef WINDOWSEX
      if(::IsWindow(m_oswindowWinactionarea) &&
         ::IsWindow(m_oswindowCommand) &&
         ::IsWindow(m_oswindowWinutil) &&
         ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindow(NULL, "::ca2::fontopus::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindow(NULL, "::ca2::fontopus::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindow(NULL, "::ca2::fontopus::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindow(NULL, "::ca2::fontopus::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindow(NULL, "::ca2::fontopus::message_wnd::bergedge");
#else
      throw todo(get_app());
#endif
   }


   index view::hit_test(point pt, e_element & eelement)
   {
      rect rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_iV;
      }
      GetAreaThumbRect(rectArea, m_i_veriwell);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_veriwell;
      }
      GetAreaThumbRect(rectArea, m_i_winactionarea);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_winactionarea;
      }
      eelement = element_none;
      return -1;
   }


   UINT c_cdecl view::ThreadProcShowWindow(LPVOID lpparam)
   {
      UNREFERENCED_PARAMETER(lpparam);
      return 0;
   }


   void view::mt_show_window(oswindow oswindow, int32_t iShow)
   {
      UNREFERENCED_PARAMETER(oswindow);
      UNREFERENCED_PARAMETER(iShow);
   }

   /*void view::layout()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_ppaneview != NULL)
      {
         m_ppaneview->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pui = get_top_child();
         if(pui != NULL)
         {
            pui->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
         }
      }
      ::user::scroll_view::layout();
      gcom::backview::user::interaction::layout();
   }*/

   void view::_000OnMouse(::message::mouse * pmouse)
   {
      try
      {
         if(!_001IsPointInside(pmouse->m_pt))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pui = get_top_child();
      try
      {
         while(pui != NULL)
         {
            sp(::asphere::application) papp = NULL;
            try
            {
               papp = &App(pui->get_app());
            }
            catch(...)
            {
               papp = NULL;
            }

            try
            {

               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }


}  // namespace userstack



