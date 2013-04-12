#include "framework.h"


namespace visual
{


   icon::icon()
   {

      m_picon        = ::null();
      m_bAutoDelete  = true;

   }

   icon::icon(void * picon)
   {

      m_picon        = picon;
      m_bAutoDelete  = true;

   }

#ifdef WINDOWS

   icon::icon(HICON hicon)
   {

      m_picon        = hicon;
      m_bAutoDelete  = true;

   }

#endif

   icon::~icon()
   {

      if(m_bAutoDelete)
      {

         if(m_picon != ::null())
         {

#ifdef WINDOWSEX

            ::DestroyIcon((HICON) m_picon);

#else

            throw todo(get_app());

#endif


         }

      }

   }

   icon::operator void *()
   {

      return m_picon;

   }

#ifdef WINDOWS

   icon::operator HICON()
   {

      return (HICON) m_picon;

   }

#endif

}



