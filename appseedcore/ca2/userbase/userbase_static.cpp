#include "StdAfx.h"

namespace userbase
{

   BOOL base_static::create(const char * lpszText, DWORD dwStyle,
         const RECT& rect, ::user::interaction* pParentWnd, UINT nID)
   {
      ::user::interaction* pWnd = this;
      return pWnd->create("STATIC", lpszText, dwStyle, rect, pParentWnd, nID);
   }

   base_static::~base_static()
   {
      DestroyWindow();
   }

   // Derived class is responsible for implementing all of these handlers
   //   for owner/self draw controls
   void base_static::DrawItem(LPDRAWITEMSTRUCT)
   {
      ASSERT(FALSE);
   }

   BOOL base_static::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,
      LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
   // trans   if (message != WM_DRAWITEM)
         // return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);

      ASSERT(pResult == NULL);       // no return value expected
      UNUSED(pResult); // unused in release builds
      DrawItem((LPDRAWITEMSTRUCT)lParam);
      return TRUE;
   }

   base_static::base_static(::ca::application * papp) :
      ca(papp)
      { }
   HICON base_static::SetIcon(HICON hIcon)
      { ASSERT(IsWindow()); return (HICON)SendMessage( STM_SETICON, (WPARAM)hIcon, 0L); }
   HICON base_static::GetIcon() 
      { ASSERT(IsWindow()); return (HICON)SendMessage( STM_GETICON, 0, 0L); }
   HENHMETAFILE base_static::SetEnhMetaFile(HENHMETAFILE hMetaFile)
      { ASSERT(IsWindow()); return (HENHMETAFILE)SendMessage( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile); }
   HENHMETAFILE base_static::GetEnhMetaFile() 
      { ASSERT(IsWindow()); return (HENHMETAFILE)SendMessage( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L); }
   HBITMAP base_static::from(HBITMAP hBitmap)
      { ASSERT(IsWindow()); return (HBITMAP)SendMessage( STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap); }
   HBITMAP base_static::GetBitmap() 
      { ASSERT(IsWindow()); return (HBITMAP)SendMessage( STM_GETIMAGE, IMAGE_BITMAP, 0L); }
   HCURSOR base_static::SetCursor(HCURSOR hCursor)
      { ASSERT(IsWindow()); return (HCURSOR)SendMessage( STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor); }
   HCURSOR base_static::GetCursor()
      { ASSERT(IsWindow()); return (HCURSOR)SendMessage( STM_GETIMAGE, IMAGE_CURSOR, 0L); }



} // namespace userbase