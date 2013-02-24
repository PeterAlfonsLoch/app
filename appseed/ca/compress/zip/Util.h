#pragma once


namespace zip
{


   class CLASS_DECL_ca Util
   {
   public:


      Util();
      virtual ~Util();


      void ls(::ca::application * papp, const char * lpszFileName, bool bRecursive, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < int64_t, int64_t > * piaSize = NULL, e_extract eextract = extract_first);
      void ls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      bool extract(::ca::application * papp, const char * lpszFileName, const char * lpszExtractFileName);
      bool extract_all(const char * pszDir, ::ca::file * pfile);
      bool exists(::ca::application * papp, const char * pszPath);
      bool IsUnzipable(::ca::application * papp, const char * lpszFileName);
      bool HasSubFolder(::ca::application * papp, const char * lpszFileName);


   };


} // namespace zip



