#pragma once


namespace ca2
{

   class CLASS_DECL_ca2 fs_interface
   {
   public:
      virtual void ls_dir(const char * pszPath, stringa & straName);
      virtual void ls_file(const char * pszPath, stringa & straName);
      virtual void query_info(string & straInfo);
      virtual void query_default_info(string & straInfo);
      virtual bool get_info(const char * pszPath, const char * pszInfo, var & varInfo);
   };

} // namespace ca2
