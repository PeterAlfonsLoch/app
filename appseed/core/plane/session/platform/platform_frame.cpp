#include "framework.h"


namespace platform
{


   frame::frame(sp(base_application) papp) :
      element(papp),
      simple_frame_window(papp),
      form_frame(papp)
   {
      m_pimagelist         = NULL;
      m_iFrameData         = 10;
      m_dataid             = "core::platform::frame";

      m_bWindowFrame       = true;
      m_bFrameMoveEnable   = false;
      m_bHover             = false;
      m_bMouseLeaveTimer   = false;
      m_bOnDraw            = false;
      m_dwLastSuperDock    = 0;
      m_bHideTimer         = false;


      m_bAutoWindowFrame   = false;
      m_bWindowFrame       = true;

      oprop("should_not_be_automatically_holded_on_initial_update_frame") = true;

      WfiEnableFullScreen();
   }

   frame::~frame()
   {
   }


   bool frame::pre_create_window(CREATESTRUCT& cs)
   {

      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;

      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

   }


#ifdef DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


#endif //DEBUG

   void frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &frame::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &frame::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &frame::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame::_001OnClose);
   }


   void frame::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj);
      UINT nIDEvent = ptimer->m_nIDEvent;

      static float theta;
      if(nIDEvent == 4321875)
      {
         KillTimer(nIDEvent);
         m_bMouseLeaveTimer = false;
         if(!m_bHover)
         {
            ShowWindow(SW_HIDE);
         }
      }
      else if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 1000)
      {
         WfiRestore();
         KillTimer(nIDEvent);
         m_bTimerOn = false;
      }
      else if(nIDEvent == 8913)
      {
      }
      else if(nIDEvent == 1001)
      {
         m_bHideTimer = false;
         ShowWindow(SW_HIDE);
         KillTimer(1001);
      }
      else if(nIDEvent == 4033)
      {
         point pt;
         if(m_bHoverMouse && get_tick_count() > m_dwLastHover + 300)
         {
            OnHoverAction();
         }
         Session.get_cursor_pos(&pt);
         if(!m_bHoverMouse && pt.x <= 0)
         {
            m_dwLastHover = ::get_tick_count();
            m_bHoverMouse = true;

         }
         else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
         {
            m_bHoverMouse = false;
         }
         if(IsWindowVisible())
         {
            rect rectWindow;
            GetWindowRect(rectWindow);
            if(rectWindow.contains(pt))
            {
               m_bHideTimer = false;
               KillTimer(1001);
            }
            else if(!m_bHideTimer && (::get_tick_count() - m_dwLastSuperDock) > 984)
            {
               m_bHideTimer = true;
               SetTimer(1001, 500, NULL);
            }
         }
         // OpenGL animation code goes here

         //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
         //glClear( GL_COLOR_BUFFER_BIT );

         /*glPushMatrix();
         glRotatef( theta, 0.0f, 1.0f, 1.0f );
         glBegin( GL_TRIANGLES );
         glColor3f( 1.0f, 0.0f, 0.0f ); glVertgenf( 0.0f, 1.0f );
         glColor3f( 0.0f, 1.0f, 0.0f ); glVertgenf( 0.87f, -0.5f );
         glColor3f( 0.0f, 0.0f, 1.0f ); glVertgenf( -0.87f, -0.5f );
         glEnd();
         glPopMatrix();*/

         //SwapBuffers( m_hdcOpenGL );

         theta += 2.0f;

      }
      //simple_frame_window::OnTimer(nIDEvent);
   }



   void frame::ShowControlBars(bool bShow)
   {
      UINT nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

      /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
      //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/

   }



   void frame::OnHoverAction()
   {
      WfiRestore();
   }

   void frame::_001OnSize(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void frame::_001OnMouseMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(!m_bHover)
      {
         m_bHover = true;
         track_mouse_hover();
      }
      if(m_bMouseLeaveTimer)
      {
         m_bMouseLeaveTimer = false;
         KillTimer(4321875);
      }
   }

   void frame::_001OnMouseLeave(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_bMouseLeaveTimer = true;
      m_bHover = false;
      SetTimer(4321875, 884, NULL);
   }

   void frame::_001OnCreate(signal_details * pobj)
   {
      //      SCAST_PTR(::message::create, pcreate, pobj);
      pobj->previous();

      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);



      m_pimagelist = new image_list(get_app());

      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_icon.ico");


      if(!data_get("DockPosition", (int32_t &) m_eposition))
      {
         m_eposition = position_left;
      }
      ShowWindow(SW_HIDE);
      //super_dock_on_bergedge();
   }

   void frame::super_dock_on_bergedge()
   {
      if(!Session.m_bShowPlatform)
      {
         return;
      }
      m_dwLastSuperDock = ::get_tick_count();
      rect rectDesktop;

      sp(::user::interaction) puiParent = GetTypedParent < ::bergedge::view >();
      if(puiParent == NULL)
         puiParent = GetTypedParent < ::user::place_holder > ();
      if(puiParent == NULL)
         puiParent = get_parent();
      if(puiParent == NULL)
      {
         // There is no place to dock on to.
         return;
      }
      puiParent->GetWindowRect(rectDesktop);
      WfiRestore();
      switch(m_eposition)
      {
      case position_left:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, 400, rectDesktop.height(), SWP_SHOWWINDOW);
         break;
      case position_top:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
      case position_bottom:
         SetWindowPos(ZORDER_TOPMOST, 0, rectDesktop.height() - 400, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
      case position_right:
         SetWindowPos(ZORDER_TOPMOST, rectDesktop.width() - 400, 0, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
         default:
            break;
      }
   }


   sp(::user::uinteraction::frame::frame) frame::create_frame_schema()
   {

      sp(::user::uinteraction::frame::frame) pframe = Application.uinteraction().get_frame_schema("app-core/uinteraction", "005");

      pframe->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      pframe->set_style("StyleTranslucidWarmGray");

      return pframe;

   }


   void frame::_000OnDraw(::draw2d::graphics * pgraphics)
   {
      if(m_bOnDraw)
         return;
      form_frame::_000OnDraw(pgraphics);
   }

   void frame::_001OnClose(signal_details * pobj)
   {
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
   }


} // namespace platform


