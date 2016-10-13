//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"

#include "base/node/node.h"


#ifdef WINDOWSEX


#include "base/os/windows/windows_system_interaction_impl.h"


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

      m_posdata = new os_data();

#endif


      m_ptwf            = NULL;

      //m_psimpleui       = NULL;

//#if defined(METROWIN) || defined(APPLE_IOS) || defined(VSNORD)
//
//      m_posdata         = new os_data();
//
//#endif

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



   int32_t system::exit_instance()
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
      axis::system::exit_instance();




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



   ::user::window_draw * system::get_twf()
   {

      return m_ptwf;

   }

   bool system::initialize_twf()
   {

      if(m_ptwf != NULL)
         return true;

      sp(::user::window_draw) pwindowdraw = alloc(System.type_info < ::user::window_draw >());

      m_ptwf = pwindowdraw;

      m_ptwf->add_ref();

      if(m_ptwf->twf_start())
         return false;

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


   bool system::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

#ifdef METROWIN

      get_window_rect(m_posdata->m_pwindow,lprect);

      return true;

#elif defined(LINUX)

      xdisplay  d;

      if(!d.open(NULL))
         return false;

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

#ifdef LINUX

      xdisplay  d;

      if(!d.open(NULL))
         return false;

      lprect->left = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
      lprect->top = 0;
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

      return true;

#else

      return ::axis::system::get_wkspace_rect(iWkspace, lprect);

#endif

   }


   ::user::interaction * system::ui_from_handle(void * pdata)
   {

      return oswindow_get((oswindow) pdata);

   }


} // namespace base












