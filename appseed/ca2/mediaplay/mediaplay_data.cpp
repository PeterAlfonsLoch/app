#include "StdAfx.h"

namespace mediaplay
{

   data::data(document * pdocument) :
      ::ca::ca(pdocument->get_app()),
      m_pdocument(pdocument),
      MidiDocHelper(pdocument->get_app()),
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

      single_lock slKaraokeData(&data.m_mutex, FALSE);
      if(!slKaraokeData.lock(millis(1984 * 5)))
         return FALSE;

      e_type e_type = DetermineFileType(varFile);

      if(e_type == TypeZip)
      {
         return OnOpenZipFile(varFile) != FALSE;
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

         ::ex1::file_exception_sp e;
         ::ex1::filesp spfile = Application.get_file(varFile, ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary | ::ex1::file::hint_unknown_length_supported, &e);
         if(spfile.is_null())
         {
            throw e;
            return false;
         }

         m_spfile = spfile;


         m_spfile->seek_to_begin();

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
               command.OpenRtpFile(m_spfile);
            }
            else
            {
               bool bSeekable = !(gen::str::begins(strPath, "http://") || gen::str::begins(strPath, "https://")
                  || gen::str::begins(strPath, "uifs://") || gen::str::begins(strPath, "fs://")
                  || varFile.ca2 < ::sockets::http::file > () != NULL
                  || varFile.propset()["file"].ca2 < ::sockets::http::file >() != NULL
                  || varFile.propset()["file"].ca2 < ::ex1::file >() != NULL);
               command.OpenFile(m_spfile, bSeekable);
            }
            pwaveplayer->ExecuteCommand(command);
         }

         string str;
         string strFile;

         if(m_etype != data::TypeRtp)
         {
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

      if(ikar::data_container::m_pdata != NULL)
      {
         try
         {
            GetKaraokeData().delete_contents();
         }
         catch(...)
         {
         }
      }

   }

   void data::AttachPlaylist(::mediaplaylist::document *pdoc)
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
      ::ca::create_context_sp cc(get_app());
      cc->m_spCommandLine->m_varFile = str;
      return System.open_document_file(cc) != NULL;
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

      strPath.trim("\"'");

      if(gen::str::begins_ci(strPath, "rtp://")
      || gen::str::begins_ci(strPath, "rtprx://"))
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

   ex1::file * data::get_file()
   {
      return m_spfile;
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
      UNREFERENCED_PARAMETER(pobj);
      //m_strTimePath
/*         SCAST_PTR(ca4::http::signal, psignal, pobj);

      string strResponse;

      psignal->m_memoryRet.to_string(strResponse);

      m_ptree->Parse((*psignal)()["request"], strResponse);
      m_plist->Parse(strResponse);*/
   }

} // namespace mediaplay

