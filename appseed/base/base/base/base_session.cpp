//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


namespace base
{


   session::session(::aura::application * papp):
      object(papp),
      ::thread(papp),
      ::aura::session(papp),
      axis::session(papp)
   {

      m_pbasesession                = this;

      m_bMatterFromHttpCache        = m_pbasesystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor   = m_pbasesystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen   = m_pbasesystem->m_bSystemSynchronizedScreen;

      m_iMainMonitor                = -1;

      m_puiCapture                  = NULL;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance                = m_pauraapp->m_hinstance;

      }

#endif

      m_bDrawCursor                 = false;


      m_bDrawCursor                 = false;

      m_ecursorDefault              = ::visual::cursor_arrow;

      m_ecursor                     = ::visual::cursor_default;

      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;


      m_ecursorDefault              = ::visual::cursor_arrow;

      m_ecursor                     = ::visual::cursor_default;

      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;

      m_psavings                    = canew(class ::aura::savings(this));

      m_bZipIsDir                   = true;

      m_pmapKeyPressed              = NULL;

      m_puserstrcontext             = NULL;

      //m_paxissystem->m_basesessionptra.add_unique(this);

      m_pschemasimple               = NULL;

      m_puserschema                 = m_pschemasimple;

      m_pcopydesk                   = NULL;

      m_pschemasimple               = NULL;

