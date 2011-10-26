#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_TESSERACT toolbar : public simple_toolbar
   {
   public:


      HBRUSH m_hbrushBackgroundOriginal;


      toolbar(::ca::application * papp);
      virtual ~toolbar();


      void ChangeBackgroundColor(COLORREF cr);
      void ChangeBackgroundBrush(HBRUSH hbrush);
      void SetOriginalBackground();


   };


} // namespace whiteboard