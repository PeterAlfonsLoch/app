#include "StdAfx.h"

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

#if !core_level_1 && !core_level_2
      m_monitorinfoaDesk = m_monitorinfoa;
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


   bool application::final_handle_exception(::ax::exception & e)
   {
      base_exception * pbe = dynamic_cast < se_exception * > (&e);
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
#if !core_level_1 && !core_level_2
      m_monitorinfoa.remove_all();
      ::EnumDisplayMonitors(NULL, NULL, &application::monitor_enum_proc,
         (LPARAM) ( dynamic_cast < cube1::application * > (this)));
#endif
   }

#if !core_level_1 && !core_level_2
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

#if !core_level_1 && !core_level_2
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
#if !core_level_1
      return m_monitorinfoa.get_size();
#else
      return 1;
#endif
   }

   bool application::get_monitor_rect(index i, LPRECT lprect)
   {
      if(i < 0 || i >= get_monitor_count())
         return false;
#if !core_level_1
      *lprect = m_monitorinfoa[i].rcMonitor;
#else
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


} //namespace cube1
