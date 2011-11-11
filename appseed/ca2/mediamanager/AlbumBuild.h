#pragma once

// vmsmus
class mus::microke1;
class KaraokeUtil;
class SoftKaraokeInfo;
class ::mus::midi::sequence;
class Star350File;
class Star350InfoHeader;
class CTune1000Info;
class CXFInfoHeaders;

// vmssqlite
namespace vmssqlite
{
   class Database;
   class ::database::set;
}


class CTimeArray :
   public base_array < class time, class time& >
{
};

namespace mediamanager
{
   class AlbumBuild;
   class AlbumBuildThread;

   class CLASS_DECL_ca AlbumRecord :
      public ::radix::object
   {
   public:
      AlbumRecord(::ca::application * papp);
      static string Prepare(class time & time);
      static void Prepare(string & str, class time & time);
      static string Prepare(const char * lpcsz);
      void GetInsertSql(int iId);
      void GetUpdateSql(int iId, bool bFilePath, bool bFileName);
      void Set(Star350InfoHeader & header);
      void Set(SoftKaraokeInfo & karinfo);
      void Set(CXFInfoHeaders & headers);
      void Set(CTune1000Info & info);
      bool SetStar350File(AlbumBuild & albumbuild, primitive::memory & storage);
      bool SetGenericMidiFile(::mus::midi::sequence & seq);
      bool SetTune1000File(::mus::midi::sequence & seq);
      bool SetXFFile(::mus::midi::sequence & seq);
      bool SetSoftKaraokeFile(::mus::midi::sequence & seq);
      bool FillFileInfo(AlbumBuild & build, const char * lpcsz);
      bool FillFileInfo(AlbumBuild & build, primitive::memory & storage);
      static string GetFileName(const char * lpcsz);


      string     m_wstrFileName;
      string     m_wstrFilePath;
      string     m_wstrTitle;
      string     m_wstrArtist;
      string     m_wstrLastWriteTime;
      class time       m_timeLastWrite;

      primitive::memory m_storage;
      primitive::memory m_storage2;
      primitive::memory m_storageSql;
   };


   class CLASS_DECL_ca AlbumBuild :
      virtual public ::radix::object
   {
      friend class AlbumRecord;
      friend class AlbumBuildWnd;
      friend class MediaManager;
   public:
   public:

      class FileInfo
      {
      public:
         void Reset();
         int_array   m_iaNew;
         int_array   m_iaOld;
         int_array   m_iaAdd;
         int_array   m_iaUpdate;
         int_array   m_iaRemove;
         
         stringa      m_wstraNew; 
         CTimeArray     m_timeaNew; 
         stringa      m_wstraOld; 
         CTimeArray     m_timeaOld;
         stringa      m_wstraAdd;
         CTimeArray     m_timeaAdd;
         stringa      m_wstraUpdate; 
         CTimeArray     m_timeaUpdate;
         stringa      m_wstraRemove;
      };

      static const string m_wstrBuildAlbumExtensions;
      AlbumRecord & GetAlbumRecord();
      Star350File & GetStar350File();
      ::mus::midi::sequence & GetMidiSequence();

      void Build(stringa & wstraFolder, bool bRecursive);
      
      protected:
      bool PreBuild(
         int &          iStep,
         bool           bRecursive,
         bool           bAddEmpty);
      public:
      //void PreRestartBuild();

      AlbumBuild(::ca::application * papp);
      virtual ~AlbumBuild();
   protected:
      bool        m_bBuilding;
      int         m_iPreBuildSubStep;
      int         m_iFindFilesStep;
      int         m_iZipFindFilesStep;
      //int         m_iExistFileStep;
      stringa   m_wstraPreBuildFolders;
      int         m_iFindFileIStart;
      int         m_iFindFileJStart;
      int         m_iZipFindFileIStart;
      int         m_iZipFindFileJStart;
      int         m_iPreBuildRowCount;
      ::sqlite::set *     m_pdsPreBuildRead;
      ::sqlite::set *     m_pdsPreBuildWrite;
      ::sqlite::set *     m_pdsGetExRead;
      int         m_iGetExStep;
//      FileFind    m_filefind;
  //    FileFind    m_filefindZip;
      bool        m_bFindFiles;
   public:
      bool IsBuilding();
      bool HasFile(const char * lpcsz);
      void SetCallbackWnd(::user::interaction * hwnd);
      void Initialize(::user::interaction * hwndCallback);
      bool m_bBuilt;
      FileInfo   m_fileinfo;
      int_array  m_iaPriority;

   protected:
      void KickBuild();
      void KillBuild();

   public:

      AlbumBuildThread  *     m_pthread;
      ::sqlite::base *  m_pdb;
      ::sqlite::set *   m_pdsRead1;
      critical_section        m_csRead1;
      ::sqlite::set *   m_pdsWrite;
      AlbumRecord             m_albumrecord;
      KaraokeUtil *           m_pkaraokeutil;
      ::mus::midi::sequence *          m_pmidisequence;
      Star350File *           m_pstar350file;
      mus::microke1 *       m_pmicroke1;

      stringa               m_wstraFolder;


      ::user::interaction *        m_hwndCallback;

      void RecurseFolders(stringa & straFolder, stringa & straFolderSource);
      void RecurseFolders(stringa & straFolder, string & wstrFolderSource);
      
   protected:
      void FindFiles(stringa & straFile, CTimeArray & base_array, stringa & straFolder);
      void ZipFindFiles(stringa & straFile, CTimeArray & timea, stringa & straFolder);

      void GetExistingFiles(int_array & ia, stringa & straFile, CTimeArray & base_array);
      void GetExistingFiles(::sqlite::set * pds, int_array & ia, stringa & straFile, CTimeArray & base_array);

      void CalcFiles(FileInfo & fileinfo, bool bRestart);

   public:

      bool add(stringa & straFile, CTimeArray & base_array);
      bool add(const char * lpcszFile, class time & time);
      bool add(AlbumRecord & record);
      bool AddAlbumRecord();
      bool AddInvalidFile(const char * lpcsz);
      bool AddEmpty(int_array & ia, stringa & straFile);
      int  AddEmptyFile(const char * lpcsz);

      bool Update(stringa & straFile, CTimeArray & base_array);
      bool Update(const char * lpcszFile, class time & time, int iId = 0x80000000);
      bool Update(AlbumRecord & record);
      bool UpdateAlbumRecord(int iId, bool bUpdateFilePath, bool bUpdateFileName);
      bool UpdateInvalidFile(const char * lpcsz);

      bool remove(stringa & straFile);
      bool remove(string & wstrFile);
      bool remove(int iId);
      bool remove(int_array & ia);

      int_array & GetPriorityArray();

   };

} // namespace mediamanager
