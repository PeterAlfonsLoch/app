#pragma once


typedef string_map < COLORREF > string_to_colorref;


namespace html
{


   typedef string_to_colorref CNamedColors;


   class CLASS_DECL_CORE html :
      public ::base_departament
   {
   public:


      


      COLORREF                   m_clrInvalid;   // an invalid color
      uint16_t                   m_percentMax;   // maximum allowable percentage value
      CNamedColors               m_namedColors;   // collection of named colors
      LiteHTMLEntityResolver     m_entityresolver;


      html(base_application * papp);
      virtual ~html();

      virtual void construct(sp(base_application) papp);


      virtual bool initialize();

      string special_chars(const char * psz);
      string entities(const char * psz);
      int32_t resolve_entity(const char * lpszEntity, string & strChar);


      e_tag tag_name_to_id(id idTag);
      e_display display_name_to_id(const var & varDisplay, e_tag e_tag);
      e_display tag_to_display(e_tag etag);
      id concat(id id1, id id2);

   };


} // namespace html



