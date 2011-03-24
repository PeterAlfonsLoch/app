#include "StdAfx.h"

namespace netnode
{
   profiler::item::item()
   {
      m_iTotalTime = 0;
      m_iCount = 0;
   }
   void profiler::item::enter(profiler * pprofiler, const char * pszName)
   {
      UNREFERENCED_PARAMETER(pprofiler);
      UNREFERENCED_PARAMETER(pszName);
      {
         __int64 count;
         __int64 freq;
         if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
         && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
         {
            m_iEnterTime = count * 1000 * 1000 / freq;
         }
         else
         {
            m_iEnterTime = ::GetTickCount();
         }
      }
   }
   void profiler::item::leave(profiler * pprofiler, const char * pszName)
   {
      __int64 iLeaveTime;
      {
         __int64 count;
         __int64 freq;
         if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
         && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
         {
            iLeaveTime = count * 1000 * 1000 / freq;
         }
         else
         {
            iLeaveTime = ::GetTickCount();
         }
      }
      m_iTotalTime += iLeaveTime - m_iEnterTime;
      m_iCount++;
      string str;
      str.Format("prof_leave - Total time - %s : %0.3f", pszName, m_iTotalTime / (1000.0, 1000.0));
      pprofiler->dprint(str);
   }

   profiler::scope::scope(profiler * pprofiler, const char * pszName, bool bEnter)
   {
      m_bEntered = false;
      m_bLeft = false;
      m_strName = pszName;
      m_pprofiler = pprofiler;
      if(bEnter)
         enter();
   }
   profiler::scope::~scope()
   {
      if(m_bEntered && !m_bLeft)
      {
         leave();
      }
   }
   void profiler::scope::enter()
   {
      if(m_pprofiler != NULL)
      {
         if(!m_bEntered)
         {
            m_pprofiler->enter(m_strName);
            m_bEntered = true;
            m_bLeft = false;
         }
      }
   }
   void profiler::scope::leave()
   {
      if(m_pprofiler != NULL)
      {
         if(m_bEntered)
         {
            m_pprofiler->leave(m_strName);
            m_bLeft = true;
         }
      }
   }

   void profiler::enter(const char * psz)
   {
      m_map[psz].enter(this, psz);
   }
   void profiler::leave(const char * psz)
   {
      m_map[psz].leave(this, psz);
   }

   void profiler::display()
   {
      POSITION pos = m_map.get_start_position();
      string strName;
      item item;
      while(pos != NULL)
      {
         m_map.get_next_assoc(pos, strName, item);
         dprint("<h3>profile name: " + strName + "</h3>");
         string str;
         str.Format("total time %0.3f<br/>", item.m_iTotalTime / (1000.0 * 1000.0));
         dprint(str);
         if(item.m_iCount > 0)
         {
            str.Format("average time %0.3f<br/>", item.m_iTotalTime / (1000.0 * 1000.0 * item.m_iCount));
            dprint(str);
            str.Format("count %d<br/>", item.m_iCount);
            dprint(str);
         }
         dprint("<br/>");
      }
   }



} // namespace netnode