#pragma once


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_AXIS data :
      virtual public ::data::data
   {
   public:

      data(sp(::base::application) papp);


      // optional if ls_dir is implemented
      virtual bool has_subdir(const char * pszPath);
      virtual bool ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle, int64_array * piSize, bool_array * pbaDir);
      virtual bool is_dir(const char * pszPath);
      virtual void root_ones(stringa & straPath, stringa & straTitle);
      virtual void get_ascendants_path(const char * pszPath, stringa & stra);
      virtual void get_ascendants_name(const char * lpcsz, stringa & straParam);
      virtual string eat_end_level(const char * pszPath, int32_t iCount);


      virtual bool tree_show_subdir(const char * pszPath);


      virtual string file_name(const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_exists(const char * pszPath);
      virtual var file_length(const char * pszPath);


      virtual bool file_move(const char * pszDst, const char * pszSrc);

      virtual ::file::buffer_sp get_file(var varFile, UINT nOpenFlags);


      virtual bool fast_has_subdir(const char * pszPath);

      virtual sp(data) path_data(const char * psz);
      virtual sp(data) node_path_data(const char * psz);


      virtual bool is_link(const char * psz);

      virtual bool is_zero_latency(const char * psz);


   };



} // namespace fs




