#include "framework.h"


namespace user
{


   bool static_control::create(sp(::user::interaction) pParentWnd, id id)
   {

      return ::user::control::create(pParentWnd, id);

   }


   static_control::~static_control()
   {

      DestroyWindow();

   }


   // Derived class is responsible for implementing all of these handlers
   //   for owner/self draw controls
#ifdef WINDOWSEX


   void static_control::DrawItem(LPDRAWITEMSTRUCT)
   {

      ASSERT(FALSE);

   }


#endif


   bool static_control::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,
      LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
   // trans   if (message != WM_DRAWITEM)
         // return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);

      ASSERT(pResult == ::null());       // no return value expected
#ifdef WINDOWSEX
      UNUSED(pResult); // unused in release builds
      DrawItem((LPDRAWITEMSTRUCT)lParam);
#endif
      return TRUE;
   }


   static_control::static_control(sp(::ca::application) papp) :
      ca(papp)
   {
      
      m_etype = type_text;

   }


   void static_control::set_icon(::visual::icon * picon)
   {
      
      if(picon == ::null())
         return;

      m_etype = type_icon;

      m_picon = picon;

   }


   ::visual::icon * static_control::get_icon()
   {

      return m_etype == type_icon ? m_picon : ::null();

   }


   HENHMETAFILE static_control::SetEnhMetaFile(HENHMETAFILE hMetaFile)
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);

      return ::null();

   }


   HENHMETAFILE static_control::GetEnhMetaFile()
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);

      return ::null();

   }


   void static_control::set_bitmap(::ca::bitmap * pbitmap)
   {

      
      if(pbitmap == ::null())
         return;

      m_etype = type_icon;

      m_pbitmap = pbitmap;


   }


   ::ca::bitmap * static_control::get_bitmap()
   {

      return m_etype == type_bitmap ? m_pbitmap : ::null();

   }


   void static_control::set_cursor(::visual::cursor * pcursor)
   {

      if(pcursor == ::null())
         return;

      m_etype = type_cursor;

      m_pcursor = pcursor;

   }


   ::visual::cursor *  static_control::get_cursor()
   {

      return m_etype == type_cursor ? m_pcursor : ::null();

   }

   ::user::static_control::e_type static_control::get_type()
   {
      
      return m_etype;

   }


} // namespace user







