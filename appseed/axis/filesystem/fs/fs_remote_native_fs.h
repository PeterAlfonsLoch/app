#pragma once


namespace fs
{


   // fs::interface - file system interface access to remote file system through fontopus proxy


   class CLASS_DECL_AXIS remote_native :
      virtual public ::fs::data
   {
   public:


      string                              m_strRoot;
      bool                                m_bInitialized;


      file_path_map < uint32_t >          m_mapdirTimeout;
      file_path_map < uint32_t >          m_mapfileTimeout;


      remote_native(::aura::application * papp, const char * pszRoot);
      virtual ~remote_native();

   
      virtual bool has_subdir(const ::file::path & pszPath);
      virtual bool fast_has_subdir(const ::file::path & pszPath);
      virtual bool ls(const ::file::path & pszDir,::file::patha * ppatha,::file::patha * ppathaName,int64_array * piaSize,bool_array * pbaDir);
      virtual bool is_dir(const ::file::path & pszPath);
      virtual void root_ones(::file::patha & patha,stringa & straTitle);

      //virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

      virtual ::file::buffer_sp get_file(const ::file::path & path,UINT nOpenFlags,fesp * pfesp);

      virtual bool file_exists(const ::file::path & pszPath);

      virtual void defer_initialize();

      virtual bool is_zero_latency(const ::file::path & psz);

   };


} // namespace fs



