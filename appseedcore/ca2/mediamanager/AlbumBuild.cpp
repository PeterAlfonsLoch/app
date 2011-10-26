#include "StdAfx.h"
#include "AlbumBuild.h"
#include "AlbumBuildWnd.h"
#include "AlbumBuildThread.h"

#define DATABASE_FILENAME "album002.db"
  #define TABLE_ALBUM_CREATE "create table album (id integer primary key, filename varchar(128), filepath varchar (1024), title varchar (128), artist varchar (128), lastmodified text (19))"
//#define TABLE_ALBUM_CREATE "create table album (id integer primary key, filename varchar(128), filepath varchar (1024) unique, title varchar (128), artist varchar (128), lastmodified text (128))"
#define DATASET_READ_SQL "select id, title, artist, filename, filepath, lastmodified from album;"

namespace mediamanager
{

   const string AlbumBuild::m_wstrBuildAlbumExtensions(L"mid/midi/kar/st3/mk1");

   AlbumBuild::AlbumBuild(::ca::application * papp) :
      ca(papp),
      m_albumrecord(papp)
   {
   //   m_iExistFileStep = -1;
      m_iFindFilesStep = -1;
      m_iGetExStep = -1;
      m_bBuilding = false;
      m_bBuilt = false;
      m_pkaraokeutil    = new KaraokeUtil(papp);
      m_pmidisequence   = new ::mus::midi::sequence(papp);
      m_pstar350file    = new Star350File(papp);
      m_pmicroke1       = new mus::microke1(papp);
      m_pdb             = new ::sqlite::base(papp);
      string str;
      str = System.dir().appdata("musical_players");
      System.dir().mk(str);
      str = System.dir().path(str, DATABASE_FILENAME);
      m_pdb->setDatabase(str);
      m_pdb->connect();
      m_pdsRead1        = (::sqlite::set *) m_pdb->CreateDataset();;
      m_pdsWrite        = (::sqlite::set *) m_pdb->CreateDataset();;
      m_pdsPreBuildRead        = (::sqlite::set *) m_pdb->CreateDataset();;
      m_pdsPreBuildWrite        = (::sqlite::set *) m_pdb->CreateDataset();;
      m_pdsGetExRead = (::sqlite::set *) m_pdb->CreateDataset();;



      //m_pthread = (AlbumBuildThread *) AfxBeginThread(
        // ::ca::get_type_info < AlbumBuildThread > (),
         //THREAD_PRIORITY_IDLE);

      m_pthread = NULL;
   }

   AlbumBuild::~AlbumBuild()
   {
      if(m_pkaraokeutil != NULL)
      {
         delete m_pkaraokeutil;
         m_pkaraokeutil = NULL;
      }

      if(m_pmidisequence != NULL)
      {
         delete m_pmidisequence;
         m_pmidisequence = NULL;
      }

      if(m_pstar350file != NULL)
      {
         delete m_pstar350file;
         m_pstar350file = NULL;
      }

      if(m_pmicroke1 != NULL)
      {
         delete m_pmicroke1;
         m_pmicroke1 = NULL;
      }

      if(m_pdb != NULL)
      {
         delete m_pdb;
         m_pdb = NULL;
      }

      if(m_pdsRead1 != NULL)
      {
         delete m_pdsRead1;
         m_pdsRead1 = NULL;
      }

      if(m_pdsWrite != NULL)
      {
         delete m_pdsWrite;
         m_pdsWrite = NULL;
      }

   }

   string AlbumRecord::Prepare(class time &time)
   {
      string str;
      return time.Format(str, "%Y-%m-%d %H:%M:%S");

   }

   string AlbumRecord::Prepare(const char * lpcsz)
   {
      string str = lpcsz;
      str.replace("'", "\'");
      return str;
   }

   void AlbumRecord::Prepare(string & str, class time &time)
   {
      str = time.Format(str, "%Y-%m-%d %H:%M:%S");

   }

   void AlbumRecord::Set(Star350InfoHeader & header)
   {
      m_wstrTitle     = header.m_strSongTitle;
      m_wstrArtist    = header.m_strSinger;
   }

   void AlbumRecord::Set(CTune1000Info & info)
   {
      m_wstrTitle     = info.m_strSongName;
      info.m_straOther.get_format_string(
         m_wstrArtist, ";");
   }

   void AlbumRecord::Set(SoftKaraokeInfo & info)
   {
      m_wstrTitle    = info.m_strSongName;
      m_wstrArtist   = info.m_strAuthor;
   }

   void AlbumRecord::Set(CXFInfoHeaders & headers)
   {
      m_wstrTitle    = headers.m_strSongName;
      headers.m_xfInfoHeader.m_straPerformer.get_format_string(
         m_wstrArtist, ";");
   }

