#pragma once


namespace zip
{


   class CLASS_DECL_ca2 Util
   {
   public:


      Util();
      virtual ~Util();


      void ls(sp(::ca::application) papp, const char * lpszFileName, bool bRecursive, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null(), e_extract eextract = extract_first);
      void ls_dir(sp(::ca::application) papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null());
      bool extract(sp(::ca::application) papp, const char * lpszFileName, const char * lpszExtractFileName);
      bool extract_all(const char * pszDir, sp(::ca::file) pfile);
      bool exists(sp(::ca::application) papp, const char * pszPath);
      bool IsUnzipable(sp(::ca::application) papp, const char * lpszFileName);
      bool HasSubFolder(sp(::ca::application) papp, const char * lpszFileName);


   };


} // namespace zip



