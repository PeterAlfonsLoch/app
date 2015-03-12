#pragma once


namespace zip
{


   class CLASS_DECL_AXIS Util
   {
   public:


      Util();
      virtual ~Util();


      bool ls(::aura::application * papp, ::file::listing & listing);
      bool extract(::aura::application * papp, const char * lpszFileName, const char * lpszExtractFileName);
      bool extract_all(::aura::application * papp,const char * pszDir,var varFile,stringa * pstraFilter = NULL,bool_array * pbaBeginsFilterEat = NULL);
      bool exists(::aura::application * papp, const char * pszPath);
      bool IsUnzipable(::aura::application * papp, const char * lpszFileName);
      bool HasSubFolder(::aura::application * papp, const char * lpszFileName);


   };


} // namespace zip



