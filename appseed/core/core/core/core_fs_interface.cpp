#include "framework.h"


namespace core
{

   void fs_interface::ls_dir(const char * pszPath, stringa & straName)
   {
      UNREFERENCED_PARAMETER(pszPath);
      UNREFERENCED_PARAMETER(straName);
   }
   
   void fs_interface::ls_file(const char * pszPath, stringa & straName)
   {
      UNREFERENCED_PARAMETER(pszPath);
      UNREFERENCED_PARAMETER(straName);
   }
   
   void fs_interface::query_info(string & straInfo)
   {
      query_default_info(straInfo);
   }

   void fs_interface::query_default_info(string & straInfo)
   {
      query_info(straInfo);
   }
   
   bool fs_interface::get_info(const char * pszPath, const char * pszInfo, var & varInfo)
   {
      UNREFERENCED_PARAMETER(pszPath);
      UNREFERENCED_PARAMETER(pszInfo);
      UNREFERENCED_PARAMETER(varInfo);
      return false;
   }

} // namespace core
