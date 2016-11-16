#include "framework.h"


namespace draw2d_cairo
{


#ifdef WINDOWS


   class font_fam_c2
   {
   public:

      ENUMLOGFONTW lf;

   };

   int CALLBACK EnumFamCallBack(
      _In_ ENUMLOGFONTW   *lpelf,
      _In_ NEWTEXTMETRICW *lpntm,
      _In_ DWORD         FontType,
      _In_ LPARAM        lParam
   )
   {

      font_fam_c2 * pc2 = (font_fam_c2 *)lParam;

      pc2->lf = *lpelf;

      return TRUE;

   }


#endif


   font::font(::aura::application * papp) :
   ::object(papp)
   {

      m_pfont = NULL;
      m_ft = NULL;
      m_pface = NULL;
      ZERO(m_keyDone);

   }


   font::~font()
   {

      destroy();

   }


   bool font::destroy()
   {

      synch_lock ml(cairo_mutex());
//      if(m_pfont != NULL)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_scaled_font_destroy(m_pfont);
//
//         m_pfont = NULL;
//
//      }

//      if(m_pface != NULL)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_font_face_destroy(m_pface);
//
//         m_pface = NULL;
//
//      }

//      if(m_ft != NULL)
      {

         //FT_Done_Face (m_ft);

  //       m_ft = NULL;

      }

      return true;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::font::dump(dumpcontext);

   }


   void * font::get_os_data() const
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::draw2d::font::e_cs font::calc_cs(::draw2d::graphics * pgraphics)
   {

#ifndef WINDOWS

      return ::draw2d::font::cs_default;

#else

      font_fam_c2 c2;

      HDC hdc = ::CreateCompatibleDC(NULL);

      wstring wstr = m_strFontFamilyName;

      if (!EnumFontFamiliesW(hdc, wstr, (FONTENUMPROCW)&EnumFamCallBack, (LPARAM)&c2))
      {

         ::DeleteDC(hdc);

         return ::draw2d::font::cs_default;

      }

      ::DeleteDC(hdc);


      return ::draw2d::wingdi_get_cs(c2.lf.elfLogFont.lfCharSet);

#endif

   }



} // namespace draw2d_cairo





