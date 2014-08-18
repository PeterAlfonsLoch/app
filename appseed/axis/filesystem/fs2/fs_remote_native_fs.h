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


      string_map < uint32_t >   m_mapdirTimeout;
      string_map < uint32_t >   m_mapfileTimeout;


      remote_native(sp(::axis::application) papp, const char * pszRoot);
      virtual ~remote_native();

   
      virtual bool has_subdir(const char * pszPath);
      virtual bool fast_has_subdir(const char * pszPath);
      virtual bool ls(const char * pszDir,stringa * pstraPath,stringa * pstraTitle,int64_array * piaSize,bool_array * pbaDir);
      virtual bool is_dir(const char * pszPath);
      virtual void root_ones(stringa & straPath, stringa & straTitle);

      virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_move(const char * pszDst, const char * pszSrc);

      virtual ::file::buffer_sp get_file(var varFile, UINT nOpenFlags);

      virtual bool file_exists(const char * pszPath);

      virtual void defer_initialize();

      virtual bool is_zero_latency(const char * psz);

   };


} // namespace fs



