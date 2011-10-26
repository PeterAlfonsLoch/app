#include "StdAfx.h"
#include <math.h>
#include "window_frame/FrameSchemaHardCoded002.h"
#include "window_frame/FrameSchemaHardCoded005.h"

namespace querydb
{

   HHOOK g_mousehookLL;
   frame * g_pframe;

   static UINT indicators[] =
   {
	   ID_SEPARATOR,           // status line indicator
	   ID_INDICATOR_CAPS,
	   ID_INDICATOR_NUM,
	   ID_INDICATOR_SCRL,
   };


   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      ::ca::message_window_simple_callback(papp)
   {
      m_iFrameData = 10;
      m_dataid = "ca2::querydb::frame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";

      m_etranslucency      = TranslucencyPresent;

   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
      
      SCAST_PTR(::user::win::message::create, pcreate, pobj);

      pobj->previous();

      if(pobj->m_bRet)
         return;

      if(!initialize_message_window("ca2::fontopus::message_wnd::querydb"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }

      LoadToolBar(0, "querydb/toolbar.xml", TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

      SetTimer(1000, 100, NULL);
      
   }

#ifdef _DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }


#endif //_DEBUG

   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      UINT nIDEvent = ptimer->m_nIDEvent;
      static float theta;
      if(nIDEvent == 1000)
      {
         KillTimer(1000);
      }
      else if(nIDEvent == 85421)
      {
//         post_hotspot();
      }
      else if(nIDEvent == 1001)
      {
         KillTimer(nIDEvent);
         ShowWindow(SW_HIDE);
      }
      else if(nIDEvent == 5000)
      {
  /*       if(IsWindowVisible() && m_bAutoHideOnOutClick)
         {
            point pt;
            Application.get_cursor_pos(&pt);
            HWND hwnd = ::WindowFromPoint(pt);
            if(_get_handle() != hwnd
               && !user::WndUtil::IsAscendant(_get_handle(), hwnd))
            {
               m_bHover = false;
               ShowWindow(SW_HIDE);
            }
         }*/
      }
   }

   void frame::_001OnClose(gen::signal_object * pobj)
   {
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
   }


   void frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame::_001OnClose);
   }


   bool frame::_001OnCommand(id id)
   {
      if(id == "app_exit")
      {
         simple_frame_window::OnClose();
         return true;
      }
      return simple_frame_window::_001OnCommand(id);
   }

   bool frame::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      if(pcmdui->m_id == "app_exit")
      {
         return true;
      }
      return simple_frame_window::_001OnUpdateCmdUi(pcmdui);
   }


   void frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
//         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
      else if(pbase->m_uiMessage == WM_COPYDATA)
      {
  /*       PCOPYDATASTRUCT  lpcopydata = (PCOPYDATASTRUCT) pbase->m_lparam;
         DWORD dwData = lpcopydata->dwData;
         if(dwData == 198477)  // simple text command
         {
            string str((const char *) lpcopydata->lpData, min(lpcopydata->cbData, 1024 * 64));
            if(gen::str::begins_eat(str, "winactionareaview::"))
            {
               if(gen::str::begins_eat(str, "show_calendar("))
               {
                  const char * pszXml = str;
                  m_pwinactionareaview->show_calendar(gen::str::consume_quoted_value(pszXml));
               }
            }
         }
         */
      }
   }


   window_frame::FrameSchema * frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded005 * pschema = new window_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_typeinfoControlBoxButton = ::ca::get_type_info < MetaButton > ();
      pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;
   }

   bool frame::calc_layered()
   {
      return true;
   }

   void frame::_000OnDraw(::ca::graphics * pdc)
   {
      if(!Application.savings().should_save(gen::resource_processing)
      && !Application.savings().should_save(gen::resource_display_bandwidth)
      && !Application.savings().should_save(gen::resource_memory))
      {
         simple_frame_window::_000OnDraw(pdc);
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }



} // namespace querydb
