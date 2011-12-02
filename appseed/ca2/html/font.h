#pragma once


namespace html
{

   class CLASS_DECL_ca font
   {
   public:
      
      
      int               m_iIndex;
      string            m_strFamily;
      string            m_strWeight;
      string            m_strSize;
      string            m_strTextDecoration;
      ::ax::font_sp     m_font;


      font();
      font(const class font & font);
      
      bool create(::ax::application * papp);

      bool operator == (const font & font);
   };


} // namespace html