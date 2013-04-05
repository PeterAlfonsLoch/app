#pragma once


namespace fs
{


   class CLASS_DECL_ca set :
      public ::fs::data
   {
   public:

      spa(data)                                 m_spafsdata;
      string_map < data * >       m_fsdatamap;


      set(::ca::applicationsp papp);
      virtual ~set();

   
      string_map < data * > &     fsmap();
      spa(data) &                               fsa();
      

      virtual data * path_data(const char * psz);
      virtual void root_ones(stringa & stra);
      virtual bool ls(const char * psz, stringa * pstraPath, stringa * pstraTitle);
      virtual bool is_dir(const char * psz);
      virtual string file_name(const char * psz);
      virtual bool file_move(const char * pszDst, const char * pszSrc);
      virtual bool has_subdir(const char * psz);
      virtual void get_ascendants_path(const char * psz, stringa & stra);
      virtual string eat_end_level(const char * psz, int32_t iLevel);
      virtual string dir_path(const char * pszPath1, const char * pszPath2);

   };


} // namespace fs


