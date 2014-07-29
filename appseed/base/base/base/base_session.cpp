#include "framework.h"



namespace base
{


   session::session(sp(::base::application) papp) :
      element(papp),
      ::thread(papp)
   {

      m_pbaseapp        = this;

      m_pbasesession    = this;

      m_pcoreplatform   = NULL;

      m_bMatterFromHttpCache = m_pbasesystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor = m_pbasesystem->m_bSystemSynchronizedCursor;
      m_bSystemSynchronizedScreen = m_pbasesystem->m_bSystemSynchronizedScreen;
      m_iMainMonitor = -1;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance = m_pbaseapp->m_hinstance;

      }

#endif


      m_bDrawCursor              = false;
      m_ecursorDefault  = ::visual::cursor_arrow;
      m_ecursor         = ::visual::cursor_default;


      m_puiMouseMoveCapture = NULL;
      m_puiLastLButtonDown = NULL;
      m_bIfs                     = true;

      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);
      m_psavings                 = canew(class ::base::savings(this));

      m_bZipIsDir                = true;


      m_pmapKeyPressed           = NULL;
      m_puserstrcontext = NULL;

      m_pbasesystem->m_basesessionptra.add_unique(this);

      m_puserschema = &m_schemasimple;

      m_schemasimple.m_pfont.create(allocer());

      m_schemasimple.m_pfont->create_pixel_font("Verdana",16);


   }


   void session::construct(sp(::base::application) papp, int iPhase)
   {

      if(iPhase == 0)
      {
         
         if(papp->is_system())
         {

            m_pfontopus = create_fontopus();

            if(m_pfontopus == NULL)
               throw simple_exception(this,"could not create fontopus for ::base::session (::base::session::construct)");

            m_pfontopus->construct(this);

         }
         m_pifs                     = new ifs(this,"");
         m_prfs                     = new ::fs::remote_native(this,"");

         ::fs::set * pset = new class ::fs::set(this);
         ::fs::link * plink = new ::fs::link(this);
         plink->fill_os_user();
         pset->m_spafsdata.add(plink);
         pset->m_spafsdata.add(new ::fs::native(this));
         m_spfsdata = pset;

      }

   }

   session::~session()
   {

      m_pbasesystem->m_basesessionptra.remove(this);

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

#ifdef WINDOWSEX

      ::visual::cursor * pcursor = get_cursor();

      if(pcursor != NULL)
      {

         ::SetCursor(pcursor->get_HCURSOR());

      }

#endif

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

   index session::get_main_wkspace(LPRECT lprect)
   {

      if(m_bSystemSynchronizedScreen)
      {

         if(m_iMainWkspace < 0 || m_iMainWkspace >= System.get_monitor_count())
         {

            return System.get_main_wkspace(lprect);

         }
         else
         {

            if(System.get_monitor_rect(m_iMainWkspace,lprect))
            {

               return m_iMainMonitor;

            }
            else
            {

               System.get_wkspace_rect(0,lprect);

               return 0;

            }

         }

      }
      else
      {

         int iMainWkspace = m_iMainWkspace;

         if(iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
         {

            iMainWkspace = 0;

         }

         if(m_rectaWkspace.get_count() <= 0)
         {

            return -1;

         }

         *lprect = m_rectaWkspace[iMainWkspace];

         return iMainWkspace;

      }

   }


   bool session::set_main_wkspace(index iWkspace)
   {

      if(iWkspace == -1)
      {

         m_iMainWkspace = -1;

         return true;

      }
      else if(iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWkspace = iWkspace;

         return true;

      }

   }

   index session::get_main_monitor(LPRECT lprect)
   {

      if(m_bSystemSynchronizedScreen)
      {

         if(m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
         {

            return System.get_main_monitor(lprect);

         }
         else
         {

            if(System.get_monitor_rect(m_iMainMonitor,lprect))
            {

               return m_iMainMonitor;

            }
            else
            {

               System.get_monitor_rect(0,lprect);

               return 0;

            }

         }

      }
      else
      {

         int iMainMonitor = m_iMainMonitor;

         if(iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
         {

            iMainMonitor = 0;

         }

         if(m_rectaMonitor.get_count() <= 0)
         {

            return -1;

         }

         *lprect = m_rectaMonitor[iMainMonitor];

         return iMainMonitor;

      }

   }


   bool session::set_main_monitor(index iMonitor)
   {

      if(iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if(iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   ::count session::get_wkspace_count()
   {

      if(m_bSystemSynchronizedScreen)
      {

         return System.get_wkspace_count();

      }
      else
      {

         return m_rectaWkspace.get_count();

      }

   }


   ::count session::get_monitor_count()
   {

      if(m_bSystemSynchronizedScreen)
      {

         return System.get_monitor_count();

      }
      else
      {

         return m_rectaMonitor.get_count();

      }

   }


   bool session::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

      if(m_bSystemSynchronizedScreen)
      {

         return System.get_monitor_rect(iMonitor, lprect);

      }
      else
      {

         if(iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
         {

            return false;

         }

         *lprect = m_rectaMonitor[iMonitor];

         return true;

      }

   }

   bool session::wkspace_to_monitor(LPRECT lprect,index iMonitor,index iWkspace)
   {

      rect rect(lprect);

      ::rect rectWkspace;

      if(!get_wkspace_rect(iWkspace,rectWkspace))
         return false;

      rect -= rectWkspace.top_left();

      ::rect rectMonitor;

      if(!get_monitor_rect(iMonitor,rectMonitor))
         return false;

      rect += rectMonitor.top_left();

      *lprect = rect;

      return true;

   }

   
   bool session::wkspace_to_monitor(LPRECT lprect)
   {
      
      int iWkspace = get_best_wkspace(NULL,lprect);

      return wkspace_to_monitor(lprect,iWkspace,iWkspace);

   }


   bool session::monitor_to_wkspace(LPRECT lprect)
   {

      int iMonitor = get_best_monitor(NULL, lprect);

      return monitor_to_wkspace(lprect,iMonitor,iMonitor);

   }


   bool session::monitor_to_wkspace(LPRECT lprect,index iWkspace,index iMonitor)
   {

      rect rect(lprect);

      ::rect rectMonitor;

      if(!get_monitor_rect(iMonitor,rectMonitor))
         return false;

      rect -= rectMonitor.top_left();

      ::rect rectWkspace;

      if(!get_wkspace_rect(iWkspace,rectWkspace))
         return false;

      rect += rectWkspace.top_left();

      *lprect = rect;

      return true;

   }




   bool session::get_wkspace_rect(index iWkspace,LPRECT lprect)
   {

      if(m_bSystemSynchronizedScreen)
      {

         return System.get_wkspace_rect(iWkspace,lprect);

      }
      else
      {

         if(iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
         {

            return false;

         }

         *lprect = m_rectaWkspace[iWkspace];

         return true;

      }

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
      int64_t iBestArea = -1;
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

         if(lprect != NULL)
         {

            *lprect = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(lprect);

      return iMatchingMonitor;

   }


   index session::get_best_wkspace(LPRECT lprect,LPCRECT lpcrect)
   {

      index iMatchingWkspace = -1;
      int64_t iBestArea = -1;
      rect rectMatch;

      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_wkspace_rect(iWkspace,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(lpcrect,rectMonitor))
            {

               if(rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }

         }

      }

      if(iMatchingWkspace >= 0)
      {

         *lprect = rectMatch;

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(lprect);

      return iMatchingWkspace;

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




   bool session::process_initialize()
   {

      if(!::base::application::process_initialize())
         return false;

      m_spuser = create_user();

      if(m_spuser == NULL)
         return false;

      m_spuser->construct(this);

      m_psockets = canew(::sockets::sockets(this));

      m_psockets->construct(this);

      if(!m_psockets->initialize1())
         throw simple_exception(this,"could not initialize (1) sockets for application (application::construct)");

      if(!m_psockets->initialize())
         throw simple_exception(this,"could not initialize sockets for application (application::construct)");

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

      m_puserstrcontext = canew(::user::str_context(this));

      if(m_puserstrcontext == NULL)
         return false;

      if(!m_spuser->initialize1())
         return false;

      if(!m_spuser->initialize2())
         return false;


      string strLocaleSystem;

      string strSchemaSystem;

      string strPath = System.dir().appdata("langstyle_settings.xml");

      if(file().exists(strPath))
      {

         string strSystem = file().as_string(strPath);

         ::xml::document docSystem(get_app());

         if(docSystem.load(strSystem))
         {

            if(docSystem.get_child("lang") != NULL)
            {

               strLocaleSystem = docSystem.get_child("lang")->get_value();

            }

            if(docSystem.get_child("style") != NULL)
            {

               strSchemaSystem = docSystem.get_child("style")->get_value();

            }

         }

      }

      string strLocale;

      string strSchema;

#ifdef METROWIN

      stringa stra;

      try
      {

         stra.explode("-",::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

      }
      catch(long)
      {


      }

      strLocale = stra[0];

      strSchema = stra[0];

#elif defined(WINDOWS)

      LANGID langid = ::GetUserDefaultLangID();

#define SPR_DEUTSCH LANG_GERMAN

      if(langid == LANG_SWEDISH)
      {
         strLocale = "se";
         strSchema = "se";
      }
      else if(langid == MAKELANGID(LANG_PORTUGUESE,SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "pt-br";
         strSchema = "pt-br";
      }
      else if(PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
         strSchema = "de";
      }
      else if(PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
         strSchema = "en";
      }
      else if(PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
         strSchema = "jp";
      }
      else if(PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
         strSchema = "pl";
      }

#endif

      if(strLocale.is_empty())
         strLocale = "se";

      if(strSchema.is_empty())
         strSchema = "se";

      if(strLocaleSystem.has_char())
         strLocale = strLocaleSystem;

      if(strSchemaSystem.has_char())
         strSchema = strSchemaSystem;

      if(Sys(this).directrix()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = Sys(this).directrix()->m_varTopicQuery["locale"].stra()[0];

      if(Sys(this).directrix()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = Sys(this).directrix()->m_varTopicQuery["schema"].stra()[0];

      if(App(this).directrix()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = App(this).directrix()->m_varTopicQuery["locale"].stra()[0];

      if(App(this).directrix()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = App(this).directrix()->m_varTopicQuery["schema"].stra()[0];


      set_locale(strLocale,::action::source::database());
      set_schema(strSchema,::action::source::database());


      str_context()->localeschema().m_idaLocale.add(strLocale);
      str_context()->localeschema().m_idaSchema.add(strSchema);


      return true;

   }


   bool session::initialize2()
   {

      if(!::base::application::initialize2())
         return false;

      fill_locale_schema(*str_context()->m_plocaleschema);

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


   bool session::initialize()
   {

      if(!::base::application::initialize())
         return false;

      if(!is_installing() && !is_uninstalling())
      {

         if(!user()->keyboard().initialize())
            return false;

      }

      if(!m_spuser->initialize())
         return false;

      user()->set_keyboard_layout(NULL,::action::source::database());


      if(m_bIfs)
      {

         if(m_spfsdata.is_null())
            m_spfsdata = new ::fs::set(this);

         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         pset->m_spafsdata.add(m_pifs);
         pset->m_spafsdata.add(m_prfs);

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


   void system::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL,NULL,&system::monitor_enum_proc,(LPARAM)(dynamic_cast < ::base::system * > (this)));

#else

      // todo
      //      m_monitorinfoa.remove_all();


#endif

   }



#ifdef WINDOWSEX
   BOOL CALLBACK system::monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData)
   {

      ::base::system * psystem = (::base::system *) dwData;

      psystem->monitor_enum(hmonitor,hdcMonitor,lprcMonitor);

      return TRUE; // to enumerate all

   }

   void system::monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor)
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

      if(m_bSystemSynchronizedCursor)
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


   sp(::user::interaction) session::get_active_guie()
   {

      return System.get_active_guie();

   }


   sp(::user::interaction) session::get_focus_guie()
   {

#if defined (METROWIN)

      return GetFocus()->interaction_impl();

#elif defined(WINDOWSEX) || defined(LINUX)

      ::user::interaction * pwnd = ::window_from_handle(::GetFocus());
      if(pwnd != NULL)
      {
         if(get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
            || ::user::window_util::IsAscendant(get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      pwnd = System.window_from_os_data(::GetFocus());
      if(pwnd != NULL)
      {
         if(get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
            || ::user::window_util::IsAscendant(get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      pwnd = m_spuiFocus;
      if(pwnd != NULL)
      {
         if(get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
            || ::user::window_util::IsAscendant(get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      return NULL;
#else

      return System.get_active_guie();

#endif

   }


   application_ptra & session::appptra()
   {

      return m_appptra;

   }


   string session::matter_as_string(const char * pszMatter,const char * pszMatter2)
   {

      var varQuery;

      varQuery["disable_ca2_sessid"] = true;

      return file().as_string(dir_matter(pszMatter,pszMatter2),varQuery);

   }

   string session::dir_matter(const char * pszMatter,const char * pszMatter2)
   {

      return dir().matter(pszMatter,pszMatter2);

   }

   bool session::is_inside_time_dir(const char * pszPath)
   {
      throw not_implemented(this);
      return false;
   }

   bool session::file_is_read_only(const char * pszPath)
   {
      throw not_implemented(this);
      return false;
   }

   string session::file_as_string(var varFile)
   {

      if(::str::begins_ci(varFile.get_string(),"http://")
         || ::str::begins_ci(varFile.get_string(),"https://"))
      {

         ::property_set set(get_app());

         return http().get(varFile.get_string(),set);

      }
      else if(::str::begins_ci(varFile["url"].get_string(),"http://")
         || ::str::begins_ci(varFile["url"].get_string(),"https://"))
      {

         ::property_set set(get_app());

         return http().get(varFile["url"].get_string(),set);

      }
      else
      {
         return file_as_string_dup(varFile.get_string());
      }

   }

   string session::dir_path(const char * psz1,const char * psz2,const char * psz3)
   {
      return ::dir::path(psz1,psz2,psz3);
   }

   string session::dir_name(const char * psz)
   {
      return ::dir::name(psz);
   }

   bool session::dir_mk(const char * psz)
   {
      return ::dir::mk(psz);
   }

   string session::file_title(const char * psz)
   {
      return ::file_title_dup(psz);
   }
   string session::file_name(const char * psz)
   {
      return ::file_name_dup(psz);
   }


   bool session::is_key_pressed(::user::e_key ekey)
   {

      if(m_pmapKeyPressed == NULL)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;

      }
         
      bool bPressed = false;
      if(ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->Lookup(::user::key_shift,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lshift,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rshift,bPressed);
         if(bPressed)
            goto ret;
      }
      else if(ekey == ::user::key_control)
      {
         m_pmapKeyPressed->Lookup(::user::key_control,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lcontrol,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rcontrol,bPressed);
         if(bPressed)
            goto ret;
      }
      else if(ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->Lookup(::user::key_alt,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lalt,bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_ralt,bPressed);
         if(bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->Lookup(ekey,bPressed);

      }

   ret:

      return bPressed;

   }

   void session::set_key_pressed(::user::e_key ekey,bool bPressed)
   {

      if(m_pmapKeyPressed == NULL)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }

   ::user::str_context * session::str_context()
   {

      return m_puserstrcontext;

   }


   void session::set_locale(const string & lpcsz,::action::context actioncontext)
   {
      string strLocale(lpcsz);
      strLocale.trim();
      m_strLocale = strLocale;
      on_set_locale(m_strLocale,actioncontext);
   }

   void session::set_schema(const string & lpcsz,::action::context actioncontext)
   {
      string strSchema(lpcsz);
      strSchema.trim();
      m_strSchema = strSchema;
      on_set_schema(m_strSchema,actioncontext);
   }

   void session::on_set_locale(const string & lpcsz,::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }

   void session::on_set_schema(const string & lpcsz,::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }


   string session::get_locale()
   {
      return m_strLocale;
   }

   string session::get_schema()
   {
      return m_strSchema;
   }


   string session::get_locale_schema_dir()
   {

      return System.dir().simple_path(get_locale(),get_schema());

   }


   string session::get_locale_schema_dir(const string & strLocale)
   {

      if(strLocale.is_empty())
      {

         return System.dir().simple_path(get_locale(),get_schema());

      }
      else
      {

         return System.dir().simple_path(strLocale,get_schema());

      }

   }


   string session::get_locale_schema_dir(const string & strLocale,const string & strSchema)
   {

      if(strLocale.is_empty())
      {

         if(strSchema.is_empty())
         {

            return System.dir().simple_path(get_locale(),get_schema());

         }
         else
         {

            return System.dir().simple_path(get_locale(),strSchema);

         }

      }
      else
      {

         if(strSchema.is_empty())
         {

            return System.dir().simple_path(strLocale,get_schema());

         }
         else
         {

            return System.dir().simple_path(strLocale,strSchema);

         }

      }

   }


   void session::fill_locale_schema(::str::international::locale_schema & localeschema,const char * pszLocale,const char * pszSchema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_idLocale = pszLocale;
      localeschema.m_idSchema = pszSchema;


      localeschema.add_locale_variant(strLocale,strSchema);
      localeschema.add_locale_variant(get_locale(),strSchema);
      localeschema.add_locale_variant(__id(std),strSchema);
      localeschema.add_locale_variant(__id(en),strSchema);


      localeschema.finalize();


   }


   void session::fill_locale_schema(::str::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      stringa straLocale;
      stringa straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      stringa stra;

      stra = Application.directrix()->m_varTopicQuery["locale"].stra();

      stra.remove_ci("_std");

      straLocale.add_unique(Application.directrix()->m_varTopicQuery["locale"].stra());

      stra = Application.directrix()->m_varTopicQuery["schema"].stra();

      stra.remove_ci("_std");

      straSchema.add_unique(Application.directrix()->m_varTopicQuery["schema"].stra());


      localeschema.m_idLocale = straLocale[0];
      localeschema.m_idSchema = straSchema[0];

      for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale],straSchema[iSchema]);

         }

      }

      for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(),straSchema[iSchema]);

      }

      for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(std),straSchema[iSchema]);

      }


      for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(en),straSchema[iSchema]);

      }

      localeschema.finalize();


   }


   ::file::binary_buffer_sp session::file_get_file(var varFile,uint32_t uiFlags)
   {

      return file().get_file(varFile,uiFlags);

   }



} // namespace base
































