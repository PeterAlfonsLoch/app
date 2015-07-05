//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


namespace base
{


   session::session(::aura::application * papp) :
      object(papp),
      ::thread(papp),
      ::aura::session(papp),
      axis::session(papp)
   {

      m_pbasesession                = this;

      m_bMatterFromHttpCache        = m_pbasesystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor   = m_pbasesystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen   = m_pbasesystem->m_bSystemSynchronizedScreen;

      m_bShouldInitializeGTwf       = m_pbasesystem->m_bShouldInitializeGTwf;

      m_bEnableOnDemandDrawing      = m_pbasesystem->m_bEnableOnDemandDrawing;

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

      m_pschemasimple               = canew(::user::schema_simple_impl);

      m_puserschema                 = m_pschemasimple;

      m_pschemasimple->m_pfont.alloc(allocer());

      m_pschemasimple->m_pfont->create_pixel_font("Helvetica",16);


      m_pcopydesk = NULL;

      m_puiFocus = NULL;

      m_pschemasimple               = canew(::user::schema_simple_impl);

      m_puserschema                 = m_pschemasimple;

      m_pschemasimple->m_pfont.alloc(allocer());

      m_pschemasimple->m_pfont->create_pixel_font("Helvetica",16);

      m_puiFocus = NULL;



   }


   //void session::construct(::aura::application * papp, int iPhase)
   //{

