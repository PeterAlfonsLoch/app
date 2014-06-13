#include "framework.h"


namespace base
{


   session::session()
   {

      m_pfontopus = create_fontopus();

      if(m_pfontopus == NULL)
         throw simple_exception(this,"could not create fontopus for ::base::session (::base::session::construct)");

      m_pfontopus->construct(this);

      m_bSessionSynchronizedCursor = true;
//      m_bSessionSynchronizedScreen = true;


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


   ::visual::cursor * session::get_cursor()
   {
      return NULL;
      /*   if (m_ecursor == ::visual::cursor_none)
            return NULL;
            else if (m_ecursor == ::visual::cursor_default)
            return System.visual().get_cursor(m_ecursorDefault);
            else
            return System.visual().get_cursor(m_ecursor);*/
   }



   ::visual::cursor * session::get_default_cursor()
   {
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

      get_monitor_rect(0,lprect);

      return 0;

   }

   index session::get_good_restore(LPRECT lprect,LPCRECT lpcrect)
   {

      rect rectRestore = *lpcrect;

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor,lpcrect);

      rect rectIntersect;

      rectIntersect.intersect(rectMonitor,rectRestore);

      ::size sizeMin;

      get_window_minimum_size(&sizeMin);

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

      }
      else
      {

         rectRestore = rectIntersect;

      }

      if(rectRestore != lprect)
      {

         *lprect = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }


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


   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }


   bool session::initialize1()
   {

      enum_display_monitors();

      if(!::base::application::initialize1())
         return false;
    
      return true;
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
