   bool AlbumRecord::FillFileInfo(
      AlbumBuild & build,
      const char * lpcsz)
   {
      string str(lpcsz);

      m_wstrArtist.Empty();

      m_wstrFilePath = lpcsz;

      int iFind = str.find(".zip:");
      if(iFind >= 0)
      {
         ex1::filesp spfile(get_app());

         spfile->open(
            str.Left(iFind + 4),
            ::ex1::file::mode_read |
            ::ex1::file::shareDenyWrite |
            ::ex1::file::type_binary);

         zip::File zipfile(get_app());

         zipfile.m_pfile = spfile;

         unzFile pf = zip::api::unzipOpen(&zipfile);

         if(pf == NULL)
            return false;

         string str;

         str = str.Mid(iFind + 5);

         if(unzLocateFile(
               pf,
               str,
               1) != UNZ_OK)
               return false;
         unz_file_info file_info;
         unzGetCurrentFileInfo(
            pf,
            &file_info,
            NULL,
            0,
            NULL, // extra Field
            0,
            NULL, // comment
            0);

         m_storage.allocate(file_info.uncompressed_size);

         int iResult = unzOpenCurrentFile(pf);
         if(iResult != UNZ_OK)
            return false;


         unzReadCurrentFile(
            pf,
            m_storage.get_data(),
            m_storage.get_size());

         iResult = unzCloseCurrentFile(pf);

         return FillFileInfo(
            build,
            m_storage);
      }
      else
      {



         int iFind1 = str.reverse_find('\\');
         int iFind2 = str.reverse_find('/');
         int iFind = 0;
         if(iFind1 >= 0)
         {
            if(iFind2 >= 0)
            {
               if(iFind1 >= iFind2)
               {
                  iFind = iFind1 + 1;
               }
               else
               {
                  iFind = iFind2 + 1;
               }
            }
            else
            {
               iFind = iFind1 + 1;
            }
         }
         else
         {
            if(iFind2 >= 0)
            {
               iFind = iFind2 + 1;
            }
         }

         m_wstrFileName = str.Mid(iFind);


         ex1::filesp spfile(get_app());
         spfile->open(
            lpcsz,
            ::ex1::file::mode_read |
            ::ex1::file::shareDenyWrite |
            ::ex1::file::type_binary);
         //Archive archive(&file, CArchive::load);



         m_storage.read(spfile);

         return FillFileInfo(build, m_storage);
      }

   }

   bool AlbumRecord::FillFileInfo(
      AlbumBuild & build,
      primitive::memory & storage)
   {

      bool bValidRecord;

      if(build.m_pkaraokeutil->IsStar350File(storage))
      {
         bValidRecord = SetStar350File(build, storage);
      }
      else
      {
         ::mus::midi::sequence & seq = build.GetMidiSequence();
         if(seq.OpenFile(
            &storage,
            ::mus::midi::OpenForHeaders,
            mus::StorageAttach)
            == MMSYSERR_NOERROR)
         {
            if(seq.GetFile().IsXFFile())
            {
               bValidRecord = SetXFFile(seq);
            }
              else if(seq.GetFile().IsSoftKaraokeFile())
            {
               bValidRecord = SetSoftKaraokeFile(seq);
            }
            else
            {
               bValidRecord = SetGenericMidiFile(seq);
               // Tune 1000 Especialization
               bValidRecord = SetTune1000File(seq);
            }
         }
         else if(build.m_pmicroke1->IsMicroke1File(storage))
         {
            if(&storage == &m_storage)
            {
               build.m_pmicroke1->ExtractFile(storage, m_storage2);
               return FillFileInfo(build, m_storage2);
            }
            else
            {
               build.m_pmicroke1->ExtractFile(storage, m_storage);
               return FillFileInfo(build, m_storage);
            }
            // not a Star350 and not a supported midi file
            // add as invalid file
            bValidRecord = false;
         }


      }

      return bValidRecord;

   }

   string AlbumRecord::GetFileName(
      const char * lpcsz)
   {
      string str(lpcsz);


      int iFind1 = str.reverse_find('\\');
      int iFind2 = str.reverse_find('/');
      int iFind = 0;
      if(iFind1 >= 0)
      {
         if(iFind2 >= 0)
         {
            if(iFind1 >= iFind2)
            {
               iFind = iFind1 + 1;
            }
            else
            {
               iFind = iFind2 + 1;
            }
         }
         else
         {
            iFind = iFind1 + 1;
         }
      }
      else
      {
         if(iFind2 >= 0)
         {
            iFind = iFind2 + 1;
         }
      }

      return str.Mid(iFind);


   }


