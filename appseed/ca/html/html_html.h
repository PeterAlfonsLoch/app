#pragma once


typedef string_map < COLORREF > string_to_colorref;


namespace html
{


   typedef string_to_colorref CNamedColors;


   class CLASS_DECL_ca html :
      public ::ca::section
   {
   public:


      


      COLORREF                   m_clrInvalid;   // an invalid color
      uint16_t                   m_percentMax;   // maximum allowable percentage value
      CNamedColors               m_namedColors;   // collection of named colors
      LiteHTMLEntityResolver     m_entityresolver;


      html();
      virtual ~html();

      virtual void construct(::ca::applicationsp papp);

      string special_chars(const char * psz);
      string entities(const char * psz);
      int32_t resolve_entity(const char * lpszEntity, string & strChar);

   };


} // namespace html



