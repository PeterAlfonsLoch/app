#include "framework.h"


namespace userbase
{


   bool base_static::create(::user::interaction* pParentWnd, id id)
   {

      return ::user::control::create(pParentWnd, id);

   }


   base_static::~base_static()
   {

      DestroyWindow();

   }


   // Derived class is responsible for implementing all of these handlers
   //   for owner/self draw controls
#ifdef WINDOWSEX


   void base_static::DrawItem(LPDRAWITEMSTRUCT)
   {

      ASSERT(FALSE);

   }


#endif


   bool base_static::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,
      LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
   // trans   if (message != WM_DRAWITEM)
         // return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);

      ASSERT(pResult == NULL);       // no return value expected
#ifdef WINDOWSEX
      UNUSED(pResult); // unused in release builds
      DrawItem((LPDRAWITEMSTRUCT)lParam);
#endif
      return TRUE;
   }


   base_static::base_static(::ca::application * papp) :
      ca(papp)
   {

   }


   HICON base_static::SetIcon(HICON hIcon)
   {

      //ASSERT(IsWindow());

      //return (HICON)send_message( STM_SETICON, (WPARAM)hIcon, 0L);

      return NULL;

   }


   HICON base_static::GetIcon()
   {

      //ASSERT(IsWindow());

      //return (HICON)send_message( STM_GETICON, 0, 0L);

      return NULL;

   }


   HENHMETAFILE base_static::SetEnhMetaFile(HENHMETAFILE hMetaFile)
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);

      return NULL;

   }


   HENHMETAFILE base_static::GetEnhMetaFile()
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);

      return NULL;

   }


   HBITMAP base_static::from(HBITMAP hBitmap)
   {

      //ASSERT(IsWindow());

      //return (HBITMAP)send_message( STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

      return NULL;

   }


   HBITMAP base_static::GetBitmap()
   {

      //ASSERT(IsWindow());

      //return (HBITMAP)send_message( STM_GETIMAGE, IMAGE_BITMAP, 0L);

      return NULL;

   }


   HCURSOR base_static::SetCursor(HCURSOR hCursor)
   {

      //ASSERT(IsWindow());

      //return (HCURSOR)send_message( STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);

      return NULL;

   }


   HCURSOR base_static::GetCursor()
   {

      //ASSERT(IsWindow());

      //return (HCURSOR)send_message( STM_GETIMAGE, IMAGE_CURSOR, 0L);

      return NULL;

   }


} // namespace userbase







