#pragma once



namespace install
{

   class CLASS_DECL_BASE install :
      virtual public ::base_departament
   {
   public:

      install(sp(base_application) papp);
      virtual ~install();


      int_bool is_file_ok(const char * path1, const char * pszTemplate);

   };


} // namespace spa