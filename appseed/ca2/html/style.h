#pragma once



namespace html
{

   class elemental;

   /*enum edisplay
   {
      display_block,
      display_inline,
   };*/

   class CLASS_DECL_ca style
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

      bool get_color(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, COLORREF & cr) const;
      bool get_text(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, string & str) const;
      bool get_alpha(const char * pszSubClass, const data * pdata, const elemental * pelemental, double & d) const;

      bool matches(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const;

      
   };

} // namespace html