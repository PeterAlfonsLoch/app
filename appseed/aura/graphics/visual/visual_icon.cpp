#include "framework.h"
#include "visual_icon.h"


namespace visual
{


   icon::icon()
   {

      m_picon        = NULL;
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

         if(m_picon != NULL)
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



