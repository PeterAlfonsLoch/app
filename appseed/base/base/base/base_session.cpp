#include "framework.h"


#ifdef WINDOWSEX

HMONITOR GetPrimaryMonitorHandle()
{

   const POINT ptZero = { 0 , 0 };

   return MonitorFromPoint(ptZero,MONITOR_DEFAULTTOPRIMARY);

}

#endif

namespace base
{


   session::session(sp(::base::application) papp) :
      element(papp),
      ::thread(papp)
   {

      m_pbasesession = this;

      if(papp->is_system())
      {

         m_pfontopus = create_fontopus();

         if(m_pfontopus == NULL)
            throw simple_exception(this,"could not create fontopus for ::base::session (::base::session::construct)");

         m_pfontopus->construct(this);

      }
      else
      {

         m_pfontopus = m_pbaseapp->m_pbasesession->m_pfontopus;

      }

      m_bMatterFromHttpCache = m_pbasesystem->m_bMatterFromHttpCache;

      m_bSessionSynchronizedCursor = m_pbasesystem->m_bSessionSynchronizedCursor;
//      m_bSessionSynchronizedScreen = true;

      if(m_hinstance == NULL)

      {

         m_hinstance = m_pbaseapp->m_hinstance;

      }

      m_pifs                     = new ifs(this,"");
      m_prfs                     = new ::fs::remote_native(this,"");

      ::fs::set * pset = new class ::fs::set(this);
      ::fs::link * plink = new ::fs::link(this);
      plink->fill_os_user();
      pset->m_spafsdata.add(plink);
      pset->m_spafsdata.add(new ::fs::native(this));
      m_spfsdata = pset;

      m_bDrawCursor              = true;
      m_ecursorDefault  = ::visual::cursor_arrow;
      m_ecursor         = ::visual::cursor_default;



   }

   session::~session()
   {

      POSITION pos = m_mapApplication.get_start_position();

      string strId;

      sp(::base::application) pbaseapp;

      while(pos != NULL)
      {

         strId.Empty();

         pbaseapp = NULL;

         m_mapApplication.get_next_assoc(pos,strId,pbaseapp);

         sp(::base::application) papp = (pbaseapp);

         papp->post_thread_message(WM_QUIT);

      }

   }


   bool session::is_session()
   {

      return true;

   }


   sp(::base::application) session::start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext)
   {

      throw interface_only_exception(this);

      return NULL;

   }



   ::fontopus::user * session::safe_get_user()
   {

      if(m_pfontopus == NULL)
         return NULL;

      return m_pfontopus->m_puser;

   }


   void session::set_cursor(::visual::e_cursor ecursor)
   {

      m_ecursor = ecursor;

   }


   void session::set_default_cursor(::visual::e_cursor ecursor)
   {

      if(ecursor == ::visual::cursor_default)
      {

         m_ecursorDefault = ::visual::cursor_arrow;

      }
      else
      {

         m_ecursorDefault = ecursor;

      }

   }



   COLORREF session::get_default_color(uint64_t ui)
   {

      switch(ui)
      {
      case COLOR_3DFACE:
         return ARGB(127,192,192,184);
      case COLOR_WINDOW:
         return ARGB(127,255,255,255);
      case COLOR_3DLIGHT:
         return ARGB(127,218,218,210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127,238,238,230);
      case COLOR_3DSHADOW:
         return ARGB(127,138,138,130);
      case COLOR_3DDKSHADOW:
         return ARGB(127,84,84,77);
      default:
         break;
      }

      return ARGB(127,0,0,0);

   }





   ::base::copydesk & session::copydesk()
   {

      return *m_spcopydesk;

   }


   ::fontopus::user * session::get_user()
   {

      return m_pfontopus->get_user();

   }


   bool session::get_auth(const string & pszForm,string & strUsername,string & strPassword)
   {
      UNREFERENCED_PARAMETER(pszForm);
      UNREFERENCED_PARAMETER(strUsername);
      UNREFERENCED_PARAMETER(strPassword);
      return false;
   }


   /*::fontopus::user * application::create_user(const string & pszLogin)
   {
   return NULL;
   }*/

   ::fontopus::user * session::create_current_user()
   {
      return NULL;
      /*   string str = get_current_user_login();
      return create_user(str);*/
   }

   /*string application::get_current_user_login()
   {
   return "";
   }*/



   bool session::is_licensed(const char * pszId,bool bInteractive)
   {

      if(directrix()->m_varTopicQuery.has_property("install"))
         return true;

      if(directrix()->m_varTopicQuery.has_property("uninstall"))
         return true;

      return license().has(pszId,bInteractive);

   }


   ::fontopus::fontopus * session::create_fontopus()
   {

      return canew(::fontopus::fontopus(this));

   }


   index session::get_main_monitor(LPRECT lprect)
   {

      int iMainMonitor = 0;

#ifdef WINDOWSEX

      HMONITOR hmonitorPrimary = GetPrimaryMonitorHandle();

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if(m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }


#endif

      if(lprect != NULL)
      {

         get_monitor_rect(iMainMonitor,lprect);

      }

      return iMainMonitor;

   }



   ::count session::get_monitor_count()
   {

#ifdef WINDOWSEX

      return m_monitorinfoa.get_count();

#else

      return 1;

#endif

   }


   bool session::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

