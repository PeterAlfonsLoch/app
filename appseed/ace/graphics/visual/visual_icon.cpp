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

      m_picon = NULL;
      m_bAutoDelete = true;

   }

   icon::icon(void * picon)
   {

      set_app(::get_thread_app());

      m_picon = picon;
      m_bAutoDelete = true;

      on_update_icon();

   }

#ifdef WINDOWS

   icon::icon(HICON hicon)
   {

      set_app(::get_thread_app());

      m_picon = hicon;
      m_bAutoDelete = true;

      on_update_icon();

   }

#endif

   icon::~icon()
   {

      if (m_bAutoDelete)
      {

         if (m_picon != NULL)
         {

#ifdef WINDOWSEX

            ::DestroyIcon((HICON)m_picon);

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

      return (HICON)m_picon;

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

      auto info = MyGetIconInfo((HICON)m_picon);

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


   ::draw2d::dib * icon::get_dib(int cx, int cy)
   {

      ::draw2d::dib_sp & dib = m_dibmap[size(cx, cy)];

      if (dib.is_set() && dib->area() == size(cx, cy).area())
      {

         return dib;

      }

      dib.alloc(allocer());

      if (dib.is_null())
         return NULL;

      if (!dib->create(cx, cy))
         return NULL;

#ifdef WINDOWSEX

      bool bOk = false;

      HBITMAP hbitmap = NULL;

      HDC hdc = NULL;

      HBITMAP hbitmapOld = NULL;

      try
      {

         BITMAPINFO info;
         COLORREF * pcolorref;

         ZeroMemory(&info, sizeof(BITMAPINFO));

         info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         info.bmiHeader.biWidth = cx;
         info.bmiHeader.biHeight = -cy;
         info.bmiHeader.biPlanes = 1;
         info.bmiHeader.biBitCount = 32;
         info.bmiHeader.biCompression = BI_RGB;
         info.bmiHeader.biSizeImage = cx * cy * 4;

         hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **)&pcolorref, NULL, 0);

         hdc = ::CreateCompatibleDC(NULL);

         hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         ICONINFO ii;
         BITMAPINFO biC;
         BITMAPINFO biM;

         ZERO(biC);
         ZERO(biM);

         if (::GetIconInfo((HICON)m_picon, &ii))
         {

            ::GetObject(ii.hbmColor, sizeof(biC), (LPVOID)&biC);

            ::GetObject(ii.hbmMask, sizeof(biM), (LPVOID)&biM);

         }

         if (!::DrawIconEx(hdc, 0, 0, (HICON)m_picon, cx, cy, 0, NULL, DI_IMAGE | DI_MASK))
         {

            output_debug_string("nok");
         }
         else
         {

            bool bAllZeroAlpha = true;
            bool bTheresUint32 = false;

            int area = cx * cy;

            COLORREF * pc = pcolorref;
            BYTE * pA = &((BYTE *)pcolorref)[3];

            for (int i = 0; i < area; i++)
            {
               if (*pc != 0)
               {
                  bTheresUint32 = true;
               }
               if (*pA != 0)
               {
                  bAllZeroAlpha = false;
                  break;
               }
               pc++;
               pA += 4;
            }

            if (bAllZeroAlpha && bTheresUint32)
            {

               pc = pcolorref;
               pA = &((BYTE *)pcolorref)[3];

               for (int i = 0; i < area; i++)
               {
                  if (*pc != 0)
                  {
                     *pA = 255;
                  }
                  pc++;
                  pA += 4;
               }
            }

            ::SelectObject(hdc, hbitmapOld);

            ::draw2d::copy_colorref(cx, cy, dib->m_pcolorref, dib->m_iScan, pcolorref, cx * sizeof(COLORREF));

         }

      }
      catch (...)
      {

         output_debug_string("!");

      }

      if (hdc != NULL)
      {

         if (hbitmapOld != NULL)
         {

            ::SelectObject(hdc, hbitmapOld);

         }

         ::DeleteDC(hdc);

      }

      if (hbitmap != NULL)
      {

         ::DeleteObject(hbitmap);

      }

#endif

      return dib;


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