   //   ::axis::session::construct(papp,iPhase);
   //}

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


//   bool session::is_session()
//   {
//
//      return true;
//
//   }
//
//
//
//   void session::set_cursor(::visual::cursor * pcursor)
//   {
//
//      m_ecursor = ::visual::cursor_visual;
//
//#ifdef WINDOWSEX
//
//      if(pcursor != NULL)
//      {
//
//         ::winsetcursor(pcursor->get_HCURSOR());
//
//      }
//
//#endif
//
//   }
//
//   void session::set_cursor(::visual::e_cursor ecursor)
//   {
//
//      m_ecursor = ecursor;
//
//#ifdef WINDOWSEX
//
//      ::visual::cursor * pcursor = get_cursor();
//
//      if(pcursor != NULL)
//      {
//
//         ::winsetcursor(pcursor->get_HCURSOR());
//
//      }
//
//#endif
//
//   }
//
//
//   void session::set_default_cursor(::visual::e_cursor ecursor)
//   {
//
//      if(ecursor == ::visual::cursor_default)
//      {
//
//         m_ecursorDefault = ::visual::cursor_arrow;
//
//      }
//      else
//      {
//
//         m_ecursorDefault = ecursor;
//
//      }
//
//   }
//
//
//
//   COLORREF session::get_default_color(uint64_t ui)
//   {
//
//      switch(ui)
//      {
//      case COLOR_3DFACE:
//         return ARGB(127,192,192,184);
//      case COLOR_WINDOW:
//         return ARGB(127,255,255,255);
//      case COLOR_3DLIGHT:
//         return ARGB(127,218,218,210);
//      case COLOR_3DHIGHLIGHT:
//         return ARGB(127,238,238,230);
//      case COLOR_3DSHADOW:
//         return ARGB(127,138,138,130);
//      case COLOR_3DDKSHADOW:
//         return ARGB(127,84,84,77);
//      default:
//         break;
//      }
//
//      return ARGB(127,0,0,0);
//
//   }
//
//
//
//
//
//   ::base::copydesk & session::copydesk()
//   {
//
//      return *m_pcopydesk;
//
//   }
//
//
//   index session::get_ui_wkspace(::user::interaction * pui)
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         return System.get_ui_wkspace(pui);
//
//      }
//      else
//      {
//
//         ::rect rect;
//
//         pui->GetWindowRect(rect);
//
//         return get_best_wkspace(NULL,rect);
//
//      }
//
//
//   }
//
//   index session::get_main_wkspace(LPRECT lprect)
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         if(m_iMainWkspace < 0 || m_iMainWkspace >= System.get_monitor_count())
//         {
//
//            return System.get_main_wkspace(lprect);
//
//         }
//         else
//         {
//
//            if(System.get_monitor_rect(m_iMainWkspace,lprect))
//            {
//
//               return m_iMainMonitor;
//
//            }
//            else
//            {
//
//               System.get_wkspace_rect(0,lprect);
//
//               return 0;
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         int iMainWkspace = m_iMainWkspace;
//
//         if(iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
//         {
//
//            iMainWkspace = 0;
//
//         }
//
//         if(m_rectaWkspace.get_count() <= 0)
//         {
//
//            return -1;
//
//         }
//
//         *lprect = m_rectaWkspace[iMainWkspace];
//
//         return iMainWkspace;
//
//      }
//
//   }
//
//
//   bool session::set_main_wkspace(index iWkspace)
//   {
//
//      if(iWkspace == -1)
//      {
//
//         m_iMainWkspace = -1;
//
//         return true;
//
//      }
//      else if(iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//      else
//      {
//
//         m_iMainWkspace = iWkspace;
//
//         return true;
//
//      }
//
//   }
//
//   index session::get_main_monitor(LPRECT lprect)
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         if(m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
//         {
//
//            return System.get_main_monitor(lprect);
//
//         }
//         else
//         {
//
//            if(System.get_monitor_rect(m_iMainMonitor,lprect))
//            {
//
//               return m_iMainMonitor;
//
//            }
//            else
//            {
//
//               System.get_monitor_rect(0,lprect);
//
//               return 0;
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         int iMainMonitor = m_iMainMonitor;
//
//         if(iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
//         {
//
//            iMainMonitor = 0;
//
//         }
//
//         if(m_rectaMonitor.get_count() <= 0)
//         {
//
//            return -1;
//
//         }
//
//         *lprect = m_rectaMonitor[iMainMonitor];
//
//         return iMainMonitor;
//
//      }
//
//   }
//
//
//   bool session::set_main_monitor(index iMonitor)
//   {
//
//      if(iMonitor == -1)
//      {
//
//         m_iMainMonitor = -1;
//
//         return true;
//
//      }
//      else if(iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//      else
//      {
//
//         m_iMainMonitor = iMonitor;
//
//         return true;
//
//      }
//
//   }
//
//
//   ::count session::get_wkspace_count()
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         return System.get_wkspace_count();
//
//      }
//      else
//      {
//
//         return m_rectaWkspace.get_count();
//
//      }
//
//   }
//
//
//   ::count session::get_monitor_count()
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         return System.get_monitor_count();
//
//      }
//      else
//      {
//
//         return m_rectaMonitor.get_count();
//
//      }
//
//   }
//
//
//   bool session::get_monitor_rect(index iMonitor,LPRECT lprect)
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         return System.get_monitor_rect(iMonitor, lprect);
//
//      }
//      else
//      {
//
//         if(iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
//         {
//
//            return false;
//
//         }
//
//         *lprect = m_rectaMonitor[iMonitor];
//
//         return true;
//
//      }
//
//   }
//
//   bool session::wkspace_to_monitor(LPRECT lprect,index iMonitor,index iWkspace)
//   {
//
//      rect rect(lprect);
//
//      ::rect rectWkspace;
//
//      if(!get_wkspace_rect(iWkspace,rectWkspace))
//         return false;
//
//      rect -= rectWkspace.top_left();
//
//      ::rect rectMonitor;
//
//      if(!get_monitor_rect(iMonitor,rectMonitor))
//         return false;
//
//      rect += rectMonitor.top_left();
//
//      *lprect = rect;
//
//      return true;
//
//   }
//
//
//   bool session::wkspace_to_monitor(LPRECT lprect)
//   {
//
//      int iWkspace = get_best_wkspace(NULL,rect(lprect));
//
//      return wkspace_to_monitor(lprect,iWkspace,iWkspace);
//
//   }
//
//
//   bool session::monitor_to_wkspace(LPRECT lprect)
//   {
//
//      int iMonitor = get_best_monitor(NULL, rect(lprect));
//
//      return monitor_to_wkspace(lprect,iMonitor,iMonitor);
//
//   }
//
//
//   bool session::monitor_to_wkspace(LPRECT lprect,index iWkspace,index iMonitor)
//   {
//
//      rect rect(lprect);
//
//      ::rect rectMonitor;
//
//      if(!get_monitor_rect(iMonitor,rectMonitor))
//         return false;
//
//      rect -= rectMonitor.top_left();
//
//      ::rect rectWkspace;
//
//      if(!get_wkspace_rect(iWkspace,rectWkspace))
//         return false;
//
//      rect += rectWkspace.top_left();
//
//      *lprect = rect;
//
//      return true;
//
//   }
//
//
//
//
//   bool session::get_wkspace_rect(index iWkspace,LPRECT lprect)
//   {
//
//      if(m_bSystemSynchronizedScreen)
//      {
//
//         return System.get_wkspace_rect(iWkspace,lprect);
//
//      }
//      else
//      {
//
//         if(iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
//         {
//
//            return false;
//
//         }
//
//         *lprect = m_rectaWkspace[iWkspace];
//
//         return true;
//
//      }
//
//   }
//
//   ::count session::get_desk_monitor_count()
//   {
//
//      return get_monitor_count();
//
//   }
//
//
//   bool session::get_desk_monitor_rect(index iMonitor,LPRECT lprect)
//   {
//
//      return get_monitor_rect(iMonitor,lprect);
//
//   }
//
//
//   index session::initial_frame_position(LPRECT lprect,const RECT & rectParam, bool bMove, ::user::interaction * pui)
//   {
//
//      rect rectRestore(rectParam);
//
//      rect rectMonitor;
//
//      index iMatchingMonitor = get_best_monitor(rectMonitor,rectParam);
//
//      ::size sizeMin;
//
//      if(pui != NULL)
//      {
//
//         pui->get_window_minimum_size(sizeMin);
//
//      }
//      else
//      {
//
//         get_window_minimum_size(&sizeMin);
//
//      }
//
//      rect rectIntersect;
//
//      if(bMove)
//      {
//
//         rect_array rectaMonitor;
//
//         rect_array rectaIntersect;
//
//         get_monitor(rectaMonitor,rectaIntersect,rectParam);
//
//         rectaIntersect.get_box(rectIntersect);
//
//      }
//      else
//      {
//
//         rectIntersect.intersect(rectMonitor,&rectParam);
//
//      }
//
//      if(rectIntersect.width() < sizeMin.cx
//         || rectIntersect.height() < sizeMin.cy)
//      {
//
//         if(rectMonitor.width() / 7 + MAX(sizeMin.cx,rectMonitor.width() * 2 / 5) > rectMonitor.width()
//            || rectMonitor.height() / 7 + MAX(sizeMin.cy,rectMonitor.height() * 2 / 5) > rectMonitor.width())
//         {
//
//            rectRestore = rectMonitor;
//
//         }
//         else
//         {
//
//            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;
//
//            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;
//
//            rectRestore.right = rectRestore.left + MAX(sizeMin.cx,rectMonitor.width() * 2 / 5);
//
//            rectRestore.bottom = rectRestore.top + MAX(sizeMin.cy,rectMonitor.height() * 2 / 5);
//
//            if(rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
//            {
//
//               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right,0);
//
//            }
//
//            if(rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
//            {
//
//               rectRestore.offset(0,rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);
//
//            }
//
//         }
//
//         *lprect = rectRestore;
//
//         return iMatchingMonitor;
//
//      }
//      else
//      {
//
//         if(!bMove)
//         {
//
//            *lprect = rectIntersect;
//
//         }
//
//         return -1;
//
//      }
//
//   }
//
//   void session::get_monitor(rect_array & rectaMonitor,rect_array & rectaIntersect,const RECT & rectParam)
//   {
//
//      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
//      {
//
//         rect rectIntersect;
//
//         rect rectMonitor;
//
//         if(get_monitor_rect(iMonitor,rectMonitor))
//         {
//
//            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
//            {
//
//               if(rectIntersect.area() >= 0)
//               {
//
//                  rectaMonitor.add(rectMonitor);
//
//                  rectaIntersect.add(rectIntersect);
//
//               }
//
//            }
//
//         }
//
//      }
//
//   }
//
//   index session::get_zoneing(LPRECT lprect,const RECT & rectParam,::user::EAppearance eappearance)
//   {
//
//      index iMonitor = get_best_wkspace(lprect,rectParam);
//
//      int cx = width(lprect);
//      int cy = height(lprect);
//
//      if(cx <= 0 || cy <= 0)
//      {
//
//         return -1;
//
//      }
//
//      if(width(rectParam) <= 0 || height(rectParam) <= 0)
//      {
//
//         return -1;
//
//      }
//
//
//      int midcx = cx / 2;
//      int midcy = cy / 2;
//
//      if(eappearance == ::user::AppearanceTop)
//      {
//         *lprect = rect_dim(0,0,cx,midcy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceLeft)
//      {
//         *lprect = rect_dim(0,0,midcx,cy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceRight)
//      {
//         *lprect = rect_dim(midcx,0,midcx,cy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceBottom)
//      {
//         *lprect = rect_dim(0,midcy,cx,midcy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceTopLeft)
//      {
//         *lprect = rect_dim(0,0,midcx,midcy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceTopRight)
//      {
//         *lprect = rect_dim(midcx,0,midcx,midcy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceBottomLeft)
//      {
//         *lprect = rect_dim(0,midcy,midcx,midcy) + top_left(lprect);
//      }
//      else if(eappearance == ::user::AppearanceBottomRight)
//      {
//         *lprect = rect_dim(midcx,midcy,midcx,midcy) + top_left(lprect);
//      }
//      else
//      {
//         return -1;
//      }
//
//      return iMonitor;
//
//   }
//
//   index session::get_best_zoneing(::user::EAppearance * peappearance,LPRECT lprect,const RECT & rectParam)
//   {
//
//      index iMonitor = get_best_monitor(lprect,rectParam);
//
//      int cx = width(lprect);
//      int cy = height(lprect);
//
//      if(cx <= 0 || cy <= 0)
//      {
//
//         *peappearance = ::user::AppearanceZoomed;
//
//         return iMonitor;
//
//      }
//
//      if(width(rectParam) <= 0 || height(rectParam) <= 0)
//      {
//
//         *peappearance = ::user::AppearanceZoomed;
//
//         return iMonitor;
//
//      }
//
//
//      int midcx = cx / 2;
//      int midcy = cy / 2;
//
//      rect_array recta;
//      array < ::user::EAppearance > aa;
//
//      aa.add(::user::AppearanceTop);
//      recta.add_dim(0,0,cx,midcy);
//
//      aa.add(::user::AppearanceLeft);
//      recta.add_dim(0,0,midcx,cy);
//
//      aa.add(::user::AppearanceRight);
//      recta.add_dim(midcx,0, midcx, cy);
//
//      aa.add(::user::AppearanceBottom);
//      recta.add_dim(0,midcy,cx,midcy);
//
//      aa.add(::user::AppearanceTopLeft);
//      recta.add_dim(0,0,midcx,midcy);
//
//      aa.add(::user::AppearanceTopRight);
//      recta.add_dim(midcx,0,midcx,midcy);
//
//      aa.add(::user::AppearanceBottomLeft);
//      recta.add_dim(0,midcy,midcx,midcy);
//
//      aa.add(::user::AppearanceBottomRight);
//      recta.add_dim(midcx,midcy,midcx,midcy);
//
//      int iFoundAppearance = recta.max_normal_intersect_area(rectParam,*lprect);
//
//      if(iFoundAppearance < 0)
//      {
//
//         *peappearance = ::user::AppearanceZoomed;
//
//         return iMonitor;
//
//      }
//
//      if(lprect != NULL)
//      {
//
//         *lprect = recta[iFoundAppearance];
//
//      }
//
//      *peappearance = aa[iFoundAppearance];
//
//      return iMonitor;
//
//   }
//
//   index session::get_best_monitor(LPRECT lprect,const RECT & rectParam)
//   {
//
//      index iMatchingMonitor = -1;
//      int64_t iBestArea = -1;
//      rect rectMatch;
//
//      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
//      {
//
//         rect rectIntersect;
//
//         rect rectMonitor;
//
//         if(get_monitor_rect(iMonitor,rectMonitor))
//         {
//
//            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
//            {
//
//               if(rectIntersect.area() > iBestArea)
//               {
//
//                  iMatchingMonitor = iMonitor;
//
//                  iBestArea = rectIntersect.area();
//
//                  rectMatch = rectMonitor;
//
//               }
//
//            }
//
//         }
//
//      }
//
//      if(iMatchingMonitor >= 0)
//      {
//
//         if(lprect != NULL)
//         {
//
//            *lprect = rectMatch;
//
//         }
//
//         return iMatchingMonitor;
//
//      }
//
//      iMatchingMonitor = get_main_monitor(lprect);
//
//      return iMatchingMonitor;
//
//   }
//
//
//   index session::get_best_wkspace(LPRECT lprect,const RECT & rectParam)
//   {
//
//      index iMatchingWkspace = -1;
//      int64_t iBestArea = -1;
//      rect rectMatch;
//
//      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
//      {
//
//         rect rectIntersect;
//
//         rect rectMonitor;
//
//         if(get_wkspace_rect(iWkspace,rectMonitor))
//         {
//
//            if(rectIntersect.top_left_null_intersect(&rectParam,rectMonitor))
//            {
//
//               if(rectIntersect.area() > iBestArea)
//               {
//
//                  iMatchingWkspace = iWkspace;
//
//                  iBestArea = rectIntersect.area();
//
//                  rectMatch = rectMonitor;
//
//               }
//
//            }
//
//         }
//
//      }
//
//      if(iMatchingWkspace >= 0)
//      {
//
//         *lprect = rectMatch;
//
//         return iMatchingWkspace;
//
//      }
//
//      iMatchingWkspace = get_main_wkspace(lprect);
//
//      return iMatchingWkspace;
//
//   }
//
//
//   index session::get_good_restore(LPRECT lprect,const RECT & rectParam, ::user::interaction * pui)
//   {
//
//      return initial_frame_position(lprect,rectParam,false, pui);
//
//   }
//
//
//   index session::get_good_iconify(LPRECT lprect,const RECT & rectParam)
//   {
//
//      rect rectMonitor;
//
//      index iMatchingMonitor = get_best_monitor(rectMonitor,rectParam);
//
//      lprect->left = rectMonitor.left;
//      lprect->top = rectMonitor.top;
//      lprect->right = rectMonitor.left;
//      lprect->bottom = rectMonitor.top;
//
//      return iMatchingMonitor;
//
//   }
//
//
//   index session::get_good_move(LPRECT lprect,const RECT & rectParam, ::user::interaction * pui)
//   {
//
//      index iMatchingMonitor = initial_frame_position(lprect,rectParam,true, pui);
//
//      if(memcmp(lprect,&rectParam,sizeof(RECT)))
//      {
//
//         return iMatchingMonitor;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//
//   }
//
//
//   bool  session::get_window_minimum_size(LPSIZE lpsize)
//   {
//
//      lpsize->cx = 184 + 177;
//
//      lpsize->cy = 184 + 177;
//
//      return true;
//
//   }
//
//
//
//
bool session::process_initialize()
{



   if(!::axis::session::process_initialize())
      return false;





   if(!::base::application::process_initialize())
      return false;

   m_puser = create_user();

   if(m_puser == NULL)
      return false;

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



//
//
//   bool session::on_create_frame_window()
//   {
//
//      if(m_pcopydesk != NULL)
//         return true;
//      
//      alloc(m_pcopydesk);
//
//      if(!m_pcopydesk->initialize())
//         return false;
//
//      return true;
//
//   }
//
//
//   bool session::initialize1()
//   {
//
//      if(!::axis::session::initialize1())
//         return false;
//
//      if(!::base::application::initialize1())
//         return false;
//
//      m_puserpresence = new ::userpresence::userpresence(this);
//
//      if(m_puserpresence == NULL)
//      {
//
//         TRACE("Failed to create new User Presence");
//
//         return false;
//
//      }
//
//      try
//      {
//
//         m_puserpresence->construct(this);
//
//      }
//      catch(...)
//      {
//
//         TRACE("Failed to construct User Presence");
//
//         return false;
//
//      }
//
//
//      if(!m_puserpresence->initialize())
//      {
//
//         TRACE("Failed to initialize User Presence");
//
//         return false;
//
//      }
//
//
//      if(!m_puser->initialize1())
//         return false;
//
//      if(!m_puser->initialize2())
//         return false;
//
//      str_context()->localeschema().m_idaLocale.add(get_locale());
//
//      str_context()->localeschema().m_idaSchema.add(get_schema());
//
//      return true;
//
//   }
//
//
//   bool session::initialize2()
//   {
//
//      if(!::axis::session::initialize2())
//         return false;
//
//      if(!::base::application::initialize2())
//         return false;
//
//      fill_locale_schema(*str_context()->m_plocaleschema);
//
//      return true;
//
//   }
//
//
//
//   bool session::initialize_instance()
//   {
//
//      if(!::axis::session::initialize_instance())
//         return false;
//
//      if(!::base::application::initialize_instance())
//         return false;
//
//
//
//
//
//      return true;
//
//   }
//
//
//   bool session::initialize()
//   {
//
//      if(!::axis::session::initialize())
//         return false;
//
//      if(!::base::application::initialize())
//         return false;
//
//      //if(!is_installing() && !is_uninstalling() && System.m_bAdvancedGUI)
//      //if(!is_uninstalling() && System.m_bAdvancedGUI)
//      //{
//
//
//      //}
//
//      if(!m_puser->initialize())
//         return false;
//
//
//      return true;
//
//   }
//
//
//   bool session::finalize()
//   {
//
//      bool bOk = true;
//
//
//      try
//      {
//
//         bOk = m_puserpresence->finalize();
//
//      }
//      catch(...)
//      {
//
//         bOk = false;
//      }
//
//
//      try
//      {
//
//         bOk = ::base::application::finalize();
//
//      }
//      catch(...)
//      {
//
//         bOk = false;
//      }
//
//      try
//      {
//
//         bOk = ::axis::session::finalize();
//
//      }
//      catch(...)
//      {
//
//         bOk = false;
//      }
//
//      return bOk;
//
//   }
//
//
//   int32_t session::exit_instance()
//   {
//
//      try
//      {
//         if(m_pcopydesk != NULL)
//         {
//            m_pcopydesk->finalize();
//            ::release(m_pcopydesk);
//         }
//      }
//      catch(...)
//      {
//
//      }
//
//      ::base::application::exit_instance();
//
//      ::axis::session::exit_instance();
//
//      return 0;
//
//   }
//
//
//   void system::enum_display_monitors()
//   {
//
//#ifdef WINDOWSEX
//
//      m_monitorinfoa.remove_all();
//
//      ::EnumDisplayMonitors(NULL,NULL,&system::monitor_enum_proc,(LPARAM)(dynamic_cast < ::base::system * > (this)));
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
//      ::base::system * psystem = (::base::system *) dwData;
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
//
//
//   ::user::interaction * session::get_active_guie()
//   {
//
//#if defined (METROWIN)
//
//      return GetFocus()->m_pui;
//
//#elif defined(WINDOWSEX) || defined(LINUX)
//
//      ::user::interaction * pwnd = System.get_active_guie();
//
//      if(pwnd != NULL)
//      {
//
//         return pwnd;
//
//      }
//
//      pwnd = ((::user::interaction *)m_puiActive->m_pvoidUserInteraction);
//      
//      if(pwnd != NULL)
//      {
//
//         return pwnd;
//
//      }
//
//      return NULL;
//
//#else
//
//      return System.get_active_guie();
//
//#endif
//
//
//   }
//
//
//   ::user::interaction * session::get_focus_guie()
//   {
//
//#if defined (METROWIN)
//
//      oswindow window = GetFocus();
//
//      if(window == NULL)
//         return NULL;
//
//      return GetFocus()->m_pui;
//
//#elif defined(WINDOWSEX) || defined(LINUX)
//
//      ::user::interaction * pwnd = ::window_from_handle(::GetFocus());
//      if(pwnd != NULL)
//      {
//         if(get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
//            || ::user::window_util::IsAscendant(get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
//         {
//            return pwnd;
//         }
//         else
//         {
//            return NULL;
//         }
//      }
//      pwnd = System.window_from_os_data(::GetFocus());
//      if(pwnd != NULL)
//      {
//         if(get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
//            || ::user::window_util::IsAscendant(get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
//         {
//            return pwnd;
//         }
//         else
//         {
//            return NULL;
//         }
//      }
//      pwnd = m_puiFocus;
//      if(pwnd != NULL)
//      {
//         if(get_active_guie() != NULL
//            && (get_active_guie() == pwnd
//            || get_active_guie()->is_descendant(pwnd)))
//         {
//            return pwnd;
//         }
//         else
//         {
//            return NULL;
//         }
//      }
//      return NULL;
//#else
//
//      return System.get_active_guie();
//
//#endif
//
//   }
//
//
//   bool session::is_key_pressed(::user::e_key ekey)
//   {
//
//      if(m_pmapKeyPressed == NULL)
//      {
//
//         m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;
//
//      }
//
//      bool bPressed = false;
//      if(ekey == ::user::key_shift)
//      {
//         m_pmapKeyPressed->Lookup(::user::key_shift,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_lshift,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_rshift,bPressed);
//         if(bPressed)
//            goto ret;
//      }
//      else if(ekey == ::user::key_control)
//      {
//         m_pmapKeyPressed->Lookup(::user::key_control,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_lcontrol,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_rcontrol,bPressed);
//         if(bPressed)
//            goto ret;
//      }
//      else if(ekey == ::user::key_alt)
//      {
//         m_pmapKeyPressed->Lookup(::user::key_alt,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_lalt,bPressed);
//         if(bPressed)
//            goto ret;
//         m_pmapKeyPressed->Lookup(::user::key_ralt,bPressed);
//         if(bPressed)
//            goto ret;
//      }
//      else
//      {
//
//         m_pmapKeyPressed->Lookup(ekey,bPressed);
//
//      }
//
//   ret:
//
//      return bPressed;
//
//   }
//
//   void session::set_key_pressed(::user::e_key ekey,bool bPressed)
//   {
//
//      if(m_pmapKeyPressed == NULL)
//      {
//
//         m_pmapKeyPressed = new ::map < ::user::e_key,::user::e_key,bool,bool >;
//
//      }
//
//      (*m_pmapKeyPressed)[ekey] = bPressed;
//
//   }
//
//
//   ::visual::cursor * session::get_cursor()
//   {
//
//      if(m_pcoresession == NULL)
//         return NULL;
//
//      return m_pcoresession->get_cursor();
//
//   }
//
//
//   ::visual::cursor * session::get_default_cursor()
//   {
//
//      if(m_pcoresession == NULL)
//         return NULL;
//
//      return m_pcoresession->get_default_cursor();
//
//   }
//
//   /*::aura::str_context * session::str_context()
//   {
//
//      return m_puserstrcontext;
//
//   }
//*/
//
//
//
//
//
//   bool session::is_licensed(const char * pszId,bool bInteractive)
//   {
//
//      return ::axis::session::is_licensed(pszId,bInteractive);
//
//   }
//
//
//   void session::frame_pre_translate_message(signal_details * pobj)
//   {
//
//      try
//      {
//
//         ::user::interaction * pui = NULL;
//
//         while(get_frame(pui))
//         {
//
//            try
//            {
//
//               if(pui != NULL)
//               {
//
//                  pui->pre_translate_message(pobj);
//
//                  if(pobj->m_bRet)
//                     return;
//
//               }
//
//            }
//            catch(exit_exception & e)
//            {
//               
//               throw e;
//
//            }
//            catch(...)
//            {
//            }
//
//         }
//
//      }
//      catch(exit_exception & e)
//      {
//
//         throw e;
//
//      }
//      catch(...)
//      {
//         
//         pobj->m_bRet = true;
//
//      }
//
//   }
//
//
//
//   //   void session::set_cursor(::visual::e_cursor ecursor)
//   //   {
//   //
//   //      m_ecursor = ecursor;
//   //
//   //#ifdef WINDOWSEX
//   //
//   //      ::visual::cursor * pcursor = get_cursor();
//   //
//   //      if(pcursor != NULL)
//   //      {
//   //
//   //         ::winsetcursor(pcursor->get_HCURSOR());
//   //
//   //      }
//   //
//   //#endif
//   //
//   //   }
//   //
//   //
//   //   void session::set_default_cursor(::visual::e_cursor ecursor)
//   //   {
//   //
//   //      if(ecursor == ::visual::cursor_default)
//   //      {
//   //
//   //         m_ecursorDefault = ::visual::cursor_arrow;
//   //
//   //      }
//   //      else
//   //      {
//   //
//   //         m_ecursorDefault = ecursor;
//   //
//   //      }
//   //
//   //   }
//   //
//
//
//   //COLORREF session::get_default_color(uint64_t ui)
//   //{
//
//   //   switch(ui)
//   //   {
//   //   case COLOR_3DFACE:
//   //      return ARGB(127,192,192,184);
//   //   case COLOR_WINDOW:
//   //      return ARGB(127,255,255,255);
//   //   case COLOR_3DLIGHT:
//   //      return ARGB(127,218,218,210);
//   //   case COLOR_3DHIGHLIGHT:
//   //      return ARGB(127,238,238,230);
//   //   case COLOR_3DSHADOW:
//   //      return ARGB(127,138,138,130);
//   //   case COLOR_3DDKSHADOW:
//   //      return ARGB(127,84,84,77);
//   //   default:
//   //      break;
//   //   }
//
//   //   return ARGB(127,0,0,0);
//
//   //}
//
//
//
//   bool session::on_ui_mouse_message(::message::mouse * pmouse)
//   {
//
//
//      //::axis::session::on_ui_mouse_message(pmouse);
//
//      m_ptCursor = pmouse->m_pt;
//
//
//
//      // user presence status activity reporting
//      if(pmouse->m_uiMessage == WM_LBUTTONDOWN
//         || pmouse->m_uiMessage == WM_RBUTTONDOWN
//         || pmouse->m_uiMessage == WM_MBUTTONDOWN
//         || pmouse->m_uiMessage == WM_MOUSEMOVE)
//      {
//
//         if(fontopus() != NULL && fontopus()->m_puser != NULL)
//         {
//
//            if(ApplicationUser.m_ppresence != NULL)
//            {
//
//               try
//               {
//
//                  ApplicationUser.m_ppresence->report_activity();
//
//               }
//               catch(...)
//               {
//
//               }
//
//            }
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
//   void session::defer_initialize_user_presence()
//   {
//
//      userpresence().defer_initialize_user_presence();
//
//   }
//
//   void session::on_request(sp(::create) pcreate)
//   {
//
//      ::axis::session::on_request(pcreate);
//
//   }
//
//   string session::get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
//   {
//
//      string str = ::fontopus::get_cred(papp,strUsername,strPassword,strToken);
//
//      if(str == "ok")
//         return "ok";
//
//      if(!bInteractive)
//         return "failed";
//
//      sp(::fontopus::simple_ui) pui;
//
//      string strRequestUrl(strRequestUrlParam);
//
//      if(strRequestUrl.is_empty())
//      {
//
//         string strIgnitionServer = file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt");
//
//         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
//         {
//
//            strRequestUrl = "https://" + strIgnitionServer + "/";
//
//         }
//         else
//         {
//
//            strRequestUrl = "https://account.ca2.cc/";
//
//         }
//
//      }
//
//      pui = canew(::fontopus::simple_ui(papp,strRequestUrl));
//
//      pui->m_login.m_peditUser->SetWindowText(strUsername);
//
//      pui->m_login.m_ppassword->SetWindowText("");
//
//      string strResult = pui->get_cred(rect,strUsername,strPassword,strToken,strTitle);
//
//      pui->DestroyWindow();
//
//      return strResult;
//
//   }


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





::user::interaction * session::get_focus_guie()
{

#if defined (METROWIN)

   oswindow window = GetFocus();

   if(window == NULL)
      return NULL;

   return GetFocus()->m_pui;

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
   pwnd = m_puiFocus;
   if(pwnd != NULL)
   {
      if(get_active_guie() != NULL
         && (get_active_guie() == pwnd
         || get_active_guie()->is_descendant(pwnd)))
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





::user::interaction * session::get_active_guie()
{

#if defined (METROWIN)

   return GetFocus()->m_pui;

#elif defined(WINDOWSEX) || defined(LINUX)

   ::user::interaction * pwnd = System.get_active_guie();

   if(pwnd != NULL)
   {

      return pwnd;

   }

   if(m_puiActive != NULL)
   {

      pwnd = ((::user::interaction *)m_puiActive->m_pvoidUserInteraction);

      if(pwnd != NULL)
      {

         return pwnd;

      }

   }

   return NULL;

#else

   return System.get_active_guie();

#endif


}


void session::frame_pre_translate_message(signal_details * pobj)
{

   try
   {

      ::user::interaction * pui = NULL;

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

   string str = ::axis::session::get_cred(papp,strRequestUrlParam,rect,strUsername, strPassword, strToken, strTitle, bInteractive);

   if(str == "ok")
      return "ok";

   if(!bInteractive)
      return "failed";

   sp(::fontopus::simple_ui) pui;

   string strRequestUrl(strRequestUrlParam);

   if(strRequestUrl.is_empty())
   {

      string strIgnitionServer = file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt");

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



} // namespace base
































