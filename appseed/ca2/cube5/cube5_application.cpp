#include "framework.h"


namespace cube5 // cube5 + ca8
{


   application::application()
   {

      m_phtml = NULL;

      m_puserex = NULL;

   }


   application::~application()
   {

   }


   bool application::initialize1()
   {

      m_puserex = new ::userex::userex();

      m_puserex->construct(this);

      if(!m_puserex->initialize1())
         return false;

      m_dwAlive = ::get_tick_count();

      if(!cubebase::application::initialize1())
         return false;

      m_dwAlive = ::get_tick_count();

      enum_display_monitors();


      rect rect;
      get_monitor_rect(0, &rect);
      for(int32_t i = 1; i < get_monitor_count(); i++)
      {
         class rect rectMonitor;
         get_monitor_rect(i, &rectMonitor);
         rect.unite(rect, &rectMonitor);
      }

#ifdef WINDOWSEX

      m_monitorinfoaDesk = m_monitorinfoa;

#else

      //throw todo(get_app());

#endif

      /*if(m_monitorinfoa.get_size() == 1)
      {
         MONITORINFO mi = m_monitorinfoaDesk.last_element();
         m_monitorinfoaDesk[0].rcMonitor.right = mi.rcMonitor.right /2;
         m_monitorinfoaDesk.add(mi);
         m_monitorinfoaDesk.last_element().rcMonitor.left = mi.rcMonitor.right / 2;

      }*/

      /*if(get_twf() != NULL)
      {
         get_twf()->Update(rect);
      }*/


      return true;

   }

   bool application::initialize2()
   {

      if(!::cubebase::application::initialize2())
         return false;

      if(!m_puserex->initialize2())
         return false;

      return true;

   }

   bool application::initialize()
   {

      m_dwAlive = ::get_tick_count();

      if(is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }

      if(!::cubebase::application::initialize())
         return false;

      m_puinteraction = new ::uinteraction::uinteraction();

      m_puinteraction->construct(this);

      if(!m_puinteraction->initialize())
         return false;

      m_puserbase = new ::userbase::userbase();

      m_puserbase->construct(this);

      if(!m_puserbase->initialize())
         return false;

      m_pfilemanager = new ::filemanager::filemanager();

      ::radix::application::m_pfilemanager = m_pfilemanager;

      m_pfilemanager->construct(this);

      if(!m_pfilemanager->initialize())
         return false;

      m_pmail = new ::mail::mail();

      m_pmail->construct(this);

      if(!m_pmail->initialize())
         return false;

      m_dwAlive = ::get_tick_count();

      return true;

   }

   string application::message_box(const char * pszMatter, gen::property_set & propertyset)
   {
      class message_box box(this);
      box.show(pszMatter, &propertyset);
      return box.m_strResponse;
   }

   int32_t application::simple_message_box(::user::interaction * pwndOwner, const char * pszMessage, UINT fuStyle)
   {
      class message_box box(this);

      gen::property_set propertyset;
      propertyset["message"] = pszMessage;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      try
      {
         if(!box.show(strMatter, &propertyset))
         {
            string strMessage = pszMessage;
            strMessage.replace("<br>", "\r\n");
            return MessageBox(pwndOwner == NULL ? (oswindow) ::ca::null() : pwndOwner->get_handle(), strMessage, m_strAppName, fuStyle);
         }
      }
      catch(...)
      {
         string strMessage = pszMessage;
         strMessage.replace("<br>", "\r\n");
         return MessageBox(pwndOwner == NULL ? (oswindow) ::ca::null() : pwndOwner->get_handle(), strMessage, m_strAppName, fuStyle);
      }
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int32_t application::simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(puiOwner);

      class message_box box(this);

      gen::property_set propertyset;
      propertyset["message"] = pszMessage;
      propertyset["simple_message_box_timeout_ms"] = iTimeout;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      box.show(strMatter, &propertyset);
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int32_t application::track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }

   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      return user().keyboard().load_layout(pszPath, bUser);
   }


   bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {
      int64_t i64Size;
      if(!get_fs_size(i64Size, pszPath, bPending))
      {
         strSize.Empty();
         return false;
      }
      if(i64Size > 1024 * 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0 * 1024.0);
         strSize.Format("%0.2f GB", d);
      }
      else if(i64Size > 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0);
         strSize.Format("%0.1f MB", d);
      }
      else if(i64Size > 1024)
      {
         double d = (double) i64Size / (1024.0);
         strSize.Format("%0.0f KB", d);
      }
      else if(i64Size > 0)
      {
         strSize.Format("1 KB");
      }
      else
      {
         strSize.Format("0 KB");
      }
      if(bPending)
      {
         strSize = "~" + strSize;
      }
      return true;
   }

   bool application::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
   {
      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void application::data_on_after_change(gen::signal_object * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2_fontopus_votagus")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(savings().m_eresourceflagsShouldSave);
         }
      }
   }


   bool application::final_handle_exception(::ca::exception & e)
   {
      base_exception * pbe = dynamic_cast < standard_exception * > (&e);
      if(pbe != NULL)
      {
         TRACE(pbe->stack_trace());
      }
      return cubebase::application::final_handle_exception(e);
   }

