#pragma once


namespace fs
{


   // fs::interface - file system interface


   class CLASS_DECL_AXIS link:
      virtual public ::fs::native,
      virtual public ::file::listing
   {
   public:


      
      ::file::path      m_strTitle;


      link(::aura::application * papp);



      virtual ::file::listing & ls(::file::listing & listing) override;


      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath);
      virtual bool is_dir(const ::file::path & pszPath);
      virtual void root_ones(::file::patha & patha,stringa & straTitle);
      //virtual void get_ascendants_path(const char * pszPath,stringa & stra);
      //virtual void get_ascendants_name(const char * lpcsz,stringa & straParam);
      //virtual string eat_end_level(const char * pszPath,int32_t iCount);


      //virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1,const char * psz2);

      //virtual bool file().exists(const char * pszPath);

      //virtual bool file_move(const char * pszDst,const char * pszSrc);

      //virtual ::file::buffer_sp get_file(var varFile,UINT nOpenFlags);

      virtual void fill_os_user();

      virtual void fill_os_user_desktop();

      virtual bool tree_show_subdir(const ::file::path & pszPath);


   };



} // namespace fs







