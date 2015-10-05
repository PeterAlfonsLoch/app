#include "framework.h"
#include "axis/net/net_sockets.h"
#include "fiasco_finder.h"


namespace axis
{


   session::session(::aura::application * papp) :
      ::object(papp),
      ::thread(papp),
      ::aura::session(papp)
   {

      m_paxissession                = this;

      m_bMatterFromHttpCache        = m_paxissystem->m_bMatterFromHttpCache;


#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance                = m_pauraapp->m_hinstance;

      }

#endif


      m_bIfs                        = true;

      m_psavings                    = canew(class ::aura::savings(this));

      m_bZipIsDir                   = true;

      m_puserstrcontext             = NULL;


//      m_puserschema                 = &m_schemasimple;

  //    m_schemasimple.m_pfont.alloc(allocer());

    //  m_schemasimple.m_pfont->create_pixel_font("Helvetica",16);

      m_puserpresence               = NULL;

      m_bMatterFromHttpCache        = m_paxissystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor   = m_paxissystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen   = m_paxissystem->m_bSystemSynchronizedScreen;

      m_bShouldInitializeGTwf       = m_paxissystem->m_bShouldInitializeGTwf;

      m_bEnableOnDemandDrawing      = m_paxissystem->m_bEnableOnDemandDrawing;

      m_iMainMonitor                = -1;

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

      m_paxissystem->m_basesessionptra.add_unique(this);

      m_pcopydesk = NULL;


