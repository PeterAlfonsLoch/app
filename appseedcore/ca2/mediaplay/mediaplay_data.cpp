#include "StdAfx.h"

namespace mediaplay
{

   data::data(document * pdocument) :
      ::ca::ca(pdocument->get_app()),
      m_pdocument(pdocument),
      MidiDocHelper(pdocument->get_app()), 
      m_fileWave(pdocument->get_app()) ,
      m_memfile(pdocument->get_app()),
      m_karaokeinterface(pdocument->get_app())
   {

      m_bWrite = false;
      
      SetKaraokeData(new ikar::data(get_app()));
      if(GetKaraokeData().IsNull())
         throw new memory_exception;

      m_emode = ModeNone;
      m_bPlay = false;

   }

   data::~data()
   {
   }

   BOOL data::on_new_document()
   {
      return TRUE;
   }



   ::radix::thread * data::HelperGetMidiPlayerCallbackThread()
   {
      return NULL;
   }


   data::EMode data::GetMode()
   {
      return m_emode;
   }

   data::e_type data::get_type()
   {
      return m_etype;
   }




   bool data::on_open_document(var varFile) 
   {
      keeper < bool > keepWrite(&m_bWrite, true, false, true);

      ikar::data & data = GetKaraokeData();
      
      CSingleLock slKaraokeData(&data.m_mutex, FALSE);
      if(!slKaraokeData.Lock(1984 * 5))
         return FALSE;

      e_type e_type = DetermineFileType(varFile);

      if(e_type == TypeZip)
      {
         return OnOpenZipFile(varFile);
      }

      string strPath;

      if(varFile.get_type() == var::type_propset)
      {
         if(varFile.propset()["url"].get_string().has_char())
         {
            strPath = varFile.propset()["url"];
         }
      }
      else
      {
         strPath = varFile;
      }

      
      m_etype = e_type;
      
      EMode emode = DetermineMode(e_type);

      m_emode = emode;

      if(GetMode() == ModeWave)
      {
         if(m_fileWave->IsOpened())
            m_fileWave->close();
       
         if(varFile.get_type() == var::type_propset
         && varFile.propset()["file"].ca2 < ::ex1::file >() != NULL)
         {
            m_fileWave.destroy();
            m_fileWave.m_p = varFile.propset()["file"].ca2 < ::ex1::file >();
         }
         else if(e_type == TypeRtp)
         {
            m_fileWave.destroy();
            rtp::file * pfile =  new rtp::file(get_app());

            m_fileWave.m_p = pfile;
            if(!pfile->rx_open(
               System.url().get_server(strPath),
               System.url().get_port(varFile)))
            {
      /*         throw new ex1::file_exception_sp(fileexception.m_cause, 
                  fileexception.m_lOsError,
                  fileexception.m_wstrFileName);*/
               throw new ex1::file_exception_sp(get_app());
            }
            pfile->set_payload("mp3", &payload_type_mp3_128);
         }
         else if(gen::str::begins(strPath, "http://")
            ||   gen::str::begins(strPath, "https://"))
         {
             m_fileWave.destroy();
             sockets::http::file * pfile = new sockets::http::file(get_app());
             m_fileWave.m_p = *pfile;

            if(!pfile->open(strPath, ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary))
            {
               throw new ex1::file_exception_sp(get_app());
            }
         }
         else if(gen::str::begins(strPath, "ifs://")
            ||   gen::str::begins(strPath, "uifs://"))
         {
             m_fileWave.destroy();
             ex1::filesp * pfile = ifs(get_app(), "").get_file(strPath);
             m_fileWave.m_p = *pfile;

            /*if(!pfile->open(strPath, ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary))
            {
               throw new ex1::file_exception_sp(get_app());
            }*/
         }
         else
         {
            m_fileWave.create(get_app());
            ex1::file_exception_sp fileexception(get_app());
            if(!m_fileWave->open(strPath, ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary))
            {
      /*         throw new ex1::file_exception_sp(fileexception.m_cause, 
                  fileexception.m_lOsError,
                  fileexception.m_wstrFileName);*/
               throw new ex1::file_exception_sp(get_app());
            }
         }

         m_fileWave->seek_to_begin();

         m_strPathName = strPath;

         ::mediaplay::view_update_hint uh;


         uh.m_pwaveplayer = NULL;
         uh.set_type(::mediaplay::view_update_hint::TypeGetWavePlayer);
         get_document()->update_all_views(NULL, 0, &uh);

         audWavePlayer * pwaveplayer = uh.m_pwaveplayer;

         if(pwaveplayer != NULL)
         {
            m_karaokeinterface.m_pwaveplayer = pwaveplayer;
            GetKaraokeData().SetInterface(&m_karaokeinterface);
            audWavePlayerCommand command;
            if(m_etype == data::TypeRtp)
            {
               command.OpenRtpFile(m_fileWave);
            }
            else
            {
               bool bSeekable = !(gen::str::begins(strPath, "http://") || gen::str::begins(strPath, "https://")
                  || gen::str::begins(strPath, "uifs://") || gen::str::begins(strPath, "fs://")
                  || varFile.ca2 < ::sockets::http::file > () != NULL
                  || varFile.propset()["file"].ca2 < ::sockets::http::file >() != NULL);
               command.OpenFile(m_fileWave, bSeekable);
            }
            /*
            switch(pviewdata->get_type())
            {
            case data::TypeAiff:
               command.OpenAiffFile(&pviewdata->GetWaveFile());
               break;
            case data::TypeCda:
               command.OpenCdaFile(&pviewdata->GetWaveFile());
               break;
            case data::TypeMpeg:
               command.OpenMp3File(&pviewdata->GetWaveFile());
               break;
            case data::TypeTwinVQ:
               command.OpenVqfFile(&pviewdata->GetWaveFile());
               break;
            case data::TypeWav:
               command.OpenWavFile(&pviewdata->GetWaveFile());
               break;
            case data::TypeWm:
               command.OpenWmFile(&pviewdata->GetWaveFile());
               break;
            default:
               ASSERT(FALSE);
               break;
            }*/
            pwaveplayer->ExecuteCommand(command);
         }

         string str;
         string strFile;

         int iFind = m_strPathName.reverse_find(L'.');
         str = m_strPathName.Left(iFind + 1) + "kok";
         strFile = Application.file().as_string(str);
         if(strFile.has_char())
         {
            gen::memory_file memfile(get_app());
            memfile.from_string(strFile);
            m_karaokeinterface.ParseKOKFile(&memfile);
            GetKaraokeData().Initialize(&m_karaokeinterface);
            GetKaraokeData().Prepare();
            goto kokEnd;
         }

         iFind = m_strPathName.reverse_find(L'.');
         str = m_strPathName.Left(iFind + 1) + "ssa";
         strFile = Application.file().as_string(str);
         if(strFile.has_char())
         {
            gen::memory_file memfile(get_app());
            memfile.from_string(strFile);
            m_karaokeinterface.ParseSSAFile(&memfile);
            GetKaraokeData().Initialize(&m_karaokeinterface);
            GetKaraokeData().Prepare();
            goto kokEnd;
         }
   kokEnd:

         return true;
      }
      else if(GetMode() == ModeMidi)
      {
         GetKaraokeData().SetInterface(&HelperGetMidiSequence());

         if(!HelperOnOpenDocument(varFile))
         {
            return false;
         }

         m_strPathName = strPath;
      
         GetKaraokeData().Prepare();

         return true;
      }
      else
      {
         return false;
      }
   }

