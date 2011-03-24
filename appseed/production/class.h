#pragma once

namespace production
{
   class view;
} // namespace production


class CLASS_DECL_CA2_PRODUCTION production_class : public simple_thread 
{
public:

   mutex       m_mutexStatus;
   stringa     m_straStatus;
   bool        m_bLoop;
   int         m_iLoop;
   int         m_iLoopCount;
   string      m_strSubversionRevision;
   stringa     m_straCompress;
   mutex       m_mutexCompress;
   string      m_strBuildTook;
   string      m_strSpc;
   string      m_strSignTool;

   production_class(::ca::application * papp);
   virtual ~production_class();
   enum e_version
   {
      version_backup,
      version_stage,
   };


   class release :
      virtual public thread
   {
   public:
      release(production_class * pproduction);

      string m_strRelease;
      production_class * m_pproduction;
      bool initialize_instance();
      int run();
   };

   class compress_thread :
      virtual public thread
   {
   public:
      compress_thread(production_class * pproduction);

      manual_reset_event m_evFinished;
      production_class * m_pproduction;
      int run();
   };

   void start(e_version eversion);
   void start_loop(e_version eversion, int iLoopCount);
   void step();

   void add_status(const char * psz);
   void change_status(const char * psz);

   int m_iRelease;

   e_version m_eversion;
   
   class time m_timeStart;
   class time m_timeEnd;


   stringa   m_straStageDirAcceptedFileExtensions;
   
   
   int m_iStep;

   virtual int run();
   ::view * m_pview;
   bool m_bFinished;
   DWORD m_dwStartTick;
   DWORD m_dwEndTick;
   stringa m_straCC;
   stringa m_straBB;
   string m_strBuild;
   string m_strFormatBuild;

   string m_strTag;
   string m_strTagPath;

   string m_strStatus;
   string m_strBase;
   int m_iBaseLen;
   stringa m_straFiles;

   bool m_bClean;
   bool m_bBuild;
   bool get_file_list(const char * pszBase, const char * pszDir,string &  strRemote, stringa & stra, stringa & straTitle, stringa & straRelative, bool bFileSet = false);
// bool ftp_put_dir(CFtpConnection & ftpconn, const char * pszBase, const char * pszDir, int iMode);

   virtual void compress();
   virtual bool compress_next();

   virtual void generate_appmatter_spa();
   virtual void release();
   virtual bool release_npca2(const char * pszPlatform);
   virtual bool release_iexca2(const char * pszPlatform);

   bool sync_source(const char * psz, const char * pszRevision);
   bool commit_for_new_build_and_new_release();


   void compress(const char * lpszRelative);
   string m_strVrel;
   string m_strCCVotagus;
   string m_strCCVrel;
   string m_strCCVrelNew;
   string   m_strIndexMd5;
   
   void OnUpdateRelease();

};