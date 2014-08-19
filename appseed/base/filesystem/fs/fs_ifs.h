#pragma once


// ifs - implementation of file system interface - file.veriwell.net

class CLASS_DECL_BASE ifs :
   virtual public ::fs::data
{
public:


   string         m_strRoot;
   bool           m_bInitialized;
   string         m_strServer;

   string_map < uint32_t >    m_mapdirTimeout;
   string_map < uint32_t >    m_mapfileTimeout;
   string_map < uint32_t >    m_maplsTimeout;
   strsp(stringa)             m_mapdirFile;
   strsp(stringa)             m_mapdirFolder;
   strsp(stringa)             m_mapdirFileName;
   strsp(stringa)             m_mapdirFolderName;
   strsp(int64_array)         m_mapdirFileSize;
   strsp(int64_array)         m_mapdirFolderSize; // by now, always store item count?
   strsp(bool_array)          m_mapdirFileDir;
   strsp(bool_array)          m_mapdirFolderDir; // by now, always store item count?


   ifs(sp(::axis::application) papp, const char * pszRoot);

   
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
   virtual var file_length(const char * pszPath);

   virtual void defer_initialize();

   virtual bool is_zero_latency(const char * psz);

};