   void data::delete_contents() 
   {

      keeper < bool > keepWrite(&m_bWrite, true, false, true);
      GetKaraokeData().delete_contents();
      
   }

   void data::AttachPlaylist(PlaylistDoc *pdoc)
   {
      ::mediaplay::view_update_hint uh;
      uh.set_type(::mediaplay::view_update_hint::TypeAttachPlaylist);
      uh.m_pplaylistdoc = pdoc;
      m_pdocument->update_all_views(NULL, 0, &uh);
   }


   BOOL data::OpenFile(const char * bstrFilePath, BOOL bMakeVisible) 
   {
      UNREFERENCED_PARAMETER(bMakeVisible);
      string str;
      str = bstrFilePath;
      return System.open_document_file(str) != NULL;
   }

   data::e_type data::DetermineFileType(var varFile)
   {
      // quite simple by the time.

      string strPath;

      if(varFile.get_type() == var::type_propset)
      {
         if(varFile.propset()["url"].get_string().has_char())
         {
            strPath = varFile.propset()["url"];
         }
      }
      else
      {
         strPath = varFile;
      }

      if(gen::str::begins_ci(strPath, "rtp://"))
      {
         return TypeRtp;
      }
      if(strPath.Right(4).CompareNoCase(".cda") == 0)
      {
         return TypeCda;
      }
      else if(strPath.Right(4).CompareNoCase(".mp3") == 0)
      {
         return TypeMpeg;
      }
      else if(strPath.Right(4).CompareNoCase(".vqf") == 0)
      {
         return TypeTwinVQ;
      }
      else if(strPath.Right(4).CompareNoCase(".wma") == 0)
      {
         return TypeWm;
      }
      else if(strPath.Right(4).CompareNoCase(".wav") == 0)
      {
         return TypeWav;
      }
      else if(strPath.Right(4).CompareNoCase(".zip") == 0)
      {
         return TypeZip;
      }
      else if(strPath.find(".zip:") > 0)
      {
         return TypeZip;
      }
      else
      {
         return TypeUnknown;
      }

   }

