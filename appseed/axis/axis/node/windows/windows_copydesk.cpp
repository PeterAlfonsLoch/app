//#include "framework.h"
//#include "base/user/user.h"
//#include "windows.h"
//#include <shlobj.h>




namespace windows
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp),
      ::user::interaction(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {
      if(!::OpenClipboard(get_handle()))
         return 0;
      HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      int32_t iCount = 0;
      if(hdrop != NULL)
      {
         iCount = ::DragQueryFile(hdrop , 0xFFFFFFFF, NULL, 0);
      }
      ::CloseClipboard();
      return iCount;
   }


   void copydesk::get_filea(::file::patha & stra)
   {
      int32_t iCount = get_file_count();
      if(iCount <= 0)
         return;
      if(!::OpenClipboard(get_handle()))
         return;
      HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      string str;
      for(int32_t i = 0; i < iCount; i++)
      {
         UINT uiLen = ::DragQueryFileW(hdrop, i, NULL, 0);
         wchar_t * lpwsz = (wchar_t *) malloc(sizeof(wchar_t) * (uiLen + 1));
         ::DragQueryFileW(hdrop, i, lpwsz, uiLen + 1);
         stra.add(::file::path(::str::international::unicode_to_utf8(lpwsz)));
         free(lpwsz);
      }
      ::CloseClipboard();
   }

   void copydesk::set_filea(stringa & stra)
   {

      ASSERT(IsWindow());

      strsize iLen = 0;

      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         iLen += ::str::international::utf8_to_unicode_count(stra[i]) + 1;
      }


      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
      LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglbCopy);
      pDropFiles->pFiles = sizeof(DROPFILES);
      pDropFiles->pt.x = pDropFiles->pt.y = 0;
      pDropFiles->fNC = TRUE;
      pDropFiles->fWide = TRUE; // ANSI charset

      ASSERT(IsWindow());
      LPTSTR lptstrCopy = (char *) pDropFiles;
      lptstrCopy += pDropFiles->pFiles;
      wchar_t * lpwstrCopy = (wchar_t *) lptstrCopy;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         ASSERT(IsWindow());
         ::str::international::utf8_to_unicode(lpwstrCopy, ::str::international::utf8_to_unicode_count(stra[i]) + 1, stra[i]);
         ASSERT(IsWindow());
         lpwstrCopy += (stra[i].get_length() + 1);
      }
      ASSERT(IsWindow());
      *lpwstrCopy = '\0';    // null character
      ASSERT(IsWindow());
      ::GlobalUnlock(hglbCopy);
      ASSERT(IsWindow());
      if(!::OpenClipboard(get_handle()))
      {
         ::GlobalFree(hglbCopy);
         return;
      }
      EmptyClipboard();
      SetClipboardData(CF_HDROP, hglbCopy);
      VERIFY(::CloseClipboard());

   }



   bool copydesk::initialize()
   {
      
      if(!::user::copydesk::initialize())
         return false;

      if(!create_window_ex())
         return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;
      
      bOk = ::user::copydesk::finalize();

      return bOk;

   }

   void copydesk::set_plain_text(const char * psz)
   {
      ASSERT(IsWindow());
   //   int32_t iLen = 0;

      string str(psz);



      ASSERT(IsWindow());
      if(!::OpenClipboard(get_handle()))
      {
         return;
      }
      EmptyClipboard();


      ::count iCount = ::str::international::utf8_to_unicode_count(str) + 1;
      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iCount * sizeof(WCHAR));
      wchar_t * lpwstrCopy  = (wchar_t *) ::GlobalLock(hglbCopy);
      ::str::international::utf8_to_unicode(lpwstrCopy, iCount, str);
      ::GlobalUnlock(hglbCopy);

      HGLOBAL hglbCopy2 = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(CHAR) * (strlen(psz) + 1));
      char * lpstrCopy  = (char *) ::GlobalLock(hglbCopy2);
      strcpy(lpstrCopy, psz);
      ::GlobalUnlock(hglbCopy2);


      SetClipboardData(CF_UNICODETEXT, hglbCopy);
      SetClipboardData(CF_TEXT, hglbCopy2);
      VERIFY(::CloseClipboard());

   }


   string copydesk::get_plain_text()
   {
      if (IsClipboardFormatAvailable(CF_UNICODETEXT))
      {
         if(!::OpenClipboard(get_handle()))
            return "";
         HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
         string str(::str::international::unicode_to_utf8((const wchar_t *) GlobalLock(hglb)));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else if (IsClipboardFormatAvailable(CF_TEXT))
      {
         if(!::OpenClipboard(get_handle()))
            return "";
         HGLOBAL hglb = GetClipboardData(CF_TEXT);
         string str((char *) GlobalLock(hglb));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else if(get_file_count() > 0)
      {
         
         ::file::patha patha;

         get_filea(patha);

         return patha.implode("\r\n");

      }
      else
      {
         return "";
      }
   }

   #undef new

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {
      if(!::OpenClipboard(get_handle()))
         return false;
      bool bOk = false;
      HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
      try
      {
         
         BITMAP bm;

         ZERO(bm);
         
         ::GetObject(hbitmap, sizeof(bm), &bm);

         pdib->create(bm.bmWidth, bm.bmHeight);

         if(pdib->m_size.area() <= 0)
         {
            ::DeleteObject((HGDIOBJ)hbitmap);
            //::DeleteDC(hdc);
            ::CloseClipboard();

            return false;
         }

         HDC hdc = (HDC) pdib->get_graphics()->get_os_data_ex(1);

         HDC hdcMem = ::CreateCompatibleDC(NULL);

         HGDIOBJ hbitmapOld = ::SelectObject(hdcMem,hbitmap);

         ::BitBlt(hdc,0,0,pdib->m_size.cx,pdib->m_size.cy,hdcMem,0,0,SRCCOPY);

         pdib->get_graphics()->release_os_data_ex(1, hdc);

         ::SelectObject(hdcMem,hbitmapOld);

         //bitmap->attach(new Gdiplus::Bitmap(hbitmap, NULL));
         //HDC hdc = ::CreateCompatibleDC(NULL);
         //::draw2d::graphics_sp g(allocer());
         //g->attach(hdc);
         //::draw2d::graphics * pgraphics = Application.graphics_from_os_data(hdc);
         //g->SelectObject(hbitmap);
       //  BITMAP bm;
         //::GetObjectA(hbitmap, sizeof(bm), &bm);
         //if(!pdib->create(bm.bmWidth, bm.bmHeight))
           // return false;
         //::draw2d::graphics_sp g(allocer());
         //g->SelectObject(bitmap);
         //size sz = bitmap->GetBitmapDimension();
         //if(pdib->create(sz))
         //{
           // bOk = pdib->get_graphics()->BitBlt(0, 0, sz.cx, sz.cy, g, 0, 0, SRCCOPY) != FALSE;
         //}
      }
      catch(...)
      {
      }
      ::DeleteObject((HGDIOBJ) hbitmap);
      //::DeleteDC(hdc);
      ::CloseClipboard();
      return bOk;
   }


   bool copydesk::dib_to_desk(::draw2d::dib * pdib)
   {

      ASSERT(IsWindow());

      if(!::OpenClipboard(get_handle()))
      {

         return false;

      }

      EmptyClipboard();

      //   HDC hMemDC;
      DWORD dwWidth,dwHeight;
      BITMAPINFOHEADER bi;
      // HBITMAP hOldBitmap;
      HBITMAP hBitmap;
      void *lpBits;
      HCURSOR hAlphaCursor = NULL;

      dwWidth  = pdib->m_size.cx;  // width of the Bitmap V5 Dib bitmap
      dwHeight = pdib->m_size.cy;  // height of the Bitmap V5 Dib bitmap

      ZeroMemory(&bi,sizeof(BITMAPINFOHEADER));
      bi.biSize           = sizeof(BITMAPINFOHEADER);
      bi.biWidth           = dwWidth;
      bi.biHeight          = - (LONG)dwHeight;
      bi.biPlanes = 1;
      bi.biBitCount = 32;
      bi.biCompression = BI_RGB;
      bi.biSizeImage = pdib->m_iScan * pdib->m_size.cy;
      // The following mask specification specifies a supported 32 BPP
      // alpha format for Windows XP.
      //bi.bV5RedMask   =  0x00FF0000;
      //bi.bV5GreenMask =  0x0000FF00;
      //bi.bV5BlueMask  =  0x000000FF;
      //bi.bV5AlphaMask =  0xFF000000;

      //HDC hdc;
      //hdc = GetDC(NULL);

      // Create the DIB section with an alpha channel.
///      hBitmap = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,(void **)&lpBits,NULL,(DWORD)0);

      //hMemDC = CreateCompatibleDC(hdc);
   //   ReleaseDC(NULL,hdc);

      // Draw something on the DIB section.
      //hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
      //PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
      //SetTextColor(hMemDC,RGB(0,0,0));
      //SetBkMode(hMemDC,TRANSPARENT);
      //TextOut(hMemDC,0,9,"rgba",4);
      //SelectObject(hMemDC,hOldBitmap);
      //DeleteDC(hMemDC);

      // Set the alpha values for each pixel in the cursor so that
      // the complete cursor is semi-transparent.

      //int iStrideDst = dwWidth * sizeof(COLORREF);

      //::draw2d::copy_colorref(pdib->m_size.cx,pdib->m_size.cy,(COLORREF *)lpBits,iStrideDst,pdib->m_pcolorref,pdib->m_iScan);

      HGLOBAL hResult = GlobalAlloc(GMEM_MOVEABLE,sizeof(bi) + pdib->m_iScan * pdib->m_size.cy);
      if(hResult == NULL) return false;

      LPBYTE lp = (LPBYTE) ::GlobalLock(hResult);

      memcpy(lp,&bi,sizeof(bi));
      memcpy(lp + sizeof(bi),pdib->m_pcolorref, pdib->m_iScan * pdib->m_size.cy);
      GlobalUnlock(hResult);

      SetClipboardData(CF_DIB,hResult);


      VERIFY(::CloseClipboard());

      return true;
      
   }

#define new AURA_NEW


} // namespace windows



