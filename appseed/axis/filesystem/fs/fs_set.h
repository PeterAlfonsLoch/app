#pragma once


namespace fs
{


   class CLASS_DECL_AXIS set :
      public ::fs::data
   {
   public:


      spa(data)                     m_spafsdata;
      strsp(data)                   m_fsdatamap;


      set(::aura::application * papp);
      virtual ~set();


      strsp(data) &                 fsmap();
      spa(data) &                   fsa();


      virtual sp(data) path_data(const ::file::path & psz);
      virtual sp(data) node_path_data(const ::file::path & psz);
      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual ::file::listing & ls(::file::listing & listing);
      virtual bool is_dir(const ::file::path & psz);
      //virtual string file_name(const char * psz);
      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);
      virtual bool has_subdir(const ::file::path & psz);
      virtual bool tree_show_subdir(const ::file::path & psz);
      virtual bool fast_has_subdir(const ::file::path & psz);
      virtual bool is_link(const ::file::path & psz);
      //virtual void get_ascendants_path(const ::file::path & psz,::file::patha & stra);
      //virtual string eat_end_level(const char * psz, int32_t iLevel);
      //virtual string dir_path(const char * pszPath1, const char * pszPath2);

      virtual bool is_zero_latency(const ::file::path & psz);

   };


} // namespace fs


