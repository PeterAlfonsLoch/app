#include "framework.h"


DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}

__thread DWORD g_dwLastError = 0;

CLASS_DECL_c DWORD GetLastError()
{

   return g_dwLastError;

}

CLASS_DECL_c DWORD SetLastError(DWORD dw)
{

   DWORD dwLastError = g_dwLastError;

   g_dwLastError = dw;

   return dwLastError;

}


CLASS_DECL_c bool _istlead(int32_t ch)
{

   return false;

}


void Sleep(DWORD dwMillis)
{
   timespec t;
   t.tv_sec = dwMillis / 1000;
   t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   nanosleep(&t, NULL);
}





cairo_keep::cairo_keep(cairo_t * pdc, bool bSave)
{

   m_pdc = pdc;

   m_bSave = false;

   if(bSave)
      save();


}


cairo_keep::~cairo_keep()
{

   if(m_bSave)
   {

      restore();

   }

}



void cairo_keep::save()
{

   if(m_bSave)
      return;

   cairo_save(m_pdc);

   m_bSave = true;

}


void cairo_keep::restore()
{

   if(!m_bSave)
      return;

   cairo_restore(m_pdc);

   m_bSave = false;

}


void cairo_keep::pulse()
{

   save();

   restore();

}

