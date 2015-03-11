#pragma once


// ifs - implementation of file system interface - file.veriwell.net

class CLASS_DECL_AXIS ifs :
   virtual public ::fs::data
{
public:


   string         m_strRoot;
   bool           m_bInitialized;
   string         m_strServer;

   class CLASS_DECL_AXIS dir
   {
   public:
      uint32_t          m_uiDirTimeout;
      uint32_t          m_uiFileTimeout;
      uint32_t          m_uiLsTimeout;
      ::file::patha     m_pathaFile;
      ::file::patha     m_pathaFolder;
      ::file::patha     m_pathaFileName;
      ::file::patha     m_pathaFolderName;
   };

   filepathmap(dir)     m_map;

   //file_path_map < uint32_t >    m_mapdirTimeout;
   //file_path_map < uint32_t >    m_mapfileTimeout;
   //file_path_map < uint32_t >    m_maplsTimeout;
   //filepathmap(::file::patha)    m_mapdirFile;
   //filepathmap(::file::patha)    m_mapdirFolder;
   //filepathmap(::file::patha)    m_mapdirFileName;
   //filepathmap(::file::patha)    m_mapdirFolderName;
   //filepathmap(int64_array)      m_mapdirFileSize;
   //filepathmap(int64_array)      m_mapdirFolderSize; // by now, always store item count?
   //filepathmap(bool_array)       m_mapdirFileDir;
   //filepathmap(bool_array)       m_mapdirFolderDir; // by now, always store item count?


   ifs(::aura::application * papp, const char * pszRoot);

   
   virtual bool has_subdir(const ::file::path & pszPath);
   virtual bool fast_has_subdir(const ::file::path  & pszPath);
   virtual bool ls(const ::file::path & pszDir,::file::patha * ppatha,::file::patha * ppathaName,bool bSize = false);
   virtual bool is_dir(const ::file::path & pszPath);
   virtual void root_ones(::file::patha & patha,stringa & straTitle);

   //virtual string file_name(const char * pszPath);
   //virtual string dir_path(const char * psz1, const char * psz2);

   virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

   virtual ::file::buffer_sp get_file(const ::file::path & path,UINT nOpenFlags,fesp * pfesp);

   virtual bool file_exists(const ::file::path & pszPath);
   virtual var file_length(const ::file::path & pszPath);

   virtual void defer_initialize();

   virtual bool is_zero_latency(const ::file::path & psz);

};

