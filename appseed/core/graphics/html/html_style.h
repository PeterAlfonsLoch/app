#pragma once



namespace html
{

   class elemental;

   /*enum edisplay
   {
      display_block,
      display_inline,
   };*/

   class CLASS_DECL_CORE style :
      virtual public element
   {
   public:

      
      e_tag                m_etag;
      string               m_strName;
      string               m_strSubClass;

      property_set         m_propertyset;

      e_display            m_edisplay;


      style(sp(::aura::application) papp);
      style(const style & style);

      void initialize(e_tag etag);

      //static e_display display_name_to_id(const var & varDisplay, e_tag e_tag);
      //static e_display tag_to_display(e_tag e_tag);

      style & operator = (const style & style);
      
      const char * parse(data * pdata, const char * psz);

      static COLORREF parse_color(const char * psz);
      static float parse_dimension(const char * psz);
      static bool parse_border_width(const char * psz, float & f);
      static bool parse_border_color(const char * psz, COLORREF & cr);

      bool get_dimension(bool bParent, id idName, const string & strSubClass, data * pdata, elemental * pelemental, float & f);
      bool get_surround_box(id idName, const string & strSubClass, data * pdata, elemental * pelemental, box & box);
      bool get_border_box(id idName, const string & strSubClass, data * pdata, elemental * pelemental, border & border);
      bool get_border_color(id idName, const string & strSubClass, data * pdata, elemental * pelemental, border & border);
      // todo
      // bool get_border_style(id idName, const string & strSubClass, const data * pdata, elemental * pelemental, COLORREF & cr) const;
      bool get_color(id idName, const string & strSubClass, data * pdata, elemental * pelemental, COLORREF & cr);
      bool get_text(id idName, const string & strSubClass, data * pdata, elemental * pelemental, string & str);
      bool get_alpha(const string & strSubClass, data * pdata, elemental * pelemental, double & d);

      bool matches(e_tag etag, const string & strClass, const string & strSubClass, id idName);
      bool matches_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f);
      bool matches_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, COLORREF & cr);

      
   };

} // namespace html