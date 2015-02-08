#pragma once


namespace linux
{

   class CLASS_DECL_AXIS file_path :
      virtual public ::file::file_path
   {
   public:
      file_path(::aura::application *  papp);
      virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
   };

   class CLASS_DECL_AXIS dir :
      virtual public ::file::dir::system
   {
   public:




      string      m_strca2;


      dir(::aura::application *  papp);


      using ::file::dir::system::path;
      virtual class ::file::file_path & path();
      virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);

      virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = NULL);
      virtual bool  ls_pattern(::aura::application *  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
      virtual bool  ls(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
      virtual bool  rls_pattern(::aura::application *  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
      virtual bool  rls(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
      virtual bool  rls_dir(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
      virtual bool  ls_dir(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      virtual bool  ls_file(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);


      virtual bool initialize();
   protected:
      class file_path     m_path;
      string         m_strTimeFolder;
      string         m_strNetSeedFolder;
   };

} // namespace linux