// 23 = Carlinhos Gustavinho Cecynzinho Lundgrenzinho
// monitors all -- que olhões

   void application::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL, NULL, &application::monitor_enum_proc, (LPARAM) ( dynamic_cast < ::cube5::application * > (this)));

#else

      // todo
//      m_monitorinfoa.remove_all();


#endif

   }

#ifdef WINDOWSEX
   BOOL CALLBACK application::monitor_enum_proc(
     HMONITOR hmonitor,
     HDC hdcMonitor,
     LPRECT lprcMonitor,
     LPARAM dwData)
   {
      cube5::application * papp = (cube5::application *) dwData;
      papp->monitor_enum(hmonitor, hdcMonitor, lprcMonitor);
      return TRUE; // to enumerate all
   }
#endif

#ifdef WINDOWSEX
   void application::monitor_enum(
     HMONITOR hmonitor,
     HDC hdcMonitor,
     LPRECT lprcMonitor)
   {
      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(lprcMonitor);
      m_monitorinfoa.set_size(m_monitorinfoa.get_size() + 1);
      memset(&m_monitorinfoa.last_element(), 0, sizeof(MONITORINFO));
      m_monitorinfoa.last_element().cbSize = sizeof(MONITORINFO);
      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last_element());
      MONITORINFO mi = m_monitorinfoa.last_element();

      TRACE0("application::monitor_enum\n");
      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);
   }
#endif

   count application::get_monitor_count()
   {
#ifdef WINDOWSEX
      return m_monitorinfoa.get_size();
#else
      // throw todo(get_app());
      return 1;
#endif
   }

   bool application::get_monitor_rect(index i, LPRECT lprect)
   {
      if(i < 0 || i >= get_monitor_count())
         return false;
#ifdef WINDOWSEX
      *lprect = m_monitorinfoa[i].rcMonitor;
#elif defined(METROWIN)

      return System.get_window_rect(lprect);

#elif defined(LINUX)

      Display * d=XOpenDisplay(NULL);


      //throw todo(get_app());
      lprect->left = 0;
      lprect->top = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d));
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d));


      XCloseDisplay(d);

#elif defined(MACOS)


      throw todo(get_app());




#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


   count application::get_desk_monitor_count()
   {
#ifdef WINDOWSEX
      return m_monitorinfoaDesk.get_size();
#else
      throw todo(get_app());
      return 1;
#endif
   }

   bool application::get_desk_monitor_rect(index i, LPRECT lprect)
   {
      if(i < 0 || i >= get_desk_monitor_count())
         return false;
#ifdef WINDOWSEX
      *lprect = m_monitorinfoaDesk[i].rcMonitor;
#elif defined(METROWIN)
      throw todo(get_app());
#elif defined(LINUX)
      throw todo(get_app());
#elif defined(MACOS)
      throw todo(get_app());
#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


} //namespace cube5 + ca8
