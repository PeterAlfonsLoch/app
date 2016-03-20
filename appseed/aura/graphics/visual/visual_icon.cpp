#include "framework.h"
#include "visual_icon.h"

#ifdef WINDOWSEX

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

struct MYICON_INFO
{
   int     nWidth;
   int     nHeight;
   int     nBitsPerPixel;
};

MYICON_INFO MyGetIconInfo(HICON hIcon);

#endif

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

      on_update_icon();

   }

#ifdef WINDOWS

   icon::icon(HICON hicon)
   {

      m_picon        = hicon;
      m_bAutoDelete  = true;

      on_update_icon();

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

      on_update_icon();

      return m_picon != NULL;

#else

      m_strAppTrayIcon = strApp;

      return true;

#endif

   }

   void icon::on_update_icon()
   {
      
      if (m_picon == NULL)
      {

         m_size.cx = 0;
         m_size.cy = 0;

         return;

      }

#ifdef WINDOWSEX

      auto info = MyGetIconInfo((HICON) m_picon);

      m_size.cx = info.nWidth;
      m_size.cy = info.nHeight;

#else

      // building icon not supported (size > 512 :-)
      if (m_size.cx <= 0 || m_size.cy <= 0 || m_size.cx >= 512 || m_size.cy >= 512)
      {

         m_size.cx = 22;
         m_size.cy = 22;

      }

#endif

   }


   ::size icon::get_size()
   {

      return m_size;

   }


} // namespace visual


#ifdef WINDOWSEX

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

MYICON_INFO MyGetIconInfo(HICON hIcon)
{
   MYICON_INFO myinfo;
   ZeroMemory(&myinfo, sizeof(myinfo));

   ICONINFO info;
   ZeroMemory(&info, sizeof(info));

   BOOL bRes = FALSE;

   bRes = GetIconInfo(hIcon, &info);
   if (!bRes)
      return myinfo;

   BITMAP bmp;
   ZeroMemory(&bmp, sizeof(bmp));

   if (info.hbmColor)
   {
      const int nWrittenBytes = GetObject(info.hbmColor, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight;
         myinfo.nBitsPerPixel = bmp.bmBitsPixel;
      }
   }
   else if (info.hbmMask)
   {
      // Icon has no color plane, image data stored in mask
      const int nWrittenBytes = GetObject(info.hbmMask, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight / 2;
         myinfo.nBitsPerPixel = 1;
      }
   }

   if (info.hbmColor)
      DeleteObject(info.hbmColor);
   if (info.hbmMask)
      DeleteObject(info.hbmMask);

   return myinfo;
}



#endif