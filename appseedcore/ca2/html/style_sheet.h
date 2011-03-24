#pragma once



namespace html
{

   class CLASS_DECL_ca style_sheet
   {
   public:


      array_ptr_alloc < style > m_stylea;
      

      style_sheet();


      void parse(data * pdoc, const char * psz);

      style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName);

   };

} // namespace html