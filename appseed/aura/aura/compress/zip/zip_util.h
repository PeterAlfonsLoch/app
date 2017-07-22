#pragma once


namespace zip
{


   class CLASS_DECL_AURA util
   {
   public:


      util();
      virtual ~util();


      bool ls(::aura::application * papp, ::file::listing & listing);
      bool extract(::aura::application * papp, const char * lpszFileName, const char * lpszExtractFileName);
      bool extract_all(::aura::application * papp,const char * pszDir,var varFile,stringa * pstraFilter = NULL,bool_array * pbaBeginsFilterEat = NULL);
      bool exists(::aura::application * papp, const char * pszPath);
      bool is_unzippable(::aura::application * papp, const char * lpszFileName);
      bool has_sub_folder(::aura::application * papp, const char * lpszFileName);


   };


} // namespace zip



