#pragma once


namespace fs
{


   class CLASS_DECL_BASE set :
      public ::fs::data
   {
   public:


      spa(data)                     m_spafsdata;
      strsp(data)                   m_fsdatamap;


      set(sp(base_application) papp);
      virtual ~set();


      strsp(data) &                 fsmap();
      spa(data) &                   fsa();


      virtual sp(data) path_data(const char * psz);
      virtual sp(data) node_path_data(const char * psz);
      virtual void root_ones(stringa & stra);
      virtual bool ls(const char * psz, stringa * pstraPath, stringa * pstraTitle, int64_array * piaSize);
      virtual bool is_dir(const char * psz);
      virtual string file_name(const char * psz);
      virtual bool file_move(const char * pszDst, const char * pszSrc);
      virtual bool has_subdir(const char * psz);
      virtual bool tree_show_subdir(const char * psz);
      virtual bool fast_has_subdir(const char * psz);
      virtual void get_ascendants_path(const char * psz, stringa & stra);
      virtual string eat_end_level(const char * psz, int32_t iLevel);
      virtual string dir_path(const char * pszPath1, const char * pszPath2);

   };


} // namespace fs