   void AlbumBuild::Build(stringa & wstraFolder, bool bRecursive)
   {
      single_lock slRead1(&m_csRead1, TRUE);
      ::sqlite::base * pdb   = m_pdb;
      ::sqlite::set * pds    = m_pdsWrite;

      //create Album table if necessary
      try
      {
         pdb->start_transaction();
         pds->query("select * from sqlite_master where type like 'table' and name like 'album'");
         if (pds->num_rows()==0)
         {
            pds->exec();
         }
         pdb->commit_transaction();
      }
      catch (...)
      {
         pdb->rollback_transaction();
         return;
      }

      pds->set_select_sql("select id, filename, filepath, title, artist from album;");
      pds->add_insert_sql("insert into album (id, filename, filepath, title, artist) values (:NEW_aid,:NEW_afn,:NEW_afp,:NEW_at)");
      pds->open();

      m_pdsRead1->exec("PRAGMA show_datatypes=on");

      FileInfo fileinfo;

      if(bRecursive)
      {
         stringa stra;
         RecurseFolders(stra, wstraFolder);
         FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, stra);
      }
      else
      {
         FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, wstraFolder);
      }

      GetExistingFiles(fileinfo.m_iaOld, fileinfo.m_wstraOld, fileinfo.m_timeaOld);


      CalcFiles(fileinfo, false);

      add(fileinfo.m_wstraAdd, fileinfo.m_timeaAdd);
      Update(fileinfo.m_wstraUpdate, fileinfo.m_timeaUpdate);
      remove(fileinfo.m_wstraRemove);

      string strSql;
      strSql = DATASET_READ_SQL;
      m_pdsRead1->query(strSql);

   }

   /*void AlbumBuild::PreRestartBuild()
   {
      FileInfo &     fileinfo = m_fileinfo;
      vmssqlite::Database * pdb   = m_pdb;
      vmssqlite::::database::set * pds    = m_pdsWrite;

      if(pds == NULL)
      {
         AfxDebugBreak();
      }
      //create Album table if necessary
      try
      {
         pdb->start_transaction();
         pds->query("select * from sqlite_master where type like 'table' and name like 'album'");
         if (pds->num_rows()==0)
         {
            pds->exec(TABLE_ALBUM_CREATE);
            return;
         }
         pdb->commit_transaction();
      }
      catch (...)
      {
         pdb->rollback_transaction();
         return;
      }

      //pds->set_select_sql("select a.id as aid, a.filename as afn, a.filepath as afp, a.title as at, a.artist as aa from album a;");
      //pds->add_insert_sql("insert into album (id, filename, filepath, title, artist) values (:NEW_aid,:NEW_afn,:NEW_afp,:NEW_at, :NEW_aa)");
      //pds->open();

      m_pdsRead->exec("PRAGMA show_datatypes=on");

      string strSql;
      strSql = DATASET_READ_SQL;
      m_pdsRead->query(strSql);

      GetExistingFiles(
         m_pdsRead,
         fileinfo.m_iaOld,
         fileinfo.m_wstraOld,
         fileinfo.m_timeaOld);

      CalcFiles(fileinfo, true);

   }*/

   bool   AlbumBuild::PreBuild(
      int &          iStep,
      bool           bRecursive,
      bool           bAddEmpty)
   {
      FileInfo & fileinfo           = m_fileinfo;
      ::sqlite::base * pdb    = m_pdb;
      ::sqlite::set * pds     = m_pdsWrite;

      if(iStep < -1)
         return false;

      if(iStep == -1)
      {
         m_iPreBuildSubStep = -1;
      }

      if(iStep == 0)
      {
         if(m_iPreBuildSubStep == -2)
         {
            m_iPreBuildSubStep = -1;
         }
         else if(m_iPreBuildSubStep == 1)
         {
            m_iPreBuildSubStep = -1;
            iStep++;
         }
      }
      else
      {
         m_iPreBuildSubStep = -1;
         iStep++;
      }

      if(iStep == 0)
      {
         if(m_iPreBuildSubStep == -1)
         {
            if(pds == NULL)
            {
               AfxDebugBreak();
            }
            //create Album table if necessary
            try
            {
               pdb->start_transaction();
               m_pdsPreBuildWrite->query("select * from sqlite_master where type like 'table' and name like 'album'");
               if (m_pdsPreBuildWrite->num_rows()==0)
               {
                  m_pdsPreBuildWrite->exec(TABLE_ALBUM_CREATE);
               }
               pdb->commit_transaction();
            }
            catch (...)
            {
               pdb->rollback_transaction();
               iStep = -2;
               return false;
            }

            try
            {
               m_pdsPreBuildRead->exec("PRAGMA show_datatypes=on");
            }
            catch(...)
            {
            }

            //m_pdsPreBuildRead->query("select a.id as aid, a.filename as afn, a.filepath as afp, a.title as at, a.artist as aa from album a;");
            m_iFindFilesStep = 0;
            m_iZipFindFilesStep = 0;
            m_iPreBuildSubStep = 0;
            m_iGetExStep = -1;
            //int m_iPreBuildRowCount = m_pdsPreBuildRead->num_rows();
            m_wstraPreBuildFolders.remove_all();
            if(bRecursive)
            {
               RecurseFolders(m_wstraPreBuildFolders, m_wstraFolder);
            }
            else
            {
               m_wstraPreBuildFolders = m_wstraFolder;
            }

            single_lock sl(&m_csRead1, TRUE);
            m_pdsRead1->query(DATASET_READ_SQL);
            if(m_pdsRead1->result.record_header.get_size() != 6)
            {
               m_pdsRead1->result.record_header.remove_all();
               database::field_properties prop;
               prop.name = "id";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
               prop.name = "title";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
               prop.name = "artist";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
               prop.name = "filename";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
               prop.name = "filepath";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
               prop.name = "lastmodified";
               prop.type = database::DataTypeWideString;
               m_pdsRead1->result.record_header.add(prop);
            }

         }
         else if(m_iPreBuildSubStep == 0)
         {
            GetExistingFiles(fileinfo.m_iaOld, fileinfo.m_wstraOld, fileinfo.m_timeaOld);
            if(m_iGetExStep == -1)
               m_iPreBuildSubStep = 1;
         }
         else
         {
            if(m_iFindFilesStep >= 0)
            {
               FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, m_wstraPreBuildFolders);
            }
            if(m_iZipFindFilesStep >= 0)
            {
               ZipFindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, m_wstraPreBuildFolders);
            }

            CalcFiles(fileinfo, false);
            if(bAddEmpty)
            {
               AddEmpty(fileinfo.m_iaAdd, fileinfo.m_wstraAdd);
               fileinfo.m_iaUpdate.add(fileinfo.m_iaAdd);
               fileinfo.m_wstraUpdate.add(fileinfo.m_wstraAdd);
               fileinfo.m_timeaUpdate.add(fileinfo.m_timeaAdd);
               fileinfo.m_iaAdd.remove_all();
               fileinfo.m_wstraAdd.remove_all();
               fileinfo.m_timeaAdd.remove_all();
            }
            if(m_iZipFindFilesStep < 0 &&
               m_iFindFilesStep < 0 &&
               m_iGetExStep < 0)
            {
               m_iPreBuildSubStep = -2;
            }

         }

      }
      else
      {
         // pre-built
         iStep = -1;
      }
      return true;

   }

   bool AlbumBuild::add(
       stringa & stra,
       CTimeArray & timea)
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         add(stra[i], timea[i]);
      }
      return true;
   }

   bool AlbumBuild::AddEmpty(int_array & ia, stringa & stra)
   {
      ::sqlite::base * pdb   = m_pdb;
      ::sqlite::set * pds    = m_pdsWrite;
      single_lock sl(&m_csRead1, TRUE);

      int iId = 0;

      pds->query("select max(id) as maxid from album;");
      if (pds->num_rows() > 0)
      {
         iId = pds->fv("maxid").get_integer();
         iId++;
      }

      AlbumRecord record(get_app());

      int iGroup = 1;

      string strSql;
      string str;

      database::record sqlrecord;

      strSql = "insert into album (id, filepath, filename) values ";
      pdb->start_transaction();
      for(int i = 0; i < stra.get_size(); i++)
      {
         for(int j = 0; j < iGroup; j++)
         {
            if(j >= 1)
               strSql += ", ";
            ia.add(iId);
            str.Format(
               "('%d','%s', '%s')",
               iId,
               stra[i],
               AlbumRecord::GetFileName(stra[i]));
            strSql+= str;
            sqlrecord.add(var(iId)); // id
            sqlrecord.add(var("")); // title
            sqlrecord.add(var("")); // artist
            sqlrecord.add(var(AlbumRecord::GetFileName(stra[i]))); // filename
            sqlrecord.add(var(stra[i])); // filepath
            sqlrecord.add(var("")); // last modified
            m_pdsRead1->result.records.add(sqlrecord);

            if(stra.get_size() <= 0)
               break;
            iId++;
            sqlrecord.remove_all();
         }
         pds->exec(strSql);
         strSql = "insert into album (id, filepath, filename) values ";
      }
      pdb->commit_transaction();
      return true;
   }

   bool AlbumBuild::Update(
       stringa & stra,
       CTimeArray & timea)
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         Update(stra[i], timea[i]);
      }
      return true;
   }

   bool AlbumBuild::remove(
       stringa & stra)
   {
      string strSql;
      string str;

      for(int i = 0; i < stra.get_size(); i++)
      {
         str = stra[i];
         str.replace("'","''");
         strSql.Format("delete from album where filepath = '%s'", str);
         m_pdsWrite->exec(strSql);
      }

      return true;
   }

   bool AlbumBuild::remove(
       string & str)
   {
      string strSql;

      str =  str;
      str.replace("'","''");
      strSql.Format("delete from album where filepath = '%s'", str);
      m_pdsWrite->exec(strSql);

      return true;
   }

   bool AlbumBuild::remove(int iId)
   {
      string strSql;

      strSql.Format("delete from album where id = '%d'", iId);
      m_pdsWrite->exec(strSql);

      return true;
   }

   bool AlbumBuild::remove(int_array & ia)
   {
      int iGroup = 30;

      string strSql;
      string str;
      while(ia.get_size() > 0)
      {
         strSql = "delete from album where ";
         for(int i = 0; i < iGroup; i++)
         {
            if(i >= 1)
               strSql += " OR ";
            str.Format("id = '%d'", ia.last_element());
            ia.remove_at(ia.get_upper_bound());
            strSql += str;
            if(ia.get_size() <= 0)
               break;
         }
         m_pdsWrite->exec(strSql);
      }

      return true;
   }


   bool AlbumBuild::add(
       const char * lpcsz,
       class time & time)
   {
//      ::sqlite::set * pds = m_pdsWrite;

//      AlbumRecord & albumrecord = GetAlbumRecord();
      bool bValidRecord = GetAlbumRecord().FillFileInfo(*this, lpcsz);
      GetAlbumRecord().m_timeLastWrite = time;

      if(bValidRecord)
      {
         AddAlbumRecord();
      }
      else
      {
         AddInvalidFile(lpcsz);
      }
      return true;
   }


   bool AlbumBuild::Update(
       const char * lpcsz,
       class time & time,
       int iId)
   {
//      ::sqlite::set * pds = m_pdsWrite;


//      AlbumRecord & albumrecord = GetAlbumRecord();
      bool bValidRecord = GetAlbumRecord().FillFileInfo(*this, lpcsz);
      GetAlbumRecord().m_timeLastWrite = time;

      if(bValidRecord)
      {
         UpdateAlbumRecord(iId, false, false);
      }
      else
      {
         UpdateInvalidFile(lpcsz);
      }
      return true;
   }



   ::mus::midi::sequence & AlbumBuild::GetMidiSequence()
   {
      return *m_pmidisequence;
   }

   AlbumRecord & AlbumBuild::GetAlbumRecord()
   {
      return m_albumrecord;
   }

   bool AlbumBuild::AddInvalidFile(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return true;
   }

   bool AlbumBuild::UpdateInvalidFile(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return true;
   }

   bool AlbumBuild::AddAlbumRecord()
   {
      //::sqlite::base * pdb   = m_pdb;
      ::sqlite::set * pds    = m_pdsWrite;
      AlbumRecord & record = GetAlbumRecord();

      int iId = 0;

      pds->query("select max(id) as maxid from album;");
      if (pds->num_rows() > 0)
      {
         iId = pds->fv("maxid");
         iId++;
      }


   //   pdb->start_transaction();
      record.GetInsertSql(iId);
      pds->exec((char *)record.m_storageSql.get_data());
   //   pdb->commit_transaction();

      return true;

   }

   int AlbumBuild::AddEmptyFile(const char * lpcsz)
   {
      ::sqlite::base * pdb   = m_pdb;
      ::sqlite::set * pds    = m_pdsWrite;
      AlbumRecord record(get_app());

      record.m_wstrFilePath = lpcsz;

      int iId = 0;

      pds->query("select max(id) as maxid from album;");
      if (pds->num_rows() > 0)
      {
         iId = pds->fv("maxid");
         iId++;
      }


      pdb->start_transaction();
      record.GetInsertSql(iId);
      pds->exec((char *)record.m_storageSql.get_data());
      pdb->commit_transaction();

      return iId;

   }

   bool AlbumBuild::UpdateAlbumRecord(
      int iId,
      bool bUpdateFilePath,
      bool bUpdateFileName)
   {
//      ::sqlite::base * pdb   = m_pdb;
      ::sqlite::set * pds    = m_pdsWrite;
      AlbumRecord & record = GetAlbumRecord();



      string strSql;
      string str;

      str = record.m_wstrFilePath;
      str.replace("'","''");

      if(iId < 0)
      {
         strSql.Format("select id from album where filepath='%s';", str);
         pds->query(strSql);
         ASSERT(pds->num_rows() == 1);
         iId = pds->fv("id");
      }


      //pdb->start_transaction();
      record.GetUpdateSql(
         iId,
         bUpdateFilePath,
         bUpdateFileName);
      pds->exec((char *)record.m_storageSql.get_data());
      //pdb->commit_transaction();

      return true;

   }

   bool AlbumRecord::SetStar350File(
      AlbumBuild & albumbuild,
      primitive::memory &storage)
   {
      Star350File & file = albumbuild.GetStar350File();
      if(file.OpenFile(
         &storage,
         Star350File::OpenForParsing,
         mus::StorageAttach) == Star350File::InvalidFile)
      {
         file.CloseFile();
         return false;
      }
      Set(*file.GetInfoHeader());
      file.CloseFile();

      return true;
   }

   bool AlbumRecord::SetSoftKaraokeFile(::mus::midi::sequence &seq)
   {
      SoftKaraokeInfo karinfo;

      seq.GetFile().GetTracks().seek_begin();
      seq.GetFile().GetTracks().GetKarInfoHeader(
            &karinfo);
      karinfo.Prepare();
      Set(karinfo);
      return true;
   }

   bool AlbumRecord::SetXFFile(::mus::midi::sequence &seq)
   {
      CXFInfoHeaders xfihs;
      seq.GetFile().GetTracks().GetXFInfoHeaders(&xfihs);
      xfihs.Prepare();
      Set(xfihs);
      return true;
   }

   bool AlbumRecord::SetTune1000File(::mus::midi::sequence &seq)
   {
      CTune1000Info t1000i;
      seq.GetFile().GetTracks().seek_begin();
      seq.GetFile().GetTracks().GetTune1000InfoHeader(
            &t1000i, 0);
      t1000i.Prepare();
      Set(t1000i);
      return true;

   }

   bool AlbumRecord::SetGenericMidiFile(::mus::midi::sequence &seq)
   {
      UNREFERENCED_PARAMETER(seq);
      return true;
   }

   bool AlbumBuild::add(AlbumRecord &record)
   {
      UNREFERENCED_PARAMETER(record);
      return true;
   }

   Star350File & AlbumBuild::GetStar350File()
   {
      return *m_pstar350file;
   }



   void AlbumBuild::RecurseFolders(stringa & wstraFolder, stringa & wstraFolderSource)
   {
      int i;
      string str;

      //DWORD dw = ::_getmbcp();

      for(i = 0; i < wstraFolderSource.get_size(); i++)
      {
         str = wstraFolderSource.element_at(i);
         RecurseFolders(wstraFolder, str);
      }

   }

   void AlbumBuild::RecurseFolders(stringa & wstraFolder, string & wstrFolderSource)
   {
      System.dir().rls_dir(wstrFolderSource, &wstraFolder);
   }


   void AlbumBuild::FindFiles(
       stringa & wstraFile,
       CTimeArray & timea,
       stringa & wstraFolder)
   {
      UNREFERENCED_PARAMETER(wstraFile);
      UNREFERENCED_PARAMETER(timea);
      UNREFERENCED_PARAMETER(wstraFolder);
      ASSERT(FALSE);

      /*
      FileFind & fileFind = m_filefind;
      BOOL ok = m_bFindFiles;
      int i, j;
      class time time;
      string str, strFormat;

      if(wstraFolder.get_size() <= 0)
      {
         //System.simple_message_box("There are no folders for the album build.");
      }

      if(m_iFindFilesStep == -1 || m_iFindFilesStep == 0)
      {
         m_iFindFileIStart = 0;
         m_iFindFileJStart = 0;
         ok = false;
      }

      stringa wstraExtension;
      string str;
      str = m_wstrBuildAlbumExtensions;
      wstraExtension.add_tokens(str, "/", false);
      string strB;
      int iIteration = 0;
      int iIterationCount = 10;
      for(i = m_iFindFileIStart; i < wstraFolder.get_size(); i++)
      {
         m_iFindFileIStart = i;
         for(j = m_iFindFileJStart; j < wstraExtension.get_size(); j++)
         {
            m_iFindFileJStart = j;
            if(!ok)
            {
               str = wstraFolder.element_at(i);
               str += L"\\*.";
               str += wstraExtension.element_at(j);
      //         gen::international::UnicodeToACP(str, str);
               ok = fileFind.FindFile(str);;
            }
            while(ok)
            {
               ok = fileFind.FindNextFile();
               str = fileFind.GetFilePath();
               //str.SetACP(str);
               //gen::international::UnicodeToACP(strB, str);
               //ASSERT(str.Collate(strB) == 0);
               wstraFile.add(str);
               fileFind.GetLastWriteTime(time);
               timea.add(time);
               if(m_iFindFilesStep >= 0)
               {
                  m_iFindFilesStep++;
                  iIteration++;
                  if(iIteration > iIterationCount)
                  {
                     break;
                  }
               }
            }
            if(m_iFindFilesStep >= 0)
            {
               m_iFindFilesStep++;
               iIteration++;
               if(iIteration > iIterationCount)
               {
                  break;
               }
            }
         }
         if(m_iFindFilesStep >= 0 && iIteration > iIterationCount)
         {
            break;
         }
         m_iFindFileJStart = 0;
      }

      if(i >= wstraFolder.get_size())
      {
         m_iFindFilesStep = -1;
      }
*/

   }

   void AlbumBuild::ZipFindFiles(
       stringa & wstraFile,
       CTimeArray & timea,
       stringa & wstraFolder)
   {
      UNREFERENCED_PARAMETER(wstraFile);
      UNREFERENCED_PARAMETER(timea);
      UNREFERENCED_PARAMETER(wstraFolder);
      ASSERT(FALSE);
/*      FileFind & fileFind = m_filefindZip;
      int i, j;
      class time time;
      string str, strFormat;

      if(wstraFolder.get_size() <= 0)
      {
         //System.simple_message_box("There are no folders for the album build.");
      }

      if(m_iZipFindFilesStep == -1 || m_iZipFindFilesStep == 0)
      {
         m_iZipFindFileIStart = 0;
         m_iZipFindFileJStart = 0;
      }

      stringa wstraExtension2;
      string str;
      str = m_wstrBuildAlbumExtensions;
      wstraExtension2.add_tokens(str, "/", false);

      stringa wstraExtension;
      wstraExtension.add("zip");
      string strB;
      string wstrPath;
      string wstrExtraPath;
      for(i = m_iZipFindFileIStart; i < wstraFolder.get_size(); i++)
      {
         m_iZipFindFileIStart = i;
         for(j = m_iZipFindFileJStart; j < wstraExtension.get_size(); j++)
         {
            m_iZipFindFileJStart = j;
            str = wstraFolder.element_at(i);
            str += L"\\*.";
            str += wstraExtension.element_at(j);
   //         gen::international::UnicodeToACP(str, str);
            BOOL ok;
            ok = fileFind.FindFile(str);;
            while(ok)
            {
               ok = fileFind.FindNextFile();
               str = fileFind.GetFilePath();
               //str.SetACP(str);
               //gen::international::UnicodeToACP(strB, str);
               //ASSERT(str.Collate(strB) == 0);
               {
                  ex1::filesp spfile(get_app());

                  spfile->open(str, ::ex1::file::mode_read | ::ex1::file::type_binary);

                  zip::File zipfile(get_app());

                  zipfile.m_pfile = spfile;

                  unzFile pf = zip::api::unzipOpen(&zipfile);

                  if(pf != NULL)
                  {
                     while(true)
                     {
                        if(unzOpenCurrentFile(pf) == UNZ_OK)
                        {
                           const int BUFSIZE = 4096;
   //                        char szTempName[MAX_PATH];
   //                        char buffer[BUFSIZE];
                           WCHAR lpPathBuffer[BUFSIZE];
                           GetTempPathW(BUFSIZE,   // length of the buffer
                              lpPathBuffer);      // buffer for path


                            CHAR szTitle[_MAX_PATH];

                           unz_file_info file_info;
                           unzGetCurrentFileInfo(
                              pf,
                              &file_info,
                              szTitle,
                              _MAX_PATH,
                              NULL, // extra Field
                              0,
                              NULL, // comment
                              0);



                           wstrExtraPath = szTitle;

                           for(int i = 0; i < wstraExtension2.get_size(); i++)
                           {
                              string wstrExt2 = wstraExtension2[i];
                              string wstrEnd2;
                              wstrEnd2 = "." + wstrExt2;
                              if(wstrExtraPath.Right(wstrEnd2.get_length()) ==
                                 wstrEnd2)
                              {
                                 wstrPath = str + ":" + wstrExtraPath;

                                 wstraFile.add(wstrPath);
                                 //if(file_info.dosDate != NULL)
                                 //{
                                   // class time time(HIWORD(file_info.dosDate),
                                     //          LOWORD(file_info.dosDate));
                                    //timea.add(time);
                                 //}
                                 //else
                                 {
                                    class time time(
                                       file_info.tmu_date.tm_year,
                                       file_info.tmu_date.tm_mon + 1,
                                       file_info.tmu_date.tm_mday,
                                       file_info.tmu_date.tm_hour,
                                       file_info.tmu_date.tm_min,
                                       file_info.tmu_date.tm_sec);
                                    timea.add(time);
                                 }
                                 break;
                              }

                           }


   //            nextFile:
                           unzCloseCurrentFile(pf);
                        }
                        if(unzGoToNextFile(pf) != UNZ_OK)
                        {
                           break;
                        }

                     }

                  }

               }
            }
            if(m_iZipFindFilesStep >= 0)
            {
               m_iZipFindFilesStep++;
               if(m_iZipFindFilesStep % 2 == 0)
               {
                  break;
               }
            }
         }
         if(m_iZipFindFilesStep >= 0 && m_iZipFindFilesStep % 2 == 0)
         {
            break;
         }
         m_iFindFileJStart = 0;
      }
      if(i >= wstraFolder.get_size())
      {
         m_iZipFindFilesStep = -1;
      }*/
   }


   void AlbumRecord::GetInsertSql(int iId)
   {
        while(_snprintf(
         (char *) m_storageSql.get_data(),
         m_storageSql.get_size(),
         "insert into album (id, filename, filepath, title, artist, lastmodified) values ('%d','%s','%s','%s','%s','%s');",
         iId,
         Prepare(m_wstrFileName),
         Prepare(m_wstrFilePath),
         Prepare(m_wstrTitle),
         Prepare(m_wstrArtist),
         Prepare(m_wstrLastWriteTime)) < 0)
      {
         m_storageSql.allocate(m_storageSql.get_size() + 1024);
      }
   }

   void AlbumRecord::GetUpdateSql(
      int iId,
      bool bUpdateFilePath,
      bool bUpdateFileName)
   {
      if(!bUpdateFilePath && !bUpdateFileName)
      {
         string str;
         Prepare(str,   m_timeLastWrite);
           while(_snprintf(
            (char *) m_storageSql.get_data(),
            m_storageSql.get_size(),
            "update album set title = '%s', artist = '%s', lastmodified = '%s' where id = '%d';",
            Prepare(m_wstrTitle),
            Prepare(m_wstrArtist),
            str,
            iId) < 0)
         {
            m_storageSql.allocate(m_storageSql.get_size() + 1024);
         }
      }
      else
      {
         string str;
         Prepare(str,   m_timeLastWrite);
           while(_snprintf(
            (char *) m_storageSql.get_data(),
            m_storageSql.get_size(),
            "update album set filename = '%s', filepath = '%s', title = '%s', artist = '%s', lastmodified = '%s' where id = '%d';",
            Prepare(m_wstrFileName),
            Prepare(m_wstrFilePath),
            Prepare(m_wstrTitle),
            Prepare(m_wstrArtist),
            str,
            iId) < 0)
         {
            m_storageSql.allocate(m_storageSql.get_size() + 1024);
         }
      }
   }

   void AlbumBuild::GetExistingFiles(
      int_array & ia,
      stringa & straFile,
      CTimeArray & timea)
   {
      ::sqlite::set * pds = m_pdsGetExRead;
      if(m_iGetExStep <= 0)
      {
         string strSql;
         strSql = "select id, filepath, lastmodified from album;";
         pds->query(strSql);
      }
      GetExistingFiles(pds, ia, straFile, timea);
   }

   void AlbumBuild::GetExistingFiles(
      ::sqlite::set * pds,
      int_array & ia,
      stringa & wstraFile,
      CTimeArray & timea)
   {
      int iRowCount = pds->num_rows();



      int iFieldIndexId = pds->GetFieldIndex("id");
      int iFieldIndexFilePath = pds->GetFieldIndex("filepath");
      int iFieldIndexLastModified = pds->GetFieldIndex("lastmodified");

      string strTime;
      int iYear;
      int iMonth;
      int iDay;
      int iHour;
      int iMinute;
      int iSecond;
      string wstrFile;

      char * lpszTime;

      ia.set_size(iRowCount);
      wstraFile.set_size(iRowCount);
      timea.set_size(iRowCount);

      if(m_iGetExStep == -1)
         m_iGetExStep = 0;

      for(; m_iGetExStep < iRowCount; m_iGetExStep++)
      {
         int iRow = m_iGetExStep;
         pds->seek(iRow);

         ia.set_at(iRow, pds->GetSelectFieldValue(iFieldIndexId));

         wstrFile = pds->GetSelectFieldValue(iFieldIndexFilePath);

         wstraFile.set_at(iRow, wstrFile);

         strTime = pds->GetSelectFieldValue(iFieldIndexLastModified);

         if(strTime.get_length() == 19)
         {
            lpszTime = (LPTSTR) (const char *) strTime;
            lpszTime[4] = '\0';
            lpszTime[7] = '\0';
            lpszTime[10] = '\0';
            lpszTime[13] = '\0';
            lpszTime[16] = '\0';
            iYear    = atoi(&lpszTime[0]);
            iMonth   = atoi(&lpszTime[5]);
            iDay     = atoi(&lpszTime[8]);
            iHour    = atoi(&lpszTime[11]);
            iMinute  = atoi(&lpszTime[14]);
            iSecond  = atoi(&lpszTime[17]);
            class time time(
                  iYear,
                  iMonth,
                  iDay,
                  iHour,
                  iMinute,
                  iSecond);
            timea.set_at(iRow, time);
         }
         else
         {
            class time time;
            timea.set_at(iRow, time);
         }
         if(m_iGetExStep % 100 == 99)
         {
            m_iGetExStep++;
            break;
         }
      }
      if(m_iGetExStep >= iRowCount)
      {
         m_iGetExStep = -1;
      }

   }

   void AlbumBuild::CalcFiles(FileInfo & fileinfo, bool bRestart)
   {
      int_array & iaOld    = fileinfo.m_iaOld;
      int_array & iaUpdate = fileinfo.m_iaUpdate;
      int_array & iaRemove = fileinfo.m_iaRemove;
      stringa & straNew = fileinfo.m_wstraNew; // [in]  the files that must be in the album
      CTimeArray & timeaNew = fileinfo.m_timeaNew; // [in]  the files last write time
      stringa & straOld = fileinfo.m_wstraOld; // [in]  the files that are already in the album
      CTimeArray & timeaOld = fileinfo.m_timeaOld; // [in]  the existing files recotds last write time
      stringa & straAdd = fileinfo.m_wstraAdd; // [out] files not in the album that must be in the album
      CTimeArray & timeaAdd = fileinfo.m_timeaAdd; // [out] their time
      stringa & straUpdate = fileinfo.m_wstraUpdate; // [out] files already in the album that must be updated
      CTimeArray & timeaUpdate = fileinfo.m_timeaUpdate; // [out] their time
      stringa & straRemove = fileinfo.m_wstraRemove; // [out] files that don't need to be in the album

      CTimeArray timeaRemove;

      fileinfo.m_wstraAdd.remove_all();
      fileinfo.m_timeaAdd.remove_all();

      if(bRestart)
      {
         fileinfo.m_wstraUpdate = fileinfo.m_wstraOld;
         fileinfo.m_timeaUpdate = fileinfo.m_timeaOld;
      }


      straUpdate = straNew;
      timeaUpdate = timeaNew;

      iaRemove    = iaOld;
      straRemove = straOld;
      timeaRemove = timeaOld;

      int iUpdate = 0;
      int iFound;

      while(iUpdate < straUpdate.get_size())
      {
         iFound = straRemove.find_first(straUpdate[iUpdate]);

         if(iFound >= 0)
         {
            if(timeaUpdate[iUpdate] == timeaRemove[iFound])
            {
               // The file has been found in the old base_array
               // and its write time has not changed, so
               // it is not necessary to Update.
               straUpdate.remove_at(iUpdate);
               timeaUpdate.remove_at(iUpdate);
            }
            else
            {

               // It needs update.
               iaUpdate.add(iaRemove[iFound]);
               iUpdate++;
            }
            // The file has been found in the old base_array,
            // so it will not be Removed.
            iaRemove.remove_at(iFound);
            straRemove.remove_at(iFound);
            timeaRemove.remove_at(iFound);
         }
         else
         {
            // Not found so it must be added.
            straAdd.add(straUpdate[iUpdate]);
            timeaAdd.add(timeaUpdate[iUpdate]);
            straUpdate.remove_at(iUpdate);
            timeaUpdate.remove_at(iUpdate);
         }
      }

      straNew.remove_all();
      timeaNew.remove_all();
      straOld.remove_all();
      timeaOld.remove_all();

   }


   void AlbumBuild::KickBuild()
   {
      m_bBuilding = true;
      if(m_pthread == NULL)
      {
         m_pthread = AfxBeginThread < AlbumBuildThread > (
            get_app(),
            THREAD_PRIORITY_NORMAL,
            0,
            CREATE_SUSPENDED);
         ::ResetEvent(m_pthread->m_heventSynch);
         m_pthread->ResumeThread();
         WaitForSingleObject(m_pthread->m_heventSynch, INFINITE);
         m_pthread->m_heventSynch = NULL;
         m_pthread->Initialize(this);
         m_pthread->m_pwnd->m_hwndCallback = m_hwndCallback;
      }
      m_pthread->m_pwnd->KickBuild();
   }

   void AlbumBuild::KillBuild()
   {
      if(m_pthread != NULL)
      {
         m_pthread->m_pwnd->KillBuild();
      }
      m_fileinfo.Reset();
      m_bBuilding = false;
   }


   int_array & AlbumBuild::GetPriorityArray()
   {
      return m_iaPriority;
   }

   void AlbumBuild::Initialize(::user::interaction * hwndCallback)
   {
      m_hwndCallback = hwndCallback;
      if(m_pthread != NULL)
      {
         m_pthread->Initialize(this);
         m_pthread->m_pwnd->m_hwndCallback = hwndCallback;
      }
   }

   void AlbumBuild::SetCallbackWnd(::user::interaction * hwndCallback)
   {
      m_hwndCallback = hwndCallback;
      if(m_pthread != NULL)
      {
         m_pthread->m_pwnd->m_hwndCallback = hwndCallback;
      }
   }

   void AlbumBuild::FileInfo::Reset()
   {
      m_iaAdd.remove_all();
      m_iaNew.remove_all();
      m_iaOld.remove_all();
      m_iaRemove.remove_all();
      m_iaUpdate.remove_all();
      m_timeaAdd.remove_all();
      m_timeaNew.remove_all();
      m_timeaOld.remove_all();
      m_timeaUpdate.remove_all();
      m_wstraAdd.remove_all();
      m_wstraNew.remove_all();
      m_wstraOld.remove_all();
      m_wstraRemove.remove_all();
      m_wstraUpdate.remove_all();
   }

   bool AlbumBuild::HasFile(const char * lpcsz)
   {
      ::sqlite::set * pds    = (::sqlite::set *) m_pdb->CreateDataset();
      if(pds == NULL)
         return FALSE;

      string strSql;
      strSql.Format("select id from album where filepath='%s';", lpcsz);
      pds->query(strSql);
      bool bHasFile = pds->num_rows() >= 1;

      pds->close();
      delete pds;

      return bHasFile;


   }

   AlbumRecord::AlbumRecord(::ca::application * papp)
   : ca(papp)
   {
      m_storageSql.allocate(1024);
   }

   bool AlbumBuild::IsBuilding()
   {
      return m_bBuilding;
   }

} // namespace mediamanager








