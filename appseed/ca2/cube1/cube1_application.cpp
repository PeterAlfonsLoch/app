#include "framework.h"

namespace cube1
{

   application::application()
   {
      m_pkeyboardfocus = NULL;

   }

   application::~application()
   {
   }

   bool application::initialize1()
   {

      m_dwAlive = ::GetTickCount();

      if(!ca8::application::initialize1())
         return true;


      enum_display_monitors();


      rect rect;
      get_monitor_rect(0, &rect);
      for(int i = 1; i < get_monitor_count(); i++)
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

   bool application::initialize()
   {

      m_dwAlive = ::GetTickCount();

      if(!ca8::application::initialize())
         return false;
      if(!filemanager::application::initialize())
         return false;
      if(!calculator::application::initialize())
         return false;

      return true;
   }


   bool application::final_handle_exception(::ca::exception & e)
   {
      base_exception * pbe = dynamic_cast < standard_exception * > (&e);
      if(pbe != NULL)
      {
         TRACE(pbe->stack_trace());
      }
      return ca8::application::final_handle_exception(e);
   }

// 23 = Carlinhos Gustavinho Cecynzinho Lundgrenzinho
// monitors all -- que olhões

   void application::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL, NULL, &application::monitor_enum_proc,
         (LPARAM) ( dynamic_cast < cube1::application * > (this)));

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
      cube1::application * papp = (cube1::application *) dwData;
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
#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


} //namespace cube1



