#pragma once

namespace zip
{

   class CLASS_DECL_ca Util :
      virtual public ::radix::object
   {
   public:
      void ls(const char * lpszFileName, bool bRecursive, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
      void ls_dir(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      bool extract(const char * lpszFileName, const char * lpszExtractFileName);
      bool exists(const char * pszPath);
      bool IsUnzipable(const char * lpszFileName);
      bool HasSubFolder(const char * lpszFileName);
      Util(::ca::application * papp);
      virtual ~Util();

   };

} // namespace zip

