#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_CUBE toolbar : public simple_toolbar
   {
   

   public:
      toolbar(::ca::application * papp);
      virtual ~toolbar();

      void ChangeBackgroundColor(COLORREF cr);
      void ChangeBackgroundBrush(HBRUSH hbrush);
      void SetOriginalBackground();


   protected:
      HBRUSH m_hbrushBackgroundOriginal;
      ()
   };


} // namespace whiteboard