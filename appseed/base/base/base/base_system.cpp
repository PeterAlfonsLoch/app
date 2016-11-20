//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"

#include "base/node/node.h"


#ifdef WINDOWSEX


#include "base/os/windows/windows_system_interaction_impl.h"


#elif defined(LINUX)

#define pointer x11_pointer
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#undef pointer

int xrr_GetScreenSize(int& width, int& height)
{

 		int num_sizes;
 		Rotation original_rotation;

 		Display *dpy = XOpenDisplay(NULL);
 		Window root = RootWindow(dpy, 0);
 		XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
 		//
 		//     GET CURRENT RESOLUTION AND FREQUENCY
 		//
 		XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
 		short original_rate = XRRConfigCurrentRate(conf);
 		SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);

  		width = xrrs[original_size_id].width;
  		height = xrrs[original_size_id].height;

 		XCloseDisplay(dpy);
		return 0;    //Return a value that can be used for error checking.
}

#endif


namespace base
{


   system::system(::aura::application * papp):
      ::aura::system(this, NULL),
      ::axis::system(this)
   {

      g_pszCooperativeLevel = "base";

#ifdef WINDOWSEX

      m_psystemwindow = NULL;

#endif


#if defined(METROWIN) || defined(APPLE_IOS) || defined(VSNORD)

      m_possystemwindow = new os_system_window();

#endif



      set_app(this);

      m_pbasesystem     = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(object)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_paxissystem;

      }


      __node_base_factory_exchange(this);

      m_bSystemSynchronizedCursor = true;

      m_bSystemSynchronizedScreen = true;

      ::draw2d::dib::static_initialize();

//      draw2d_factory_exchange();


