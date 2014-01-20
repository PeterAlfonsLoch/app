#pragma once



namespace html
{

   class CLASS_DECL_CORE style_sheet :
      virtual public element
   {
   public:


      smart_pointer_array < style > m_stylea;
      

      style_sheet();


      void parse(data * pdoc, const char * psz);

      style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName);
      const style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const;

      style * rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f);
      const style * rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f) const;

      style * rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr);
      const style * rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr) const;

      style * greater(style * pstyle1, style * pstyle2) const;
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2) const;
      bool greater(const style * & pstyleRet, index & iRet, var & varRet, const style * pstyle1, index i1, const var & var1, const style * pstyle2, index i2, const var & var2) const;


   };

} // namespace html