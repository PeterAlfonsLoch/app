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


   
   void static_control::_001OnDraw(::draw2d::graphics * pdc)
   {

      pdc->set_text_color(ARGB(255, 0, 0, 0));

      pdc->TextOut(0, 0, get_window_text());

   }


   bool static_control::OnChildNotify(::message::base * pbase)
   {
      
      if (pbase->m_uiMessage != WM_DRAWITEM)
          return ::user::interaction::OnChildNotify(pbase);

#ifdef WINDOWSEX
      
//      DrawItem((LPDRAWITEMSTRUCT)pbase->m_lparam);

#endif

      return true;

   }


   static_control::static_control(sp(base_application) papp) :
      element(papp)
   {

      m_etype = type_text;

   }


   void static_control::set_icon(::visual::icon * picon)
   {

      if(picon == NULL)
         return;

      m_etype = type_icon;

      m_picon = picon;

   }


   ::visual::icon * static_control::get_icon()
   {

      return m_etype == type_icon ? m_picon : NULL;

   }


   HENHMETAFILE static_control::SetEnhMetaFile(HENHMETAFILE hMetaFile)
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);

      return NULL;

   }


   HENHMETAFILE static_control::GetEnhMetaFile()
   {

      //ASSERT(IsWindow());

      //return (HENHMETAFILE)send_message( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);

      return NULL;

   }


   void static_control::set_bitmap(::draw2d::bitmap * pbitmap)
   {


      if(pbitmap == NULL)
         return;

      m_etype = type_icon;

      m_pbitmap = pbitmap;


   }


   ::draw2d::bitmap * static_control::get_bitmap()
   {

      return m_etype == type_bitmap ? m_pbitmap : NULL;

   }


   void static_control::set_cursor(::visual::cursor * pcursor)
   {

      if(pcursor == NULL)
         return;

      m_etype = type_cursor;

      m_pcursor = pcursor;

   }


   ::visual::cursor *  static_control::get_cursor()
   {

      return m_etype == type_cursor ? m_pcursor : NULL;

   }

   ::user::static_control::e_type static_control::get_type()
   {

      return m_etype;

   }


} // namespace user







