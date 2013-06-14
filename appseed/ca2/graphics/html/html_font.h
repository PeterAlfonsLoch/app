#pragma once


namespace html
{

   class CLASS_DECL_ca2 font :
      virtual public ::ca2::ca2
   {
   public:
      
      
      index               m_iIndex;
      string            m_strFamily;
      string            m_strWeight;
      string            m_strSize;
      string            m_strTextDecoration;
      ::ca2::font_sp     m_font;


      font();
      font(const class font & font);
      
      bool create(sp(::ca2::application) papp);

      bool operator == (const font & font);
   };


} // namespace html