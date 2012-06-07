#pragma once


typedef ::collection::string_map < COLORREF > string_to_colorref;


namespace html
{


   class CLASS_DECL_ca html :
      public ::radix::object
   {
   public:


      string_to_colorref         CNamedColors;


      const COLORREF             m_clrInvalid;   // an invalid color
      const unsigned short       m_percentMax;   // maximum allowable percentage value
      CNamedColors               m_namedColors;   // collection of named colors
      LiteHTMLEntityResolver     m_entityresolver;


      html(::ca::application * papp);
      virtual ~html();

      string special_chars(const char * psz);
      string entities(const char * psz);
      int resolve_entity(const char * lpszEntity, string & strChar);

   };


} // namespace html



