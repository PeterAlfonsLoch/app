#include "framework.h"
#include "visual_icon.h"


namespace visual
{


   icon::icon(::aura::application * papp) :
      ::object(papp)
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


   bool icon::load_app_tray_icon(string strApp)
   {

#ifdef WINDOWSEX

      string strPath = System.dir().appmatter(strApp, "main/icon.ico");

      int cx = GetSystemMetrics(SM_CXSMICON);
      int cy = GetSystemMetrics(SM_CYSMICON);

      HICON hIcon = (HICON) ::LoadImageW(NULL, wstring(strPath), IMAGE_ICON, cx, cy, LR_LOADFROMFILE);

      m_picon = hIcon;

      return m_picon != NULL;

#else

      m_strAppTrayIcon = strApp;

      return true;

#endif

   }


} // namespace visual