      m_pschemaLayeredFrame = canew(::user::schema_layered_frame(this));


   }


   //void system::construct(const char * pszAppId)
   //{

   //   ::base::application::construct(pszAppId);

   //}


   system::~system()
   {

   }



   int32_t system::exit_application()
   {

      m_pschemaLayeredFrame.release();

#ifdef WINDOWSEX

      try
      {

         ::aura::del(m_psystemwindow);

      }
      catch (...)
      {

         m_iReturnCode = -2;

      }


#endif
      axis::system::exit_application();




#ifdef MACOS
      ns_app_close();
#endif

      return m_iReturnCode;

   }


   ::aura::session * system::on_create_session()
   {

      return new ::base::session(this);

   }




   bool system::defer_create_system_frame_window()
   {


#ifdef WINDOWSEX

      if(m_psystemwindow != NULL)
         return true;

      m_psystemwindow = new system_interaction_impl(this);

#endif



#ifdef WINDOWSEX

      dappy(string(typeid(*this).name()) + " : Going to ::axis::system::m_spwindow->create_window_ex : " + ::str::from(m_iReturnCode));

      if(!m_psystemwindow->create_window_ex(0,NULL,NULL,0,null_rect(),NULL,"::axis::system::interaction_impl::no_twf"))
      {

         dappy(string(typeid(*this).name()) + " : ::axis::system::m_spwindow->create_window_ex failure : " + ::str::from(m_iReturnCode));

         return false;

      }

#endif

      return true;

   }




   index system::get_ui_wkspace(::user::interaction * pui)
   {

      index iMainWkspace = 0;

#ifdef WINDOWSEX

      HMONITOR hwkspacePrimary = GetUiMonitorHandle(pui->get_handle());

      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         if(m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


#endif

      return iMainWkspace;

   }





   void system::set_active_guie(::user::interaction * pui)
   {

#if defined(METROWIN)

      if(pui == NULL)
      {

         ::WinSetActiveWindow(NULL);

      }
      else
      {

         ::WinSetActiveWindow(pui->get_wnd()->get_safe_handle());

      }
#else
      if (pui == NULL)
      {

         ::SetActiveWindow(NULL);

      }
      else
      {

         ::SetActiveWindow(pui->get_wnd()->get_safe_handle());

      }
#endif
      return;

//#else
//
//      synch_lock sl(&m_uiptraFrame);
//
//      if(m_uiptraFrame.find(pui) > 0)
//      {
//
//         m_uiptraFrame.remove(pui);
//
//         m_uiptraFrame.insert_at(0,pui);
//
//      }
//
//      return pui;
//
//#endif

   }


   void system::set_focus_guie(::user::interaction * pui)
   {

      if(pui == NULL)
      {

#ifdef METROWIN

         ::WinSetFocus(NULL);
#else
         ::SetFocus(NULL);
#endif

         return;

      }


#ifdef METROWIN

      ::WinSetFocus(pui->get_safe_handle());

#else

      ::SetFocus(pui->get_safe_handle());

#endif

      if(pui->get_wnd() != NULL)
      {

         pui->SetFocus();

      }

      return;

   }

   ::count system::get_monitor_count()
   {

   #ifdef LINUX

		int heads = 0;

      xdisplay  d;

      if(!d.open(NULL))
      {

         return 1;

      }

      int dummy1, dummy2;

 		if (XineramaQueryExtension(d, &dummy1, &dummy2))
		{

         if(XineramaIsActive(d))
         {

				XineramaScreenInfo *p=XineramaQueryScreens(d, &heads);

				XFree(p);

			}

		}

		return MAX(1, heads);

#else

      return ::axis::system::get_monitor_count();

#endif


   }


   bool system::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

#ifdef METROWIN

      get_window_rect(m_posdata->m_pwindow,lprect);

      return true;

#elif defined(LINUX)

      xdisplay  d;

      if(!d.open(NULL))
         return false;

      //int iCount = ScreenCount(d.m_pdata->m_pdisplay);
      //Display *d= ScreenCount(d.m_pdata->m_pdisplay);

      bool success=false;

		int dummy1, dummy2;

		if (XineramaQueryExtension(d, &dummy1, &dummy2))
		{

         if(XineramaIsActive(d))
         {

				int heads=0;

				XineramaScreenInfo *p=XineramaQueryScreens(d, &heads);

				if(iMonitor >= 0 && iMonitor < heads)
				{

               lprect->left = p[iMonitor].x_org;
               lprect->top = p[iMonitor].y_org;
               lprect->right = lprect->left + p[iMonitor].width;
               lprect->bottom = lprect->top + p[iMonitor].height;
//      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
//      lprect->top = 0;
//      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

//					for (int x=0; x<heads; ++x)
//						cout << "Head " << x+1 << " of " << heads << ": " <<
//							p[x].width << "x" << p[x].height << " at " <<
//							p[x].x_org << "," << p[x].y_org << endl;
					success=true;
				}

				XFree(p);

			}

		}

      if(success)
      {

         return true;

      }

      int iCount;

      XRRScreenSize * psize = XRRSizes(d.m_pdata->m_pdisplay, 0, &iCount);

      lprect->left = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
      lprect->top = 0;
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

      return true;

#else

      return ::axis::system::get_monitor_rect(iMonitor, lprect);

#endif

   }


   bool system::get_wkspace_rect(index iWkspace,LPRECT lprect)
   {

//#ifdef LINUX
//
//      xdisplay  d;
//
//      if(!d.open(NULL))
//         return false;
//
//      lprect->left = 0;
//      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
//      lprect->top = 0;
//      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
//
//      return true;
//
//#else

      return ::axis::system::get_wkspace_rect(iWkspace, lprect);

//#endif

   }


   ::user::interaction_impl * system::impl_from_handle(void * pdata)
   {

      return oswindow_get((oswindow) pdata);

   }

   ::user::interaction * system::ui_from_handle(void * pdata)
   {

      ::user::interaction_impl * pimpl = impl_from_handle(pdata);

      if (pimpl == NULL)
      {

         return NULL;

      }

      return pimpl->m_pui;

   }

} // namespace base












