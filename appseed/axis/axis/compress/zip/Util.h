#pragma once


namespace zip
{


   class CLASS_DECL_AXIS Util
   {
   public:


      Util();
      virtual ~Util();


      bool ls(::aura::application * papp, const char * lpszFileName, bool bRecursive, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
      bool ls_dir(::aura::application * papp, const char * lpcsz, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL);
      bool extract(::aura::application * papp, const char * lpszFileName, const char * lpszExtractFileName);
      bool extract_all(::aura::application * papp,const char * pszDir,var varFile,stringa * pstraFilter = NULL,bool_array * pbaBeginsFilterEat = NULL);
      bool exists(::aura::application * papp, const char * pszPath);
      bool IsUnzipable(::aura::application * papp, const char * lpszFileName);
      bool HasSubFolder(::aura::application * papp, const char * lpszFileName);


   };


} // namespace zip



