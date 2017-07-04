#include "framework.h"
#include "aura/net/net_sockets.h"
//#include "fiasco_finder.h"


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

    //  m_schemasimple.m_pfont->create_pixel_font(FONT_SANS,16);

      m_puserpresence               = NULL;

      m_bMatterFromHttpCache        = m_paxissystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor   = m_paxissystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen   = m_paxissystem->m_bSystemSynchronizedScreen;

      m_iMainMonitor                = -1;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance                = m_pauraapp->m_hinstance;

      }

#endif

      m_bDrawCursor                 = false;


      m_bDrawCursor                 = false;

      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;



      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;

      m_psavings                    = canew(class ::aura::savings(this));

      m_bZipIsDir                   = true;

      m_pmapKeyPressed              = NULL;

      m_puserstrcontext             = NULL;

      m_puserpresence = NULL;

      //      m_paxissystem->m_basesessionptra.add_unique(this);

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


   }


   bool session::is_session()
   {

      return true;

   }


   void session::on_user_login(::fontopus::user * puser)
   {


      ::aura::session::on_user_login(puser);

   }






   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }




   bool session::process_initialize()
   {

      thisstart;

      if (!::aura::session::process_initialize())
      {

         thisfail << 1;

         return false;

      }

      thisok << 1;

      if(m_pfontopus == NULL)
      {

         m_pfontopus = create_fontopus();

         if (m_pfontopus == NULL)
         {

            thisfail << 2 << "Failed to create fontopus";

            return false;

         }

         m_pfontopus->construct(this);

      }

      if (m_pifs == NULL)
      {

         m_pifs = new ifs(this, ""); 

      }

      if (m_prfs.is_null())
      {

         m_prfs = canew(::fs::remote_native(this, ""));

      }

      if (m_pftpfs.is_null())
      {

         m_pftpfs = canew(ftpfs(this, ""));

      }

      if (m_spfsdata.is_null())
      {

         ::fs::set * pset = canew(class ::fs::set(this));

         ::fs::link * plink = canew(::fs::link(this));

         plink->fill_os_user();

         pset->m_spafsdata.add(plink);

         pset->m_spafsdata.add(canew(::fs::native(this)));

         m_spfsdata = pset;

      }

      thisok << 2;

      if (!::axis::application::process_initialize())
      {

         thisfail << 3;

         return false;

      }

      thisend;

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



   bool session::initialize_application()
   {

      if (!m_pfontopus->initialize_application())
      {

         return false;

      }

      if(Application.directrix()->m_varTopicQuery.has_property("uninstall")
         || Application.directrix()->m_varTopicQuery.has_property("install"))
      {

         if(m_pfontopus->create_system_user("system") == NULL)
            return false;

      }

      if (!::aura::session::initialize_application())
      {

         return false;

      }

      if (!::axis::application::initialize_application())
      {

         return false;

      }

      return true;

   }


   bool session::initialize()
   {

      if (!::aura::session::initialize())
      {

         return false;

      }

      if (!::axis::application::initialize())
      {

         return false;

      }

      if(m_bIfs)
      {

         if (m_spfsdata.is_null())
         {

            m_spfsdata = canew(::fs::set(this));

         }

         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);

         if(pset != NULL)
         {

            pset->m_spafsdata.add_unique(m_pifs);

            pset->m_spafsdata.add_unique(m_prfs);

         }

         ::file::listing patha;

         m_spfsdata->root_ones(patha);

      }

      ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);

      if (pset != NULL)
      {
         pset->m_spafsdata.add_unique(m_pftpfs);

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

         ::aura::del(m_pmapKeyPressed);

      }
      catch (...)
      {


      }

      try
      {

         if (m_puserpresence != NULL)
         {

            if (!m_puserpresence->finalize())
            {

               bOk = false;

            }

            ::aura::del(m_puserpresence);

         }


      }
      catch (...)
      {

         bOk = false;
      }


      try
      {

         m_spfsdata.release();

      }
      catch (...)
      {

         bOk = false;

      }


      try
      {

         ::aura::del(m_pifs);

      }
      catch (...)
      {

         bOk = false;

      }

      try
      {

         m_prfs.release();

      }
      catch (...)
      {

         bOk = false;

      }

      try
      {

         m_pftpfs.release();

      }
      catch (...)
      {

         bOk = false;

      }

      if(::ftp::command::info2::g_pTheOneAndOnly != NULL)
      {

         try
         {

            delete ::ftp::command::info2::g_pTheOneAndOnly;

         }
         catch (...)
         {

            bOk = false;

         }

      }

      try
      {

         m_pfontopus.release();

      }
      catch (...)
      {

         bOk = false;
      }

      try
      {
         ::aura::del(m_psockets);
      }
      catch (...)
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

      return bOk;

   }


   int32_t session::exit_application()
   {

      try
      {
         
         for(auto & pair : System.m_appmap)
         {
            
            try
            {
               
               if(pair.m_element2->m_paxissession == this)
               {
                  
                  pair.m_element2->m_paxissession = NULL;
                  
               }
               
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

         m_mapApplication.remove_all();

      }
      catch (...)
      {

      }

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

      ::aura::del(m_pkeyboard);

      ::axis::application::exit_application();

      ::aura::session::exit_application();

      return 0;

   }



   void session::defer_initialize_user_presence()
   {

      ::aura::session::defer_initialize_user_presence();

      userpresence().defer_initialize_user_presence();

   }


   void session::on_request(::create * pcreatecontext)
   {

      ::aura::session::on_request(pcreatecontext);

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

         if(m_iMainWkspace >= 0 && m_iMainWkspace < System.get_monitor_count())
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

         index iMainWkspace = m_iMainWkspace;

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

         index iMainMonitor = m_iMainMonitor;

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

      index iWkspace = get_best_wkspace(NULL,rect(lprect));

      return wkspace_to_monitor(lprect,iWkspace,iWkspace);

   }


   bool session::monitor_to_wkspace(LPRECT lprect)
   {

      index iMonitor = get_best_monitor(NULL,rect(lprect));

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

      index iFoundAppearance = recta.max_normal_intersect_area(rectParam,*lprect);

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
      rect r(rectParam);

      if(r.is_null())
      {

         get_cursor_pos((POINT *)&r.left);
         *((POINT*)&r.right) = *((POINT*)&r.left);

      }

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_monitor_rect(iMonitor,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(&r,rectMonitor))
            {

               if(rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if(rectMonitor.contains(r))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

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
      rect r(rectParam);

      if(r.is_null())
      {

         get_cursor_pos((POINT *)&r.left);
         *((POINT*)&r.right) = *((POINT*)&r.left);

      }

      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if(get_wkspace_rect(iWkspace,rectMonitor))
         {

            if(rectIntersect.top_left_null_intersect(&r,rectMonitor))
            {

               if(rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if(rectMonitor.contains(r))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

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





   bool session::on_create_frame_window()
   {

      if(m_pcopydesk != NULL)
         return true;

      alloc(m_pcopydesk);

      if(!m_pcopydesk->initialize())
         return false;

      return true;

   }










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


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}

   //void session::on_request(::create * pcreatecontext)
   //{

   //   ::axis::session::on_request(pcreate);

   //}

   
   string session::fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive)
   {

      string str = ::fontopus::get_cred(papp,strUsername,strPassword,strToken);

      if(str == "ok")
         return "ok";

      return "failed";

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


   string session::fontopus_get_user_sessid(const string & str)
   {

      return fontopus()->get_user()->get_sessid(str);

   }


} // namespace axis
































