#pragma once


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_AXIS native :
      virtual public ::fs::data
   {
   public:


      native(::aura::application * papp);
      virtual ~native();


      virtual ::file::listing & ls(::file::listing & listing);


      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath);
      virtual bool is_dir(const ::file::path & pszPath);
      virtual ::file::listing & root_ones(::file::listing & listing);
      //virtual void get_ascendants_path(const ::file::path & pszPath,::file::patha & stra);
      //virtual void get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam);
      //virtual string eat_end_level(const char * pszPath, int32_t iCount);


      //virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_exists(const ::file::path & pszPath);

      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

      virtual ::file::buffer_sp get_file(const ::file::path & path,UINT nOpenFlags,cres * pfesp);

   };



} // namespace fs
