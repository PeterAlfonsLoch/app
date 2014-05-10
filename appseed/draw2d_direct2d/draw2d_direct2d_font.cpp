#include "framework.h"


namespace draw2d_direct2d
{


   font::font(::base::application * papp) :
      element(papp)
   {

   }


   font::~font()
   { 


   }


   void font::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

   }




   IDWriteTextFormat * font::get_os_font(::draw2d_direct2d::graphics * pgraphics) const
   {

      if(m_pformat == NULL || !m_bUpdated)
      {

         if(m_pformat != NULL)
         {
            ((font *)  this)->destroy();
         }


         IDWriteFactory * pfactory = TlsGetWriteFactory();


         DWRITE_FONT_STYLE style;

         if(m_bItalic)
            style = DWRITE_FONT_STYLE_ITALIC;
         else
            style = DWRITE_FONT_STYLE_NORMAL;

         DWRITE_FONT_STRETCH stretch;

         stretch = DWRITE_FONT_STRETCH_NORMAL;

         HRESULT hr = pfactory->CreateTextFormat(
            //wstring(lplf->lfFaceName),
            wstring(m_strFontFamilyName),
            NULL,
            //(DWRITE_FONT_WEIGHT) lplf->lfWeight,
            (DWRITE_FONT_WEIGHT) m_iFontWeight ,
            style,
            stretch,
            (float) ((m_eunitFontSize == ::draw2d::unit_point ? point_dpi((float) m_dFontSize) : dpiy((float) m_dFontSize)) * pgraphics->m_dFontFactor),
            L"",
            &((font *)  this)->m_pformat);


         if(FAILED(hr) || m_pformat == NULL)
            return false;

      }


      if(m_pformat != NULL)
      {
         ((font *) this)->m_bUpdated = true;
      }

      return (IDWriteTextFormat *) m_pformat.Get();

   }


   bool font::destroy()
   {

      if(m_pformat == NULL)
         return true;


      m_pformat = nullptr;


      return true;

   }


} // namespace draw2d_direct2d