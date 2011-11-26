#pragma once



namespace html
{

   class CLASS_DECL_ca style_sheet_array :
      public array_ptr_alloc < style_sheet >
   {
   public:


      style_sheet_array();


      style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName);
      const style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const;



   };

} // namespace html