#ifdef WINDOWSEX

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
         return false;

      *lprect = m_monitorinfoa[iMonitor].rcMonitor;

#elif defined(METROWIN)

      return System.GetWindowRect(lprect);

#elif defined(LINUX)

      xdisplay  d;

      if(!d.open(NULL))
         return false;

      lprect->left = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));
      lprect->top = 0;
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));

#elif defined(APPLEOS)

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
         return false;

      GetMainScreenRect(lprect);

#else

      throw todo(get_app());

      ::GetWindowRect(::GetDesktopWindow(),lprect);

#endif

      return true;

   }


   ::count session::get_desk_monitor_count()
   {

      return get_monitor_count();

   }



   bool session::get_desk_monitor_rect(index iMonitor,LPRECT lprect)
   {

      return get_monitor_rect(iMonitor,lprect);

   }


   index session::initial_frame_position(LPRECT lprect,LPCRECT lpcrect, bool bMove)
   {

      rect rectRestore(lpcrect);

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor,lpcrect);

      ::size sizeMin;

      get_window_minimum_size(&sizeMin);

      rect rectIntersect;

      if(bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor,rectaIntersect,lpcrect);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor,lpcrect);

      }

      if(rectIntersect.width() < sizeMin.cx
         || rectIntersect.height() < sizeMin.cy)
      {

         if(rectMonitor.width() / 7 + max(sizeMin.cx,rectMonitor.width() * 2 / 5) > rectMonitor.width()
            || rectMonitor.height() / 7 + max(sizeMin.cy,rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + max(sizeMin.cx,rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + max(sizeMin.cy,rectMonitor.height() * 2 / 5);

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

   void session::get_monitor(rect_array & rectaMonitor,rect_array & rectaIntersect,LPCRECT lpcrect)
   {

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_monitor_rect(iMonitor,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(lpcrect,rectMonitor))
            {

               if(rectIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectMonitor);

                  rectaIntersect.add(rectIntersect);

               }

            }

         }

      }

   }


   index session::get_best_monitor(LPRECT lprect,LPCRECT lpcrect)
   {

      index iMatchingMonitor = -1;
      index iBestArea = -1;
      rect rectMatch;

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_monitor_rect(iMonitor,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(lpcrect,rectMonitor))
            {

               if(rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }

         }

      }

      if(iMatchingMonitor >= 0)
      {

         *lprect = rectMatch;

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(lprect);

      return iMatchingMonitor;

   }



   index session::get_good_restore(LPRECT lprect,LPCRECT lpcrect)
   {

      return initial_frame_position(lprect,lpcrect, false);

   }


   index session::get_good_iconify(LPRECT lprect,LPCRECT lpcrect)
   {

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor,lpcrect);

      lprect->left = rectMonitor.left;
      lprect->top = rectMonitor.top;
      lprect->right = rectMonitor.left;
      lprect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   index session::get_good_move(LPRECT lprect,LPCRECT lpcrect)
   {

      index iMatchingMonitor = initial_frame_position(lprect,lpcrect, true);

      if(memcmp(lprect,lpcrect,sizeof(RECT)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }


   }


   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }


   bool session::initialize_instance()
   {

      if(m_pfontopus->m_puser == NULL &&
         (Application.directrix()->m_varTopicQuery.has_property("install")
         || Application.directrix()->m_varTopicQuery.has_property("uninstall")))
      {

         if(m_pfontopus->create_system_user("system") == NULL)
            return false;

      }

      if(!m_pfontopus->initialize_instance())
         return false;


      if(!::base::application::initialize_instance())
         return false;


      return true;

   }


   bool session::initialize1()
   {

      m_spfs = canew(::fs::fs(this));

      if(m_spfs == NULL)
         return false;

      m_spfs->construct(this);

      if(!m_spfs->initialize())
         return false;

      enum_display_monitors();

      m_spcopydesk.create(allocer());

      if(!m_spcopydesk->initialize())
         return false;

      if(!::base::application::initialize1())
         return false;
    
      m_puserpresence = canew(::userpresence::userpresence(this));

      if(m_puserpresence.is_null())
      {
         TRACE("Failed to create new User Presence");
         return false;
      }

      try
      {

         m_puserpresence->construct(this);

      }
      catch(...)
      {

         TRACE("Failed to construct User Presence");

         return false;

      }


      if(!m_puserpresence->initialize())
      {

         TRACE("Failed to initialize User Presence");

         return false;

      }

      return true;

   }


   bool session::initialize()
   {

      if(!::base::application::initialize())
         return false;

      if(m_bIfs)
      {

         if(m_spfsdata.is_null())
            m_spfsdata = new ::fs::set(this);

         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         pset->m_spafsdata.add(BaseSession.m_pifs);
         pset->m_spafsdata.add(BaseSession.m_prfs);

      }


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;

      try
      {

         bOk = m_puserpresence->finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      try
      {

         bOk = ::base::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }


   int32_t session::exit_instance()
   {

      try
      {
         if(m_spcopydesk.is_set())
         {
            m_spcopydesk->finalize();
            m_spcopydesk.release();
         }
         m_splicense.release();
      }
      catch(...)
      {

      }

      ::base::application::exit_instance();

      return 0;

   }


   void session::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL,NULL,&session::monitor_enum_proc,(LPARAM)(dynamic_cast < ::base::session * > (this)));

#else

      // todo
      //      m_monitorinfoa.remove_all();


#endif

   }



#ifdef WINDOWSEX
   BOOL CALLBACK session::monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData)
   {
      
      ::base::session * psession = (::base::session *) dwData;
      
      psession->monitor_enum(hmonitor,hdcMonitor,lprcMonitor);
      
      return TRUE; // to enumerate all

   }

   void session::monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor)
   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(lprcMonitor);

      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      ZERO(m_monitorinfoa.last_element());

      m_hmonitora.add(hmonitor);

      m_monitorinfoa.last_element().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor,&m_monitorinfoa.last_element());

      MONITORINFO mi = m_monitorinfoa.last_element();

      TRACE0("session::monitor_enum\n");
      TRACE("upper_bound %d\n",m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcMonitor.left,mi.rcMonitor.top,mi.rcMonitor.right,mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcWork.left,mi.rcWork.top,mi.rcWork.right,mi.rcWork.bottom);

   }


#endif


   void session::get_cursor_pos(LPPOINT lppoint)
   {

      if(m_bSessionSynchronizedCursor)
      {

#ifdef METROWIN

         Windows::Foundation::Point p;

         p = m_posdata->m_pwindow->get_cursor_pos();

         lppoint->x = (LONG)p.X;

         lppoint->y = (LONG)p.Y;

#else

         ::GetCursorPos(&m_ptCursor);

#endif

      }

      if(lppoint != NULL)
      {

         *lppoint = m_ptCursor;

      }

   }


} // namespace base
































