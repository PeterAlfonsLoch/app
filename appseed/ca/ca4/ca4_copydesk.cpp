#include "StdAfx.h"
#include <shlobj.h>

copydesk::copydesk()
{
}

copydesk::~copydesk()
{
}

int copydesk::get_file_count()
{
   if(!m_p->OpenClipboard())
      return 0;
   HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
   int iCount = 0;
   if(hdrop != NULL)
   {
      iCount = ::DragQueryFile(hdrop , 0xFFFFFFFF, NULL, 0);
   }
   ::CloseClipboard();
   return iCount;
}


void copydesk::get_filea(stringa & stra)
{
   int iCount = get_file_count();
   if(iCount <= 0)
      return;
   if(!m_p->OpenClipboard())
      return;
   HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
   string str;
   for(int i = 0; i < iCount; i++)
   {
      UINT uiLen = ::DragQueryFileW(hdrop, i, NULL, 0);
      wchar_t * lpwsz = (wchar_t *) malloc(sizeof(wchar_t) * (uiLen + 1));
      ::DragQueryFileW(hdrop, i, lpwsz, uiLen + 1);
      stra.add(gen::international::unicode_to_utf8(lpwsz));
      free(lpwsz);
   }
   ::CloseClipboard();
}

void copydesk::set_filea(stringa & stra)
{
   
   ASSERT(m_p->IsWindow());
   
   strsize iLen = 0;

   for(int i = 0; i < stra.get_size(); i++)
   {
      iLen += gen::international::utf8_to_unicode_count(stra[i]) + 1;
   }


   HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
   LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglbCopy);
   pDropFiles->pFiles = sizeof(DROPFILES);
   pDropFiles->pt.x = pDropFiles->pt.y = 0;
   pDropFiles->fNC = TRUE;
   pDropFiles->fWide = TRUE; // ANSI charset

   ASSERT(m_p->IsWindow());
   LPTSTR lptstrCopy = (char *) pDropFiles;
   lptstrCopy += pDropFiles->pFiles;
   wchar_t * lpwstrCopy = (wchar_t *) lptstrCopy;
   for(int i = 0; i < stra.get_size(); i++)
   {
      ASSERT(m_p->IsWindow());
      gen::international::utf8_to_unicode(lpwstrCopy, gen::international::utf8_to_unicode_count(stra[i]) + 1, stra[i]);
      ASSERT(m_p->IsWindow());
      lpwstrCopy += (stra[i].get_length() + 1);
   }
   ASSERT(m_p->IsWindow());
   *lpwstrCopy = '\0';    // null character
   ASSERT(m_p->IsWindow());
   ::GlobalUnlock(hglbCopy);
   ASSERT(m_p->IsWindow());
   if(!m_p->OpenClipboard())
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
   if(!m_p->CreateEx(0, System.RegisterWndClass(0), NULL, 0, rect(0, 0, 0, 0), NULL, id()))
      return false;

   return true;
}

void copydesk::set_plain_text(const char * psz)
{
   ASSERT(m_p->IsWindow());
//   int iLen = 0;

   string str;
   str = gen::international::utf8_to_unicode(psz);



   ASSERT(m_p->IsWindow());
   if(!m_p->OpenClipboard())
   {
      return;
   }
   EmptyClipboard();


   count iCount = gen::international::utf8_to_unicode_count(str) + 1;
   HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iCount * sizeof(WCHAR));
   wchar_t * lpwstrCopy  = (wchar_t *) ::GlobalLock(hglbCopy);
   gen::international::utf8_to_unicode(lpwstrCopy, iCount, str);
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
      if(!m_p->OpenClipboard())
         return "";
      HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
      string str(gen::international::unicode_to_utf8((const wchar_t *) GlobalLock(hglb)));
      GlobalUnlock(hglb);
      VERIFY(::CloseClipboard());
      return str;
   }
   else if (IsClipboardFormatAvailable(CF_TEXT))
   {
      if(!m_p->OpenClipboard())
         return "";
      HGLOBAL hglb = GetClipboardData(CF_TEXT);
      string str((char *) GlobalLock(hglb));
      GlobalUnlock(hglb);
      VERIFY(::CloseClipboard());
      return str;
   }
   else
   {
      return "";
   }
}

bool copydesk::desk_to_dib(::ca::dib * pdib)
{
   if(!m_p->OpenClipboard())
      return false;
   HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
   HDC hdc = ::CreateCompatibleDC(NULL);
   ::ca::graphics_sp g(get_app());
   g->attach(hdc);
   //::ca::graphics * pgraphics = Application.graphics_from_os_data(hdc);
   g->SelectObject(hbitmap);
   BITMAP bm;
   ::GetObjectA(hbitmap, sizeof(bm), &bm);
   if(!pdib->create(bm.bmWidth, bm.bmHeight))
      return false;
   pdib->get_graphics()->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, g, 0, 0, SRCCOPY);
   ::DeleteDC(hdc);
   ::CloseClipboard();
   return true;
}