      m_pkeyboardfocus  = NULL;
      //      m_pshellimageset  = NULL;
      m_pkeyboard       = NULL;
      //    m_pufeschema      = NULL;
      //  m_pufe            = NULL;
   }


   void session::construct(::aura::application * papp, int iPhase)
   {

      if(iPhase == 0)
      {


      }


   }

   session::~session_parent
   {
      m_paxissystem->m_basesessionptra.remove(this);

      POSITION pos = m_mapApplication.get_start_position();

      string strId;

      sp(::aura::application) pbaseapp;

      while(pos != NULL)
      {

         strId.Empty();

         pbaseapp = NULL;

         m_mapApplication.get_next_assoc(pos,strId,pbaseapp);

         ::aura::application * papp = (pbaseapp);

         papp->post_thread_message(WM_QUIT);

      }

   }


   bool session::is_session()
   {

      return true;

   }




   bool session::get_auth(const string & pszForm,string & strUsername,string & strPassword)
   {
      
      return fontopus()->get_auth(pszForm, strUsername, strPassword);

   }


   //index session::get_ui_wkspace(::user::interaction * pui)
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_ui_wkspace(pui);

   //   }
   //   else
   //   {

   //      ::rect rect;

   //      pui->GetWindowRect(rect);

   //      return get_best_wkspace(NULL,rect);

   //   }


   //}

   //index session::get_main_wkspace(LPRECT lprect)
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      if(m_iMainWkspace < 0 || m_iMainWkspace >= System.get_monitor_count())
   //      {

   //         return System.get_main_wkspace(lprect);

   //      }
   //      else
   //      {

   //         if(System.get_monitor_rect(m_iMainWkspace,lprect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            System.get_wkspace_rect(0,lprect);

   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      int iMainWkspace = m_iMainWkspace;

   //      if(iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
   //      {

   //         iMainWkspace = 0;

   //      }

   //      if(m_rectaWkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      *lprect = m_rectaWkspace[iMainWkspace];

   //      return iMainWkspace;

   //   }

   //}


   //bool session::set_main_wkspace(index iWkspace)
   //{

   //   if(iWkspace == -1)
   //   {

   //      m_iMainWkspace = -1;

   //      return true;

   //   }
   //   else if(iWkspace < 0 || iWkspace >= get_wkspace_count())
   //   {

   //      return false;

   //   }
   //   else
   //   {

   //      m_iMainWkspace = iWkspace;

   //      return true;

   //   }

   //}

   //index session::get_main_monitor(LPRECT lprect)
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      if(m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
   //      {

   //         return System.get_main_monitor(lprect);

   //      }
   //      else
   //      {

   //         if(System.get_monitor_rect(m_iMainMonitor,lprect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            System.get_monitor_rect(0,lprect);

   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      int iMainMonitor = m_iMainMonitor;

   //      if(iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
   //      {

   //         iMainMonitor = 0;

   //      }

   //      if(m_rectaMonitor.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      *lprect = m_rectaMonitor[iMainMonitor];

   //      return iMainMonitor;

   //   }

   //}


   //bool session::set_main_monitor(index iMonitor)
   //{

   //   if(iMonitor == -1)
   //   {

   //      m_iMainMonitor = -1;

   //      return true;

   //   }
   //   else if(iMonitor < 0 || iMonitor >= get_monitor_count())
   //   {

   //      return false;

   //   }
   //   else
   //   {

   //      m_iMainMonitor = iMonitor;

   //      return true;

   //   }

   //}


   //::count session::get_wkspace_count()
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_count();

   //   }
   //   else
   //   {

   //      return m_rectaWkspace.get_count();

   //   }

   //}


   //::count session::get_monitor_count()
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_count();

   //   }
   //   else
   //   {

   //      return m_rectaMonitor.get_count();

   //   }

   //}


   //bool session::get_monitor_rect(index iMonitor,LPRECT lprect)
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_rect(iMonitor, lprect);

   //   }
   //   else
   //   {

   //      if(iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
   //      {

   //         return false;

   //      }

   //      *lprect = m_rectaMonitor[iMonitor];

   //      return true;

   //   }

   //}

   //bool session::wkspace_to_monitor(LPRECT lprect,index iMonitor,index iWkspace)
   //{

   //   rect rect(lprect);

   //   ::rect rectWkspace;

   //   if(!get_wkspace_rect(iWkspace,rectWkspace))
   //      return false;

   //   rect -= rectWkspace.top_left();

   //   ::rect rectMonitor;

   //   if(!get_monitor_rect(iMonitor,rectMonitor))
   //      return false;

   //   rect += rectMonitor.top_left();

   //   *lprect = rect;

   //   return true;

   //}

   //
   //bool session::wkspace_to_monitor(LPRECT lprect)
   //{
   //   
   //   int iWkspace = get_best_wkspace(NULL,rect(lprect));

   //   return wkspace_to_monitor(lprect,iWkspace,iWkspace);

   //}


   //bool session::monitor_to_wkspace(LPRECT lprect)
   //{

   //   int iMonitor = get_best_monitor(NULL, rect(lprect));

   //   return monitor_to_wkspace(lprect,iMonitor,iMonitor);

   //}


   //bool session::monitor_to_wkspace(LPRECT lprect,index iWkspace,index iMonitor)
   //{

   //   rect rect(lprect);

   //   ::rect rectMonitor;

   //   if(!get_monitor_rect(iMonitor,rectMonitor))
   //      return false;

   //   rect -= rectMonitor.top_left();

   //   ::rect rectWkspace;

   //   if(!get_wkspace_rect(iWkspace,rectWkspace))
   //      return false;

   //   rect += rectWkspace.top_left();

   //   *lprect = rect;

   //   return true;

   //}




   //bool session::get_wkspace_rect(index iWkspace,LPRECT lprect)
   //{

   //   if(m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_rect(iWkspace,lprect);

   //   }
   //   else
   //   {

   //      if(iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
   //      {

   //         return false;

   //      }

   //      *lprect = m_rectaWkspace[iWkspace];

   //      return true;

   //   }

   //}

   //::count session::get_desk_monitor_count()
   //{

   //   return get_monitor_count();

   //}


   //bool session::get_desk_monitor_rect(index iMonitor,LPRECT lprect)
   //{

   //   return get_monitor_rect(iMonitor,lprect);

   //}



   //void session::get_monitor(rect_array & rectaMonitor,rect_array & rectaIntersect,const RECT & rectParam)
   //{

   //   for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
   //   {

   //      rect rectIntersect;

   //      rect rectMonitor;

   //      if(get_monitor_rect(iMonitor,rectMonitor))
   //      {

   //         if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
   //         {

   //            if(rectIntersect.area() >= 0)
   //            {

   //               rectaMonitor.add(rectMonitor);

   //               rectaIntersect.add(rectIntersect);

   //            }

   //         }

   //      }

   //   }

   //}

   //index session::get_zoneing(LPRECT lprect,const RECT & rectParam,::user::EAppearance eappearance)
   //{

   //   index iMonitor = get_best_wkspace(lprect,rectParam);

   //   int cx = width(lprect);
   //   int cy = height(lprect);

   //   if(cx <= 0 || cy <= 0)
   //   {

   //      return -1;

   //   }

   //   if(width(rectParam) <= 0 || height(rectParam) <= 0)
   //   {

   //      return -1;

   //   }


   //   int midcx = cx / 2;
   //   int midcy = cy / 2;

   //   if(eappearance == ::user::AppearanceTop)
   //   {
   //      *lprect = rect_dim(0,0,cx,midcy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceLeft)
   //   {
   //      *lprect = rect_dim(0,0,midcx,cy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceRight)
   //   {
   //      *lprect = rect_dim(midcx,0,midcx,cy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceBottom)
   //   {
   //      *lprect = rect_dim(0,midcy,cx,midcy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceTopLeft)
   //   {
   //      *lprect = rect_dim(0,0,midcx,midcy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceTopRight)
   //   {
   //      *lprect = rect_dim(midcx,0,midcx,midcy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceBottomLeft)
   //   {
   //      *lprect = rect_dim(0,midcy,midcx,midcy) + top_left(lprect);
   //   }
   //   else if(eappearance == ::user::AppearanceBottomRight)
   //   {
   //      *lprect = rect_dim(midcx,midcy,midcx,midcy) + top_left(lprect);
   //   }
   //   else
   //   {
   //      return -1;
   //   }

   //   return iMonitor;

   //}

   //index session::get_best_zoneing(::user::EAppearance * peappearance,LPRECT lprect,const RECT & rectParam)
   //{

   //   index iMonitor = get_best_monitor(lprect,rectParam);

   //   int cx = width(lprect);
   //   int cy = height(lprect);

   //   if(cx <= 0 || cy <= 0)
   //   {

   //      *peappearance = ::user::AppearanceZoomed;

   //      return iMonitor;

   //   }

   //   if(width(rectParam) <= 0 || height(rectParam) <= 0)
   //   {

   //      *peappearance = ::user::AppearanceZoomed;

   //      return iMonitor;

   //   }


   //   int midcx = cx / 2;
   //   int midcy = cy / 2;

   //   rect_array recta;
   //   array < ::user::EAppearance > aa;

   //   aa.add(::user::AppearanceTop);
   //   recta.add_dim(0,0,cx,midcy);

   //   aa.add(::user::AppearanceLeft);
   //   recta.add_dim(0,0,midcx,cy);

   //   aa.add(::user::AppearanceRight);
   //   recta.add_dim(midcx,0, midcx, cy);

   //   aa.add(::user::AppearanceBottom);
   //   recta.add_dim(0,midcy,cx,midcy);

   //   aa.add(::user::AppearanceTopLeft);
   //   recta.add_dim(0,0,midcx,midcy);

   //   aa.add(::user::AppearanceTopRight);
   //   recta.add_dim(midcx,0,midcx,midcy);

   //   aa.add(::user::AppearanceBottomLeft);
   //   recta.add_dim(0,midcy,midcx,midcy);

   //   aa.add(::user::AppearanceBottomRight);
   //   recta.add_dim(midcx,midcy,midcx,midcy);

   //   int iFoundAppearance = recta.max_normal_intersect_area(rectParam,*lprect);

   //   if(iFoundAppearance < 0)
   //   {

   //      *peappearance = ::user::AppearanceZoomed;

   //      return iMonitor;

   //   }

   //   if(lprect != NULL)
   //   {

   //      *lprect = recta[iFoundAppearance];

   //   }

   //   *peappearance = aa[iFoundAppearance];

   //   return iMonitor;

   //}

   //index session::get_best_monitor(LPRECT lprect,const RECT & rectParam)
   //{

   //   index iMatchingMonitor = -1;
   //   int64_t iBestArea = -1;
   //   rect rectMatch;

   //   for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
   //   {

   //      rect rectIntersect;

   //      rect rectMonitor;

   //      if(get_monitor_rect(iMonitor,rectMonitor))
   //      {

   //         if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
   //         {

   //            if(rectIntersect.area() > iBestArea)
   //            {

   //               iMatchingMonitor = iMonitor;

   //               iBestArea = rectIntersect.area();

   //               rectMatch = rectMonitor;

   //            }

   //         }

   //      }

   //   }

   //   if(iMatchingMonitor >= 0)
   //   {

   //      if(lprect != NULL)
   //      {

   //         *lprect = rectMatch;

   //      }

   //      return iMatchingMonitor;

   //   }

   //   iMatchingMonitor = get_main_monitor(lprect);

   //   return iMatchingMonitor;

   //}


   //index session::get_best_wkspace(LPRECT lprect,const RECT & rectParam)
   //{

   //   index iMatchingWkspace = -1;
   //   int64_t iBestArea = -1;
   //   rect rectMatch;

   //   for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
   //   {

   //      rect rectIntersect;

   //      rect rectMonitor;

   //      if(get_wkspace_rect(iWkspace,rectMonitor))
   //      {

   //         if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
   //         {

   //            if(rectIntersect.area() > iBestArea)
   //            {

   //               iMatchingWkspace = iWkspace;

   //               iBestArea = rectIntersect.area();

   //               rectMatch = rectMonitor;

   //            }

   //         }

   //      }

   //   }

   //   if(iMatchingWkspace >= 0)
   //   {

   //      *lprect = rectMatch;

   //      return iMatchingWkspace;

   //   }

   //   iMatchingWkspace = get_main_wkspace(lprect);

   //   return iMatchingWkspace;

   //}


   //index session::get_good_restore(LPRECT lprect,const RECT & rectParam)
   //{

   //   return initial_frame_position(lprect,rectParam,false);

   //}


   //index session::get_good_iconify(LPRECT lprect,const RECT & rectParam)
   //{

   //   rect rectMonitor;

   //   index iMatchingMonitor = get_best_monitor(rectMonitor,rectParam);

   //   lprect->left = rectMonitor.left;
   //   lprect->top = rectMonitor.top;
   //   lprect->right = rectMonitor.left;
   //   lprect->bottom = rectMonitor.top;

   //   return iMatchingMonitor;

   //}


   //index session::get_good_move(LPRECT lprect,const RECT & rectParam)
   //{

   //   index iMatchingMonitor = initial_frame_position(lprect,rectParam,true);

   //   if(memcmp(lprect,&rectParam,sizeof(RECT)))
   //   {

   //      return iMatchingMonitor;

   //   }
   //   else
   //   {

   //      return -1;

   //   }


   //}


   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }




   bool session::process_initialize()
   {



      if(!::aura::session::process_initialize())
         return false;


      if(m_pfontopus == NULL)
      {

         m_pfontopus = create_fontopus();

         if(m_pfontopus == NULL)
            throw simple_exception(this,"could not create fontopus for ::axis::session (::axis::session::construct)");

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



      if(!::axis::application::process_initialize())
         return false;



      m_psockets = canew(::sockets::sockets(this));

      m_psockets->construct(this);

      if(!m_psockets->initialize1())
         throw simple_exception(this,"could not initialize (1) sockets for application (application::construct)");

      if(!m_psockets->initialize())
         throw simple_exception(this,"could not initialize sockets for application (application::construct)");

      m_splicensing = new class ::fontopus::licensing(this);




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

      //m_spcopydesk.alloc(allocer());

      //if(!m_spcopydesk->initialize())
      //   return false;

      if(!::aura::session::initialize1())
         return false;

      if(!::axis::application::initialize1())
         return false;

      m_puserpresence = new ::userpresence::userpresence(this);

      if(m_puserpresence == NULL)
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


      str_context()->localeschema().m_idaLocale.add(get_locale());

      str_context()->localeschema().m_idaSchema.add(get_schema());


      return true;

   }


   bool session::initialize2()
   {

      if(!::aura::session::initialize2())
         return false;

      if(!::axis::application::initialize2())
         return false;

      fill_locale_schema(*str_context()->m_plocaleschema);

      return true;

   }



   bool session::initialize_instance()
   {
      if(!m_pfontopus->initialize_instance())
         return false;

      if(Application.directrix()->m_varTopicQuery.has_property("uninstall")
         || Application.directrix()->m_varTopicQuery.has_property("install"))
      {

         if(m_pfontopus->create_system_user("system") == NULL)
            return false;

      }



      if(!::aura::session::initialize_instance())
         return false;

      if(!::axis::application::initialize_instance())
         return false;

      return true;

   }


   bool session::initialize()
   {

      if(!::aura::session::initialize())
         return false;

      if(!::axis::application::initialize())
         return false;

      //if(!is_installing() && !is_uninstalling())
      //{

      //   if(!keyboard().initialize())
      //      return false;

      //}

      
      //set_keyboard_layout(NULL,::action::source::database());


      if(m_bIfs)
      {

         if(m_spfsdata.is_null())
            m_spfsdata = new ::fs::set(this);

         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         if(pset != NULL)
         {
            pset->m_spafsdata.add(m_pifs);
            pset->m_spafsdata.add(m_prfs);
         }

         ::file::listing patha;

         m_spfsdata->root_ones(patha);

      }
      
      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;


      try
      {

         if(!::axis::application::finalize())
         {

            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;
      }

      try
      {

         if(!::aura::session::finalize())
         {

            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;
      }



      try
      {

         if(!m_puserpresence->finalize())
         {

            bOk = false;

         }


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
         if(m_pcopydesk != NULL)
         {
            m_pcopydesk->finalize();
            ::release(m_pcopydesk);
         }
      }
      catch(...)
      {

      }

      ::axis::application::exit_instance();

      ::aura::session::exit_instance();

      return 0;

   }



   bool session::is_licensed(const char * pszId,bool bInteractive)
   {

      if(directrix()->m_varTopicQuery.has_property("install"))
         return true;

      if(directrix()->m_varTopicQuery.has_property("uninstall"))
         return true;

      if(&licensing() == NULL)
      {

         return false;

      }

      if(!licensing().has(pszId,bInteractive))
      {

         licensing().m_mapInfo.remove_key(pszId);

         return false;

      }

      return true;

   }

   ::fontopus::user * session::get_user()
   {

      return m_pfontopus->get_user();

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





//   void system::enum_display_monitors()
//   {
//
//#ifdef WINDOWSEX
//
//      m_monitorinfoa.remove_all();
//
//      ::EnumDisplayMonitors(NULL,NULL,&system::monitor_enum_proc,(LPARAM)(dynamic_cast < ::axis::system * > (this)));
//
//#else
//
//      // todo
//      //      m_monitorinfoa.remove_all();
//
//
//#endif
//
//   }
//
//
//
//#ifdef WINDOWSEX
//   BOOL CALLBACK system::monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData)
//   {
//
//      ::axis::system * psystem = (::axis::system *) dwData;
//
//      psystem->monitor_enum(hmonitor,hdcMonitor,lprcMonitor);
//
//      return TRUE; // to enumerate all
//
//   }
//
//   void system::monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor)
//   {
//
//      UNREFERENCED_PARAMETER(hdcMonitor);
//      UNREFERENCED_PARAMETER(lprcMonitor);
//
//      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);
//
//      ZERO(m_monitorinfoa.last());
//
//      m_hmonitora.add(hmonitor);
//
//      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);
//
//      ::GetMonitorInfo(hmonitor,&m_monitorinfoa.last());
//
//      MONITORINFO mi = m_monitorinfoa.last();
//
//      TRACE0("session::monitor_enum\n");
//      TRACE("upper_bound %d\n",m_monitorinfoa.get_upper_bound());
//      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcMonitor.left,mi.rcMonitor.top,mi.rcMonitor.right,mi.rcMonitor.bottom);
//      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcWork.left,mi.rcWork.top,mi.rcWork.right,mi.rcWork.bottom);
//
//   }
//
//
//#endif
//

//   void session::get_cursor_pos(LPPOINT lppoint)
//   {
//
//      if(m_bSystemSynchronizedCursor)
//      {
//
//#ifdef METROWIN
//
//         Windows::Foundation::Point p;
//
//         p = System.m_posdata->m_pwindow->get_cursor_pos();
//
//         lppoint->x = (LONG)p.X;
//
//         lppoint->y = (LONG)p.Y;
//
//#else
//
//         ::GetCursorPos(&m_ptCursor);
//
//#endif
//
//      }
//
//      if(lppoint != NULL)
//      {
//
//         *lppoint = m_ptCursor;
//
//      }
//
//   }







   //bool session::is_key_pressed(::user::e_key ekey)
   //{

   //   if(m_pmapKeyPressed == NULL)
   //   {

   //      m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;

   //   }
   //      
   //   bool bPressed = false;
   //   if(ekey == ::user::key_shift)
   //   {
   //      m_pmapKeyPressed->Lookup(::user::key_shift,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_lshift,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_rshift,bPressed);
   //      if(bPressed)
   //         goto ret;
   //   }
   //   else if(ekey == ::user::key_control)
   //   {
   //      m_pmapKeyPressed->Lookup(::user::key_control,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_lcontrol,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_rcontrol,bPressed);
   //      if(bPressed)
   //         goto ret;
   //   }
   //   else if(ekey == ::user::key_alt)
   //   {
   //      m_pmapKeyPressed->Lookup(::user::key_alt,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_lalt,bPressed);
   //      if(bPressed)
   //         goto ret;
   //      m_pmapKeyPressed->Lookup(::user::key_ralt,bPressed);
   //      if(bPressed)
   //         goto ret;
   //   }
   //   else
   //   {

   //      m_pmapKeyPressed->Lookup(ekey,bPressed);

   //   }

   //ret:

   //   return bPressed;

   //}

   //void session::set_key_pressed(::user::e_key ekey,bool bPressed)
   //{

   //   if(m_pmapKeyPressed == NULL)
   //   {

   //      m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;

   //   }

   //   (*m_pmapKeyPressed)[ekey] = bPressed;

   //}

   

   //void session::set_locale(const string & lpcsz,::action::context actioncontext)
   //{
   //   string strLocale(lpcsz);
   //   strLocale.trim();
   //   m_strLocale = strLocale;
   //   on_set_locale(m_strLocale,actioncontext);
   //}

   //void session::set_schema(const string & lpcsz,::action::context actioncontext)
   //{
   //   string strSchema(lpcsz);
   //   strSchema.trim();
   //   m_strSchema = strSchema;
   //   on_set_schema(m_strSchema,actioncontext);
   //}

   //void session::on_set_locale(const string & lpcsz,::action::context actioncontext)
   //{
   //   UNREFERENCED_PARAMETER(actioncontext);
   //   UNREFERENCED_PARAMETER(lpcsz);
   //   //System.appa_load_string_table();
   //}

   //void session::on_set_schema(const string & lpcsz,::action::context actioncontext)
   //{
   //   UNREFERENCED_PARAMETER(actioncontext);
   //   UNREFERENCED_PARAMETER(lpcsz);
   //   //System.appa_load_string_table();
   //}


   //string session::get_locale()
   //{
   //   return m_strLocale;
   //}

   //string session::get_schema()
   //{
   //   return m_strSchema;
   //}


   //string session::get_locale_schema_dir()
   //{

   //   return System.dir().simple_path(get_locale(),get_schema());

   //}


   //string session::get_locale_schema_dir(const string & strLocale)
   //{

   //   if(strLocale.is_empty())
   //   {

   //      return System.dir().simple_path(get_locale(),get_schema());

   //   }
   //   else
   //   {

   //      return System.dir().simple_path(strLocale,get_schema());

   //   }

   //}


   //string session::get_locale_schema_dir(const string & strLocale,const string & strSchema)
   //{

   //   if(strLocale.is_empty())
   //   {

   //      if(strSchema.is_empty())
   //      {

   //         return System.dir().simple_path(get_locale(),get_schema());

   //      }
   //      else
   //      {

   //         return System.dir().simple_path(get_locale(),strSchema);

   //      }

   //   }
   //   else
   //   {

   //      if(strSchema.is_empty())
   //      {

   //         return System.dir().simple_path(strLocale,get_schema());

   //      }
   //      else
   //      {

   //         return System.dir().simple_path(strLocale,strSchema);

   //      }

   //   }

   //}


   //void session::fill_locale_schema(::str::international::locale_schema & localeschema,const char * pszLocale,const char * pszSchema)
   //{


   //   localeschema.m_idaLocale.remove_all();
   //   localeschema.m_idaSchema.remove_all();


   //   string strLocale(pszLocale);
   //   string strSchema(pszSchema);


   //   localeschema.m_idLocale = pszLocale;
   //   localeschema.m_idSchema = pszSchema;


   //   localeschema.add_locale_variant(strLocale,strSchema);
   //   localeschema.add_locale_variant(get_locale(),strSchema);
   //   localeschema.add_locale_variant(__id(std),strSchema);
   //   localeschema.add_locale_variant(__id(en),strSchema);


   //   localeschema.finalize();


   //}


   //void session::fill_locale_schema(::str::international::locale_schema & localeschema)
   //{


   //   localeschema.m_idaLocale.remove_all();
   //   localeschema.m_idaSchema.remove_all();


   //   //localeschema.m_bAddAlternateStyle = true;


   //   stringa straLocale;
   //   stringa straSchema;

   //   straLocale.add(get_locale());
   //   straSchema.add(get_schema());


   //   stringa stra;

   //   stra = Application.directrix()->m_varTopicQuery["locale"].stra();

   //   stra.remove_ci("_std");

   //   straLocale.add_unique(Application.directrix()->m_varTopicQuery["locale"].stra());

   //   stra = Application.directrix()->m_varTopicQuery["schema"].stra();

   //   stra.remove_ci("_std");

   //   straSchema.add_unique(Application.directrix()->m_varTopicQuery["schema"].stra());


   //   localeschema.m_idLocale = straLocale[0];
   //   localeschema.m_idSchema = straSchema[0];

   //   for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
   //   {

   //      for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
   //      {

   //         localeschema.add_locale_variant(straLocale[iLocale],straSchema[iSchema]);

   //      }

   //   }

   //   for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
   //   {

   //      localeschema.add_locale_variant(get_locale(),straSchema[iSchema]);

   //   }

   //   for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
   //   {

   //      localeschema.add_locale_variant(__id(std),straSchema[iSchema]);

   //   }


   //   for(index iSchema = 0; iSchema < straLocale.get_count(); iSchema++)
   //   {

   //      localeschema.add_locale_variant(__id(en),straSchema[iSchema]);

   //   }

   //   localeschema.finalize();


   //}



   void session::defer_initialize_user_presence()
   {

      userpresence().defer_initialize_user_presence();

   }

   //string session::get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   //{

   //   throw interface_only_exception(papp);

   //   return "";

   //}

   ::fontopus::fontopus * session::create_fontopus()
   {

      return canew(::fontopus::fontopus(this));

   }


   ::fontopus::user * session::safe_get_user()
   {

      if(m_pfontopus == NULL)
         return NULL;

      return m_pfontopus->m_puser;

   }

   void session::on_request(sp(::create) pcreate)
   {

      ::aura::session::on_request(pcreate);

   }

} // namespace axis


































//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


namespace axis
{


   //session::session(::aura::application * papp):
   //   ::object(papp),
   //   ::thread(papp),
   //   ::aura::session(papp),
   //   axis::session(papp)
   //{

   //   m_pbasesession                = this;



   //}


   //void session::construct(::aura::application * papp,int iPhase)
   //{

   //   ::axis::session::construct(papp,iPhase);
   //}

   //session::~session_parent
   //{


   //}


   //   bool session::is_session()
   //{

   //   return true;

   //}



   void session::set_cursor(::visual::cursor * pcursor)
   {

      m_ecursor = ::visual::cursor_visual;

#ifdef WINDOWSEX

      m_pcursor = pcursor;

      if(pcursor != NULL)
      {

         ::SetCursor(pcursor->get_HCURSOR());

      }

#endif

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





   ::user::copydesk & session::copydesk()
   {

      return *m_pcopydesk;

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

         return System.get_monitor_rect(iMonitor,lprect);

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

      int iWkspace = get_best_wkspace(NULL,rect(lprect));

      return wkspace_to_monitor(lprect,iWkspace,iWkspace);

   }


   bool session::monitor_to_wkspace(LPRECT lprect)
   {

      int iMonitor = get_best_monitor(NULL,rect(lprect));

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


   void session::get_monitor(rect_array & rectaMonitor,rect_array & rectaIntersect,const RECT & rectParam)
   {

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_monitor_rect(iMonitor,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
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

   index session::get_zoneing(LPRECT lprect,const RECT & rectParam,::user::EAppearance eappearance)
   {

      index iMonitor = get_best_wkspace(lprect,rectParam);

      int cx = width(lprect);
      int cy = height(lprect);

      if(cx <= 0 || cy <= 0)
      {

         return -1;

      }

      if(width(rectParam) <= 0 || height(rectParam) <= 0)
      {

         return -1;

      }


      int midcx = cx / 2;
      int midcy = cy / 2;

      if(eappearance == ::user::AppearanceTop)
      {
         *lprect = rect_dim(0,0,cx,midcy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceLeft)
      {
         *lprect = rect_dim(0,0,midcx,cy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceRight)
      {
         *lprect = rect_dim(midcx,0,midcx,cy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceBottom)
      {
         *lprect = rect_dim(0,midcy,cx,midcy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceTopLeft)
      {
         *lprect = rect_dim(0,0,midcx,midcy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceTopRight)
      {
         *lprect = rect_dim(midcx,0,midcx,midcy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceBottomLeft)
      {
         *lprect = rect_dim(0,midcy,midcx,midcy) + top_left(lprect);
      }
      else if(eappearance == ::user::AppearanceBottomRight)
      {
         *lprect = rect_dim(midcx,midcy,midcx,midcy) + top_left(lprect);
      }
      else
      {
         return -1;
      }

      return iMonitor;

   }

   index session::get_best_zoneing(::user::EAppearance * peappearance,LPRECT lprect,const RECT & rectParam)
   {

      index iMonitor = get_best_monitor(lprect,rectParam);

      int cx = width(lprect);
      int cy = height(lprect);

      if(cx <= 0 || cy <= 0)
      {

         *peappearance = ::user::AppearanceZoomed;

         return iMonitor;

      }

      if(width(rectParam) <= 0 || height(rectParam) <= 0)
      {

         *peappearance = ::user::AppearanceZoomed;

         return iMonitor;

      }


      int midcx = cx / 2;
      int midcy = cy / 2;

      rect_array recta;
      array < ::user::EAppearance > aa;

      aa.add(::user::AppearanceTop);
      recta.add_dim(0,0,cx,midcy);

      aa.add(::user::AppearanceLeft);
      recta.add_dim(0,0,midcx,cy);

      aa.add(::user::AppearanceRight);
      recta.add_dim(midcx,0,midcx,cy);

      aa.add(::user::AppearanceBottom);
      recta.add_dim(0,midcy,cx,midcy);

      aa.add(::user::AppearanceTopLeft);
      recta.add_dim(0,0,midcx,midcy);

      aa.add(::user::AppearanceTopRight);
      recta.add_dim(midcx,0,midcx,midcy);

      aa.add(::user::AppearanceBottomLeft);
      recta.add_dim(0,midcy,midcx,midcy);

      aa.add(::user::AppearanceBottomRight);
      recta.add_dim(midcx,midcy,midcx,midcy);

      int iFoundAppearance = recta.max_normal_intersect_area(rectParam,*lprect);

      if(iFoundAppearance < 0)
      {

         *peappearance = ::user::AppearanceZoomed;

         return iMonitor;

      }

      if(lprect != NULL)
      {

         *lprect = recta[iFoundAppearance];

      }

      *peappearance = aa[iFoundAppearance];

      return iMonitor;

   }

   index session::get_best_monitor(LPRECT lprect,const RECT & rectParam)
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

            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
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


   index session::get_best_wkspace(LPRECT lprect,const RECT & rectParam)
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

            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
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


   index session::get_good_iconify(LPRECT lprect,const RECT & rectParam)
   {

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor,rectParam);

      lprect->left = rectMonitor.left;
      lprect->top = rectMonitor.top;
      lprect->right = rectMonitor.left;
      lprect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }



   //bool  session::get_window_minimum_size(LPSIZE lpsize)
   //{

   //   lpsize->cx = 184 + 177;

   //   lpsize->cy = 184 + 177;

   //   return true;

   //}







   bool session::on_create_frame_window()
   {

      if(m_pcopydesk != NULL)
         return true;

      alloc(m_pcopydesk);

      if(!m_pcopydesk->initialize())
         return false;

      return true;

   }







   //bool session::initialize_instance()
   //{

   //   if(!::axis::session::initialize_instance())
   //      return false;

   //   if(!::base::application::initialize_instance())
   //      return false;





   //   return true;

   //}


   //bool session::initialize()
   //{

   //   if(!::axis::session::initialize())
   //      return false;

   //   if(!::base::application::initialize())
   //      return false;

   //   //if(!is_installing() && !is_uninstalling() && System.m_bAdvancedGUI)
   //   //if(!is_uninstalling() && System.m_bAdvancedGUI)
   //   //{


   //   //}

   //   if(!m_puser->initialize())
   //      return false;


   //   return true;

   //}




   void system::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL,NULL,&system::monitor_enum_proc,(LPARAM)(dynamic_cast < ::axis::system * > (this)));

#else

      // todo
      //      m_monitorinfoa.remove_all();


#endif

   }



#ifdef WINDOWSEX
   BOOL CALLBACK system::monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData)
   {

      ::axis::system * psystem = (::axis::system *) dwData;

      psystem->monitor_enum(hmonitor,hdcMonitor,lprcMonitor);

      return TRUE; // to enumerate all

   }

   void system::monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor)
   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(lprcMonitor);

      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      ZERO(m_monitorinfoa.last());

      m_hmonitora.add(hmonitor);

      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor,&m_monitorinfoa.last());

      MONITORINFO mi = m_monitorinfoa.last();

      TRACE0("session::monitor_enum\n");
      TRACE("upper_bound %d\n",m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcMonitor.left,mi.rcMonitor.top,mi.rcMonitor.right,mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n",mi.rcWork.left,mi.rcWork.top,mi.rcWork.right,mi.rcWork.bottom);

   }


#endif


   void session::get_cursor_pos(LPPOINT lppoint)
   {


      if(lppoint != NULL)
      {

         *lppoint = m_ptCursor;

      }

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


   ::visual::cursor * session::get_cursor()
   {

      if(m_ecursor == ::visual::cursor_visual)
      {

         return m_pcursor;

      }

      return NULL;

   }


   ::visual::cursor * session::get_default_cursor()
   {

      return NULL;

   }

   /*::aura::str_context * session::str_context()
   {

   return m_puserstrcontext;

   }
   */








   //COLORREF session::get_default_color(uint64_t ui)
   //{

   //   switch(ui)
   //   {
   //   case COLOR_3DFACE:
   //      return ARGB(127,192,192,184);
   //   case COLOR_WINDOW:
   //      return ARGB(127,255,255,255);
   //   case COLOR_3DLIGHT:
   //      return ARGB(127,218,218,210);
   //   case COLOR_3DHIGHLIGHT:
   //      return ARGB(127,238,238,230);
   //   case COLOR_3DSHADOW:
   //      return ARGB(127,138,138,130);
   //   case COLOR_3DDKSHADOW:
   //      return ARGB(127,84,84,77);
   //   default:
   //      break;
   //   }

   //   return ARGB(127,0,0,0);

   //}



   bool session::on_ui_mouse_message(::user::mouse * pmouse)
   {


      //::axis::session::on_ui_mouse_message(pmouse);

      if(pmouse->m_pt == pmouse->m_ptDesired)
      {

         m_ptCursor = pmouse->m_pt;

      }



      // user presence status activity reporting
      if(pmouse->get_message() == WM_LBUTTONDOWN
         || pmouse->get_message() == WM_RBUTTONDOWN
         || pmouse->get_message() == WM_MBUTTONDOWN
         || pmouse->get_message() == WM_MOUSEMOVE)
      {

         if(fontopus() != NULL && fontopus()->m_puser != NULL)
         {

            if(ApplicationUser.m_ppresence != NULL)
            {

               try
               {

                  ApplicationUser.m_ppresence->report_activity();

               }
               catch(...)
               {

               }

            }

         }

      }

      return true;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}

   //void session::on_request(sp(::create) pcreate)
   //{

   //   ::axis::session::on_request(pcreate);

   //}

   string session::get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::fontopus::get_cred(papp,strUsername,strPassword,strToken);

      if(str == "ok")
         return "ok";

      return "failed";

   }


   void session::on_user_login(::fontopus::user * puser)
   {




   }


   ::user::keyboard & session::keyboard()
   {

      if(m_pkeyboard == NULL)
      {

         m_pkeyboard = new ::user::keyboard(m_pauraapp);

         if(m_pkeyboard == NULL)
            throw simple_exception(get_app(),"Could not create keyboard");

         if(!m_pkeyboard->initialize())
            throw simple_exception(get_app(),"Could not initialize keyboard");

         Application.on_create_keyboard();

      }

      return *m_pkeyboard;

   }


   ::user::elemental * session::get_keyboard_focus()
   {
      
      if(m_pauraapp == NULL)
      {

         return NULL;

      }

      if(Application.is_session())
      {

         sp(::user::elemental) puieFocus;
         
         try
         {
            
            puieFocus = Session.get_focus_ui();
            
         }
         catch(...)
         {
            
         }

         if(m_pkeyboardfocus != NULL && puieFocus != NULL)
         {


            if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus)
            {

               return NULL;

            }

            return m_pkeyboardfocus;

         }
         else
         {

            return NULL;

         }

      }
      else if(Application.is_system())
      {

         return m_pkeyboardfocus;

      }
      else if(Application.m_pbasesession != NULL)
      {

         return Sess(get_app()).get_keyboard_focus();

      }
      else if(Application.m_pbasesystem != NULL)
      {

         return Sess(get_app()).get_keyboard_focus();

      }
      else
      {

         return NULL;

      }

   }


   void session::set_keyboard_focus(::user::elemental * pkeyboardfocus)
   {

      if(m_pkeyboardfocus != NULL && m_pkeyboardfocus != pkeyboardfocus)
      {

         ::user::elemental * pkeyboardfocusOld = m_pkeyboardfocus;


         try
         {

            if(pkeyboardfocusOld != NULL)
            {

               output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");

               if(!pkeyboardfocusOld->keyboard_focus_OnKillFocus())
               {

                  return;

               }

            }

         }
         catch(...)
         {

         }

      }

      if(pkeyboardfocus != NULL)
      {

         if(!pkeyboardfocus->keyboard_focus_OnSetFocus())
         {

            return;

         }

         if(pkeyboardfocus->get_wnd() != NULL)
         {

            if(!pkeyboardfocus->get_wnd_elemental()->on_keyboard_focus(pkeyboardfocus))
            {

               return;
               
            }

         }

      }

      m_pkeyboardfocus = pkeyboardfocus;

      on_finally_focus_set(pkeyboardfocus);

   }


   void session::on_finally_focus_set(::user::elemental * pelementalFocus)
   {


   }

   ::user::primitive * session::get_active_ui()
   {

      return NULL;

   }

   ::user::primitive * session::get_focus_ui()
   {
      return NULL;

   }


} // namespace axis
































