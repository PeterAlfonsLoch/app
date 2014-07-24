#include "framework.h"

namespace bergedge
{

   view::view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::place_holder(papp),

      ::backview::user::interaction(papp),
      ::backview::Interface(papp),
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
      ::user::place_holder::install_message_handling(pinterface);
      ::backview::Interface::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact drawing

   void view::OnDraw(::draw2d::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact diagnostics

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
   // ::user::impact message handlers

   // vmpLightView.cpp : implementation of the ::user::impact class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact


   bool view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::user::impact::pre_create_window(cs);
   }
   void view::_001OnInitialUpdate(signal_details * pobj)
   {
      ::user::impact::_001OnInitialUpdate(pobj);



   }

   void view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
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

      if(::backview::Interface::IsEnabled())
      {

         rect rectClient;
         GetClientRect(rectClient);


         ::backview::Main & main = ::backview::Interface::GetMain();
//         ::backview::Graphics & graphics = main.GetGraphics();

         if(main.IsInitialized())
         {

            ::draw2d::region_sp rgn(allocer());
//            rect rectFinal(graphics.m_rectFinalPlacement);
/*            ClientToScreen(rect);
            rgn->create_rect(rect);
            pdc->SelectClipRgn(rgn);*/
            pdc->SelectClipRgn(NULL);
            ::backview::Interface::BackViewRender(pdc, rectClient);


         }
      }

   }

   void view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(888888, 1977, NULL);

      sp(::bergedge::frame) pframe = GetTypedParent < ::bergedge::frame > ();

      pframe->m_pview = this;
      pframe->m_pdocument = get_document();


      string strImageDir = session().dir().userdata("image");
      session().dir().rls(strImageDir, &m_straImagePath);

      for(int32_t i = 0; i < m_straImagePath.get_size();)
      {
         if(session().dir().is(m_straImagePath[i]))
         {
            m_straImagePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }

      ::backview::Interface::Enable(false);
      ::backview::Interface::GetMain().GetImageChange().m_dwBackgroundUpdateMillis = 1000 * 30;
      //::backview::Interface::GetMain().GetTransitionEffect().DisableEffect(::backview::TransitionEffectVisual);


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

      m_ppaneview = create_view(System.type_info < ::bergedge::pane_view > (), get_document(), this, 102);

      hold(m_ppaneview);

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

   sp(::user::document) view::get_document()
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
            //::backview::Interface::ImageChangePostEvent(::backview::event_timer);
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

   bool view::UpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UNREFERENCED_PARAMETER(uiRedraw);
      m_rectaUpdate.add(recta);
      uint32_t dwNow = get_tick_count();
      if(m_rectaUpdate.get_size() <= 0)
      {
         m_dwLastUpdate = dwNow;
         return 0;
      }
      uint32_t dwElapseOptimization = 83;
      if(dwNow - m_dwLastUpdate < dwElapseOptimization)
      {
   //      TRACE("Great Optimization!\n");
         return 0;
      }
      m_dwLastUpdate = dwNow;
      _001RedrawWindow();
      m_rectaUpdate.remove_all();
      return 0;
   }


   void view::BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw)
   {
      rect rect(lpcrect);
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, uiRedraw);
   }

   void view::BackViewUpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UpdateScreen(recta, uiRedraw);
   }


   void view::BackViewUpdateScreen()
   {
      rect rect;
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, 0);
   }

   void view::BackViewGetData(::backview::InterfaceData & data)
   {

      ::backview::user::interaction::BackViewGetData(data);

   }

   void view::BackViewSetData(::backview::InterfaceData & data)
   {

      ::backview::user::interaction::BackViewSetData(data);

   }

   bool view::BackViewGetDestroy()
   {
      return m_bDestroy;
   }


   string view::GetNextBackgroundImagePath()
   {
      index i = m_straImagePath.find_first(m_strCurrentImagePath);
      i++;
      if(i >= m_straImagePath.get_size())
      {
         i = 0;
      }
      if(i < m_straImagePath.get_size())
      {
         return m_straImagePath[i];
      }
      return "";
   }

   void view::SetCurrentBackgroundImagePath(string &str)
   {
      m_strCurrentImagePath = str;
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
#if !defined(METROWIN) && !defined(LINUX) && !defined(APPLEOS)
      if(::IsWindow(m_oswindowWinactionarea) &&
         ::IsWindow(m_oswindowCommand) &&
         ::IsWindow(m_oswindowWinutil) &&
         ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::bergedge");
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
         sp(::user::interaction) pui = get_top_child();
         if(pui != NULL)
         {
            pui->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
         }
      }
      ::user::scroll_view::layout();
      ::backview::user::interaction::layout();
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
      sp(::user::interaction) pui = get_top_child();
      try
      {
         while(pui != NULL)
         {
            sp(::application) papp = NULL;
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

}  // namespace bergedge