   data::EMode data::DetermineMode(e_type e_type)
   {

      switch(e_type)
      {
      case TypeAiff:
      case TypeCda:
      case TypeMpeg:
      case TypeTwinVQ:
      case TypeWm:
      case TypeWav:
      case TypeRtp:
         return ModeWave;
      case TypeUnknown:
         return ModeMidi;
      default:
         return ModeNone;
      }

   }

   string data::get_path_name()
   {
      return m_strPathName;
   }

   ::userbase::document * data::get_document()
   {
      return m_pdocument;
   }

   ex1::filesp & data::GetWaveFile()
   {
      return m_fileWave;
   }

   string data::GetAnimatedTitle()
   {
      stringa stra;
   //   if(GetKaraokeData().GetStaticData().m_str2aTitle.get_count() > 0
     // && GetKaraokeData().GetStaticData().m_str2aTitle[0].has_char())
      //{
        // stra.add(GetKaraokeData().GetStaticData().m_str2aTitle[0]);
      //}
      if(get_document()->get_title().has_char())
      {
         stra.add(get_document()->get_title());
      }
      //if(GetKaraokeData().GetStaticData().m_straTitle.get_count() > 0
      //&& GetKaraokeData().GetStaticData().m_straTitle[0].has_char())
      //{
        // stra.add(GetKaraokeData().GetStaticData().m_straTitle[0]);
      //}
      return stra.implode(" - ");
   }

   bool data::is_writing()
   {
      return m_bWrite;
   }

   BOOL data::OnOpenZipFile(const char * lpszPathName)
   {
      string wstrPathName(lpszPathName);
      string wstrZipPath;
      string wstrTitle;

      int iFind = wstrPathName.find(".zip:");
      if(iFind > 0)
      {
         wstrZipPath = wstrPathName.Left(iFind + 4);
         wstrTitle = wstrPathName.Mid(iFind + 5);
         wstrTitle.replace("\\", "/");
      }
      else
      {
         wstrZipPath = wstrPathName;
      }
      const int BUFSIZE = 4096;
   //   char szTempName[MAX_PATH];
   //   char buffer[BUFSIZE]; 

   //   WCHAR szTitle1[_MAX_PATH];

      string strPathName;
      GetTempPath(BUFSIZE,   // length of the buffer
         strPathName.GetBuffer(BUFSIZE));      // buffer for path 
      strPathName.ReleaseBuffer();
      strPathName += "vmplite";

      DWORD dwAttrib = ::GetFileAttributes(strPathName);
      if(dwAttrib == -1 || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
      {
         if(dwAttrib != -1)
         {
            if(!::DeleteFile(strPathName))
               return FALSE;
         }
         if(!::CreateDirectory(strPathName, NULL))
            return FALSE;
      }

      string strFileName;
      ::GetTempFileName(
         strPathName,
         "VMP",
         0,
         strFileName.GetBuffer(MAX_PATH * 2));
      strFileName.ReleaseBuffer();

//      DWORD dw = ::GetLastError();


      if(zip::Util(get_app()).extract(lpszPathName, strFileName))
      {
         return on_open_document(strFileName);
      }
      else
      {
         return FALSE;
      }
   }


   void data::on_http_request_response(gen::signal_object * pobj)
   {
      //m_strTimePath
/*         SCAST_PTR(ca4::http::signal, psignal, pobj);

      string strResponse;

      psignal->m_memoryRet.to_string(strResponse);

      m_ptree->Parse((*psignal)()["request"], strResponse);
      m_plist->Parse(strResponse);*/
   }

} // namespace mediaplay