      m_puserschema                 = m_pschemasimple;

   }


   //void session::construct(::aura::application * papp, int iPhase)
   //{

   //   ::axis::session::construct(papp,iPhase);
   //}

   session::~session_parent
   {


   }


   bool session::process_initialize()
   {

      thisstart;

      m_pschemasimple               = get_new_user_schema(NULL);

      if (m_pschemasimple == NULL)
      {

         thisfail << 1;

         return false;

      }

      m_puserschema                 = m_pschemasimple;

      if (!::axis::session::process_initialize())
      {

         thisfail << 2;

         return false;

      }

      if (!::base::application::process_initialize())
      {

         thisfail << 3;

         return false;

      }

      m_puser = create_user();

      if (m_puser == NULL)
      {

         thisfail << 4;

         return false;

      }

      m_puser->construct(this);


      return true;

   }


   bool session::initialize1()
   {


      if(!::axis::session::initialize1())
         return false;

      if(!::base::application::initialize1())
         return false;


      if(!m_puser->initialize1())
         return false;

      if(!m_puser->initialize2())
         return false;


      return true;

   }


   bool session::initialize()
   {

      if(!::axis::session::initialize())
         return false;

      if(!::base::application::initialize())
         return false;

      if(!m_puser->initialize())
         return false;


      ::set_simple_message_box(&::simple_ui_message_box);

      return true;

   }



   

   index session::get_ui_wkspace(::user::interaction * pui)
   {

      if(m_bSystemSynchronizedScreen)
      {

         return System.get_ui_wkspace(pui);

      }
      else
      {

         ::rect rect;

         pui->GetWindowRect(rect);

         return get_best_wkspace(NULL,rect);

      }


   }


   index session::initial_frame_position(LPRECT lprect,const RECT & rectParam,bool bMove,::user::interaction * pui)
   {

      rect rectRestore(rectParam);

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor,rectParam);

      ::size sizeMin;

      if(pui != NULL)
      {

         pui->get_window_minimum_size(sizeMin);

      }
      else
      {

         get_window_minimum_size(&sizeMin);

      }

      rect rectIntersect;

      if(bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor,rectaIntersect,rectParam);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor,&rectParam);

      }

      if(rectIntersect.width() < sizeMin.cx
         || rectIntersect.height() < sizeMin.cy)
      {

         if(rectMonitor.width() / 7 + MAX(sizeMin.cx,rectMonitor.width() * 2 / 5) > rectMonitor.width()
            || rectMonitor.height() / 7 + MAX(sizeMin.cy,rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + MAX(sizeMin.cx,rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + MAX(sizeMin.cy,rectMonitor.height() * 2 / 5);

            if(rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
            {

               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right,0);

            }

            if(rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
            {

               rectRestore.offset(0,rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

            }

         }

         *lprect = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         if(!bMove)
         {

            *lprect = rectIntersect;

         }

         return -1;

      }

   }

   index session::get_good_restore(LPRECT lprect,const RECT & rectParam,::user::interaction * pui)
   {

      return initial_frame_position(lprect,rectParam,false,pui);

   }


   index session::get_good_move(LPRECT lprect,const RECT & rectParam,::user::interaction * pui)
   {

      index iMatchingMonitor = initial_frame_position(lprect,rectParam,true,pui);

      if(memcmp(lprect,&rectParam,sizeof(RECT)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }


   }





   ::user::primitive * session::GetFocus()
   {

#ifdef METROWIN

      return System.ui_from_handle(::WinGetFocus());

#else

      return System.ui_from_handle(::GetFocus());

#endif

   }


   ::user::primitive * session::GetActiveWindow()
   {

#ifdef METROWIN

      return System.ui_from_handle(::WinGetActiveWindow());

#else

      return System.ui_from_handle(::GetActiveWindow());

#endif

   }


   void session::frame_pre_translate_message(signal_details * pobj)
   {

      try
      {

         sp(::user::interaction) pui;

         while(get_frame(pui))
         {

            try
            {

               if(pui != NULL)
               {

                  pui->pre_translate_message(pobj);

                  if(pobj->m_bRet)
                     return;

               }

            }
            catch(exit_exception & e)
            {

               throw e;

            }
            catch(...)
            {
            }

         }

      }
      catch(exit_exception & e)
      {

         throw e;

      }
      catch(...)
      {

         pobj->m_bRet = true;

      }

   }




   string session::get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::axis::session::get_cred(papp,strRequestUrlParam,rect,strUsername,strPassword,strToken,strTitle,bInteractive);

      if(str == "ok")
         return "ok";

      if(!bInteractive)
         return "failed";

      sp(::fontopus::simple_ui) pui;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string_dup(::dir::system() / "config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

      }

      pui = canew(::fontopus::simple_ui(papp,strRequestUrl));

      pui->m_login.m_peditUser->SetWindowText(strUsername);

      pui->m_login.m_ppassword->SetWindowText("");

      string strResult = pui->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pui->DestroyWindow();

      return strResult;

   }



   bool session::ReleaseCapture()
   {

#ifdef METROWIN
      oswindow oswindowCapture = ::WinGetCapture();
#else
      oswindow oswindowCapture = ::GetCapture();
#endif

      if (oswindowCapture == NULL)
         return false;

#ifdef METROWIN
      ::WinReleaseCapture();
#else
      ::ReleaseCapture();
#endif

      m_puiCapture = NULL;

      return true;


   }


   sp(::user::interaction) session::GetCapture()
   {

#ifdef METROWIN
      oswindow oswindowCapture = ::WinGetCapture();
#else
      oswindow oswindowCapture = ::GetCapture();
#endif

      if (oswindowCapture == NULL)
         return NULL;

      sp(::user::interaction) pui = System.ui_from_handle(oswindowCapture);

      if (pui == NULL)
         return NULL;

      return pui->GetCapture();

   }





   ::user::elemental * session::get_keyboard_focus()
   {

      if(m_pauraapp == NULL)
         return NULL;


      if(m_pkeyboardfocus == NULL)
         return NULL;

      //sp(::user::elemental) puieFocus;

      //try
      //{

      //   puieFocus = System.ui_.get_focus_ui();

      //}
      //catch(...)
      //{

      //}

      //if(puieFocus == NULL)
      //   return NULL;

      //sp(::user::interaction) puiFocus = m_pkeyboardfocus;

      //if(puiFocus.is_null())
      //   return NULL;

      //if(!puiFocus->is_descendant_of(puieFocus.cast < ::user::interaction >()))
      //   return NULL;


      //if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus)
      //   return NULL;
      return m_pkeyboardfocus;

   }


   sp(::user::schema) session::get_new_user_schema(const char * pszUinteractionLibrary)
   {

      thisstart;

      stringa stra;

      string strAppId;

      sp(::user::schema) pschema;

      string strId(pszUinteractionLibrary);

      string strLibrary;

      ::aura::library library(get_app(),0,NULL);

      if(strId.is_empty())
      {

         string strWndFrm = Application.file().as_string(::dir::system() / "config/system/wndfrm.txt");

         if(strWndFrm.is_empty())
            goto defer_check_wndfrm_core;

         strId = "wndfrm_" + strWndFrm;

      }

      strLibrary = strId;

      strLibrary.replace("-","_");

      strLibrary.replace("/","_");

restart:

      if (!library.open(strLibrary, false))
      {

         thisinfo << "Failed to load " << strLibrary;

         goto defer_check_wndfrm_core;

      }

      if(!library.open_ca2_library())
         goto defer_check_wndfrm_core;

      library.get_app_list(stra);

      if(stra.get_size() != 1) // a wndfrm OSLibrary should have one wndfrm
         goto defer_check_wndfrm_core;

      strAppId = stra[0];

      if(strAppId.is_empty()) // trivial validity check
         goto defer_check_wndfrm_core;

      pschema = library.create_object(get_app(),"user_schema", NULL);

      if(pschema == NULL)
         goto defer_check_wndfrm_core;

finish:

      //pschema->m_plibrary = plibrary;

      return pschema;

defer_check_wndfrm_core:

      if(strLibrary == "wndfrm_core")
      {

         pschema = canew(::user::schema_simple_impl(get_app()));

         goto finish;

      }

      strLibrary = "wndfrm_core";

      goto restart;

   }


   void session::on_finally_focus_set(::user::elemental * pelementalFocus)
   {

      if(pelementalFocus == NULL)
         return;

      sp(::user::interaction) puiFocus = pelementalFocus;

      if(puiFocus.is_set())
      {

         if(puiFocus->GetActiveWindow() != puiFocus->get_wnd())
         {

            puiFocus->get_wnd()->SetActiveWindow();

         }

         if(puiFocus->GetFocus() != puiFocus->get_wnd())
         {

            puiFocus->get_wnd()->SetFocus();

         }

      }


   }


   void session::get_cursor_pos(LPPOINT lppoint)
   {

      if (m_bSystemSynchronizedCursor)
      {

#ifdef METROWIN

         Windows::Foundation::Point p;

         p = System.m_possystemwindow->m_pwindow->get_cursor_pos();

         m_ptCursor.x = (LONG)p.X;

         m_ptCursor.y = (LONG)p.Y;

#else

         ::GetCursorPos(&m_ptCursor);

#endif

      }

      ::axis::session::get_cursor_pos(lppoint);

   }


   oswindow session::get_capture()
   {

#ifdef METROWIN

      return ::WinGetCapture();

#else

      return ::GetCapture();

#endif

   }


} // namespace base
































