#pragma once


namespace html
{

   class font
   {
   public:
      int      m_iIndex;
      string   m_strFamily;
      string   m_strWeight;
      string   m_strSize;
      
      bool create();
      CFont    m_font;
   };


} // namespace html