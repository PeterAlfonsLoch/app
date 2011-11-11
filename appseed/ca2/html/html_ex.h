#pragma once

namespace html
{
   
   class CLASS_DECL_ca html_ex :
      virtual public ::radix::object
   {
   public:


      typedef ::collection::string_map < COLORREF>   CNamedColors;


      const COLORREF             m_clrInvalid;   // an invalid color
      const unsigned short       m_percentMax;   // maximum allowable percentage value
      CNamedColors               m_namedColors;   // collection of named colors
      LiteHTMLEntityResolver     m_entityresolver;


      html_ex(::ca::application * papp);
      virtual ~html_ex();

      int resolve_entity(const char * lpszEntity, string & strChar);
   };

} // namespace html
