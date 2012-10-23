#pragma once



namespace html
{

   class elemental;

   /*enum edisplay
   {
      display_block,
      display_inline,
   };*/

   class CLASS_DECL_ca2 style
   {
   public:

      
      string               m_strTag;
      string               m_strName;
      string               m_strSubClass;

      gen::property_set    m_propertyset;

      //edisplay             m_edisplay;


      style();
      style(const style & style);

      style & operator = (const style & style);
      
      const char * parse(data * pdata, const char * psz);

      static COLORREF parse_color(const char * psz);
      static float parse_dimension(const char * psz);
      static bool parse_border_width(const char * psz, float & f);
      static bool parse_border_color(const char * psz, COLORREF & cr);

      bool get_dimension(bool bParent, const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, float & f) const;
      bool get_surround_box(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, box & box) const;
      bool get_border_box(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, border & border) const;
      bool get_border_color(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, border & border) const;
      // todo
      // bool get_border_style(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, COLORREF & cr) const;
      bool get_color(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, COLORREF & cr) const;
      bool get_text(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, string & str) const;
      bool get_alpha(const char * pszSubClass, const data * pdata, const elemental * pelemental, double & d) const;

      bool matches(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const;
      bool matches_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f) const;
      bool matches_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr) const;

      
   };

} // namespace html