#include "StdAfx.h"
#include "Configuration.h"
#include "document_manager.h"
#include "XfplayerThreadV2.h"
#include "XfplayerDoc.h"
#include "XfplayerFrame.h"
#include "XfplayerView.h"
#include "VmpPlusThread.h"
#include "KaraokeSDIFrame.h"
#include "AudioSpectrumView.h"
#include "XfplayerViewUpdateHint.h"
#include "AudioSpectrumDoc.h"
#include "AudioSpectrumView.h"
#include "XfplayerScoring.h"



// // BEGIN_MESSAGE_MAP(XfplayerDoc, ::userbase::document)
//{{AFX_MSG_MAP(XfplayerDoc)
/*ON_COMMAND(ID_VIEW_LYRICS, OnViewLyrics)
ON_UPDATE_COMMAND_UI(ID_VIEW_LYRICS, OnUpdateViewLyrics)
ON_COMMAND(ID_VIEW_MIDIEVENTS, OnViewMidievents)
ON_UPDATE_COMMAND_UI(ID_VIEW_MIDIEVENTS, OnUpdateViewMidievents)
ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTIES, OnUpdateFileProperties)
ON_COMMAND(ID_SCORING_ENABLE, OnScoringEnable)
ON_UPDATE_COMMAND_UI(ID_SCORING_ENABLE, OnUpdateScoringEnable)*/
   //}}AFX_MSG_MAP
// // END_MESSAGE_MAP()

//BEGIN_DISPATCH_MAP(XfplayerDoc, ::userbase::document)
//{{AFX_DISPATCH_MAP(XfplayerDoc)
//DISP_FUNCTION(XfplayerDoc, "OpenFile", OpenFile, VT_BOOL, VTS_BSTR VTS_BOOL)
//}}AFX_DISPATCH_MAP
//END_DISPATCH_MAP()

//BEGIN_OLECMD_MAP(XfplayerDoc, ::userbase::document)
/*ON_OLECMD_PAGESETUP()
ON_OLECMD_PRINT()*/
//END_OLECMD_MAP()


// Note: we add support for IID_IXfplayer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL spfile->

// {93535E2A-F1A0-4FD6-A54C-DADADF314C93}
static const IID IID_IXfplayer =
{ 0x93535e2a, 0xf1a0, 0x4fd6, { 0xa5, 0x4c, 0xda, 0xda, 0xdf, 0x31, 0x4c, 0x93 } };

/*
BEGIN_INTERFACE_MAP(XfplayerDoc, ::userbase::document)
INTERFACE_PART(XfplayerDoc, IID_IXfplayer, dispatch)
END_INTERFACE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// XfplayerDoc construction/destruction

XfplayerDoc::XfplayerDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   mplite::document(papp),
   mediaplay::document(papp),
   m_fileWave(papp)
{
/*   SetKaraokeData(new ikar::data());
   if(::mediaplay::document::get_data()->GetKaraokeData().IsNull())
      throw new memory_exception;

   ::mediaplay::document::get_data()->GetKaraokeData().SetInterface(&HelperGetMidiSequence());*/

   m_emode = ModeNone;
   m_edocfiletype = FileTypeNone;
   m_bPlay = false;
   
/*   m_pdoctemplateLevelMeter = new
      ::userbase::single_document_template(
      IDR_LEVELMETER,
      &typeid(CLevelMeterDoc),
      &typeid(CTransparentFrameWndV8),
      &typeid(CLevelMeterView));;*/
   
/*   m_pdoctemplatePlayer = new
      ::userbase::single_document_template(
      IDR_PLAYERV19,
      &typeid(CPlayerDoc),
      &typeid(CPlayerControlSetV19Frame),
      &typeid(CPlayerControlSetV19View));;*/
   
   m_paudiospectrumdoc = NULL;
//   m_plevelmeterdoc = NULL;
   m_pplayerdoc = NULL;
   m_pplaylistdoc = NULL;
   
   // TODO: add one-time construction code here
//   m_dProgressRate = 0.0;
   // Use OLE compound files
//   EnableCompoundFile();
   
  // EnableAutomation();
   
   
   //CMidiStdFile * pFile = &m_midiSequence.m_File;
   //   m_p2DTokens = NULL;
   
   //   m_dScoreRate = 0;


   //   m_pInfoHeader = NULL;
   //   m_pInfoHeaderLS = NULL;
   //   m_lpSongName = NULL;
   //   spfile->m_eventsTracksV1.add(new LyricEventsV1());
   //   spfile->m_eventsTracksV1.add(new LyricEventsV1());
   //   spfile->m_eventsTracksV1.get_at(0)->m_nEventType = 1;
   //   spfile->m_eventsTracksV1.get_at(1)->m_nEventType = 2;
   m_bOpening = false;
   m_bClosing = false;
   
   //    m_pSequence = new ::mus::midi::sequence();
   
   //m_pkaraokeutil = new CKaraokeUtil();
   
   //    m_pthreadV1 = ((vmsp::application *)&System)->GetHighThread();
   m_pplaylistdoc = NULL;
   m_dataid = "XfplayerDocument";
   int i = CP_OEMCP;
   //   DILoad("LyricsCodePage", i);
   //   m_dwCodePage = i;
}

XfplayerDoc::~XfplayerDoc()
{
}

BOOL XfplayerDoc::on_new_document()
{
   int i = 1;
/*   db_long_set * plongset = db()->get_db_long_set();
   data_get("ScoringEnable", i);
   EnableScoring(i != 0);*/
   
   ::ca::application * pApp = (::ca::application *) &System;
   //   pApp->SetActiveDocument(this);
   if (!::userbase::document::on_new_document())
      return FALSE;
   
   // TODO: add reinitialization code here
   // (SDI documents will reuse this document)
   
   return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// XfplayerDoc serialization

/*
void XfplayerDoc::Serialize(CArchive& ar)
{
   MMRESULT mmr;
   if (ar.IsStoring())
   {
      HelperGetMidiSequence().SaveFile(ar);
      // TODO: add storing code here
   }
   else
   {
      
      mmr = HelperGetMidiSequence().OpenFile(ar, ::mus::midi::OpenForPlaying);
      if(mmr != MMSYSERR_NOERROR)
      {
         midi_exception * pe = new midi_exception();
         pe->SetMMResult(mmr);
         ::ca::rethrow(pe);;
      }
      // TODO: add loading code here
   }
}
*/

/////////////////////////////////////////////////////////////////////////////
// XfplayerDoc diagnostics

#ifdef _DEBUG
void XfplayerDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void XfplayerDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// XfplayerDoc commands

bool XfplayerDoc::on_open_document(var varFile) 
{
   return mediaplay::document::on_open_document(varFile);
}









void XfplayerDoc::OnPositionCB()
{
   
   //   set_modified_flag(TRUE);
   //   POSITION pos = get_view_count();
   //   if(pos != NULL)
   //   {
   //      XfplayerView* pview = (XfplayerView* ) get_view(pos);
   //      pview->OnPositionCB();
   //   }
   //   m_iPlayingTokenIndex++;
   
}




void XfplayerDoc::on_close_document() 
{
   keeper<bool> closingFlagKeeper(&m_bClosing, true, false, true);
   CSingleLock slSongData(&m_csSongData, true);
   wait_cursor wait(get_app());
   
   XfplayerViewUpdateHint uh;

   uh.AddType(XfplayerViewUpdateHint::TypeCloseDocument);
   update_all_views(NULL, 0, &uh);
   
   DetachPlaylistDoc();
   
   // TODO: add your specialized code here and/or call the base class
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(papp != NULL);
   
   ::radix::thread * pThreadV2  = papp->GetThreadV2();
   ASSERT(pThreadV2 != NULL);
   
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   ASSERT(pwavein != NULL);
   
   ::mus::midi::sequence & sequence = ::mediaplay::document::get_data()->HelperGetMidiSequence();
   
   
   ((XfplayerThreadV2 *)pThreadV2)->EnableWaveInMessageTranslation(false);
//   if(m_bScoring)
  // {
    //  pwavein->Release();
//      m_bScoring = false;
   //}
   delete_contents();
   //    GetMidiSequence()->CloseFile();
   slSongData.Unlock();
   closingFlagKeeper.KeepAway();
   ::userbase::document::on_close_document();
}

void XfplayerDoc::delete_contents() 
{
   ::mediaplay::document::delete_contents();
}

/*void XfplayerDoc::SetApproximatePosition(double rate)
{
m_csMidi.Lock();
m_pmidiplayer->PostThreadMessage(WM_USER + 100, (WPARAM) rate, 0);

  XfplayerView * pview =  GetLyricView();
  if(pview != NULL)
  pview->SetPlayingPosition(rate);
  m_csMidi.Unlock();
  
}*/

void XfplayerDoc::ClearTokens()
{
   //   stringa *pTokens;
   //   int i;//, j;
   //   m_csObjects.Lock()
   //   for(i = 0; i < m_str2aRawTokens.get_size(); i++)
   //   {
   //        delete m_str2aRawTokens.element_at(i);
   //      pTokens->remove_all();
   //   }
   //    m_str2aRawTokens.remove_all();
   
   //    if(GetMidiPlayer())
   //  {
//   ::mediaplay::document::get_data()->HelperDeleteContents();
   //}
   //   m_csObjects.Unlock();
   //   m_2DTokensMillis.remove_all();
   //   spfile->m_eventsTracksV1.add(new LyricEventsV1());
   //   spfile->m_eventsTracksV1.add(new LyricEventsV1());
   //   spfile->m_eventsTracksV1.get_at(0)->m_nEventType = 1;
   
}

/*    while(spfile->GetTracks().m_tkPosition == 0)
{
smfrc = spfile->GetNextEvent((CMidiEvent *)&event, tkMax);
if (::mus::midi::Success != smfrc)
{
/* smfGetNextEvent doesn't set this because smfSeek uses it
** as well and needs to distinguish between reaching the
** seek point and reaching end-of-spfile->
**
** To the ::fontopus::user, however, we present the selection between
** their given tkBase and tkEnd as the entire file, therefore
** we want to translate this into EOF.
*/
/*            if (SMF_REACHED_TKMAX == smfrc)
{
spfile->m_fdwSMF |= SMF_F_EOF;
}

  TRACE1("smfReadEvents: smfGetNextEvent() -> %u", (UINT)smfrc);
  break;
  }
  
    
      if ((MIDI_META == EVENT_TYPE(event)) &&
          (MIDI_META_XF_LYRICS_HEADER == EVENT_META_TYPE(event)))
          {
          string str((const char *) event.hpbParm, event.cbParm);
          if(str.Mid(0, 5) == "$Lyrc")
          {
          int iLo;
          int iHi;
          iLo = str.find(":", 0);
          if(iLo < 0)
          goto XF_Lyrics_Parse_End;
          iHi = str.find(":", iLo + 1);
          if(iHi < 0)
          goto XF_Lyrics_Parse_End;
          iLo = iHi;
          iHi = str.find(":", iLo + 1);
          if(iHi < 0)
          goto XF_Lyrics_Parse_End;
          m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
          XF_Lyrics_Parse_End:;
          
            }
            }
    }*/





XfplayerView * XfplayerDoc::GetLyricView()
{
   return get_typed_view < XfplayerView > ();   
}


//void XfplayerDoc::SetScoreRate(double dScoreRate)
//{
//   m_dScoreRate = dScoreRate;
//}





XFInfoHeaderLSArray * XfplayerDoc::GetInfoHeadersLS()
{
   return &::mediaplay::document::get_data()->HelperGetXFInfoHeaderSet()->m_xfaInfoHeaderLS;
}


BOOL XfplayerDoc::on_save_document(const char * lpszPathName) 
{
   if(lpszPathName == NULL)
      return TRUE;
   keeper<bool> savingFlagKeeper(&::mediaplay::document::get_data()->m_bSavingHelper, true, false, true);
   
   string strPathName(lpszPathName);
   if(strPathName.Right(4).CompareNoCase(".mid") != 0)
   {
      // linux System.simple_message_box(IDS_ERROR_SAVEASXFONLY);
      System.simple_message_box(NULL, "It is only possible to save as XF file format.");
      return FALSE;
   }
   ex1::file_exception_sp fe;
   MidiTrack * pTrack;
   ::mus::midi::sequence & sequence = ::mediaplay::document::get_data()->HelperGetMidiSequence();
   ::mus::midi::file & file = sequence.GetFile(); 
   if(is_modified())
   {
      if(NULL != (pTrack = file.GetTracks().seek(::mus::midi::SeekXFInfoHeader)))
      {
         MidiEventV007 midiEvent(&file, pTrack);
         midiEvent.CreateXFInfoHeaderEvent(0, &::mediaplay::document::get_data()->HelperGetXFInfoHeaderSet()->m_xfInfoHeader);
         midiEvent.SetDelta( pTrack->GetEvent().GetDelta());
         //file.ToWorkStorage();
         file.ReplaceSameDeltaEvent(midiEvent);
         //            file.WorkMergeTracks();
         //          file.WriteHeader(&mfh);
         //        file.Format0();
         
      }
      else
      {
         ASSERT(FALSE);
      }
      
   }
   
   MIDIFILEHDR fileHdr;
   
   int iTrackCount = 0;
   for(int i = 0; i < file.GetTracks().GetTrackCount(); i++)
   {
      MidiTrackBase * pTrackBase = file.GetTracks().TrackAt(i);
      if(pTrackBase->get_type() == MidiTrackBase::TypeMidi)
      {
         MidiTrack * pTrack = (MidiTrack *) pTrackBase;
         CHUNKHDR FAR * pCh = (CHUNKHDR FAR *)pTrack->GetTrackImage();
         if (pCh->fourccType == FOURCC_MTrk)
            iTrackCount++;
         
      }
      
   }
   fileHdr.wFormat = WORDSWAP(0);
   fileHdr.wDivision = m_mfh.wDivision ;
   fileHdr.wTracks = WORDSWAP(iTrackCount) ;
   
   file.WorkMergeTracks();
   
   
   
   file.WriteHeader(&fileHdr);
   
//   file.WorkBuildIndex();
   file.Format0();
   
   
   try
   {
      //m_pmidiplayer->SaveFile(lpszPathName);
      //::userbase::document::on_save_document(lpszPathName);
      ::userbase::document::on_save_document(lpszPathName);
   }
   catch(midi_exception *pe)
   {
      pe->Delete();
   }
   
   memcpy(&m_mfh, file.m_pFileHeader, sizeof(MIDIFILEHDR));
   file.GetTracks().ExpandTrack(0);
   file.ToWorkStorage();
   
   set_modified_flag(FALSE);     // back to unmodified
   
   return TRUE;        // success
}


UINT XfplayerDoc::GetMidiSequenceState()
{
   return ::mediaplay::document::get_data()->HelperGetMidiSequence().GetState();
}




void XfplayerDoc::OnViewLyrics() 
{
   // TODO: add your command handler code here
   char lpszModuleFilePath[MAX_PATH + 1];
   GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
   char lpszModuleFolder[MAX_PATH + 1];
   LPTSTR lpszModuleFileName;
   GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
   string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
   string strFolder;
   strFolder = strModuleFolder;
   string str;
   throw not_implemented_exception();
   //str.load_string(IDS_FOLDER_LYRICS);
   strFolder += str;
   System.dir().mk(strFolder);
   if(!System.dir().is(strFolder))
   {
      System.simple_message_box(NULL, "Não foi possível criar diretório de letras de músicas");
//      System.simple_message_box("Não foi possível criar diretório de letras de músicas. Existe um outro arquivo com mesmo nome que não pôde ser apagado.");
   }
   
   string strPath;
   string strFile;
   //if(GetMidiSequence()->m_strFile.is_empty())
   if(::mediaplay::document::get_data()->get_path_name().is_empty())
   {
      strFile = "Sem Título";
   }
   else
   {
      char lpszFolder[MAX_PATH + 1];
      LPTSTR lpszFileName;
      GetFullPathName(::mediaplay::document::get_data()->get_path_name(), MAX_PATH + 1, lpszFolder, &lpszFileName);
      strFile = lpszFileName;
   }
   int i = 1;
   strPath.Format("%s\\%s.txt", strFolder, strFile);
   while(true)
   {
      if(!System.file().exists(strPath))
         break;
      strPath.Format("%s\\%s[%d].txt", strFolder, strFile, i);
      i++;
   }
   ex1::filesp spfile(get_app());
   
   spfile->open(
      strPath,
      ::ex1::file::mode_create |
      ::ex1::file::mode_write |
      ::ex1::file::shareDenyWrite);
   
   string wstrText = GetLyricView()->GetPlainTextV001();
   WCHAR wchBom = 0xFEFF;
   spfile->write(&wchBom, sizeof(wchBom));
   spfile->write(wstrText, wstrText.get_length() );
   spfile->Flush();
   spfile->close();
   
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   
   papp->OpenTextFile(strPath);
   
   /*    ShellExecute(
   GetLyricView()->m_hWnd,
   "open",
   strPath,
   NULL,
   strFolder,
   SW_SHOWNORMAL);*/
   
}

void XfplayerDoc::OnUpdateViewLyrics(cmd_ui * pcmdui) 
{
   pcmdui->Enable(::mediaplay::document::get_data()->HelperGetMidiSequence().IsOpened());
}



bool XfplayerDoc::IsOpening()
{
   return m_bOpening;
}



int XfplayerDoc::GetNextSong()
{
   if(m_dwaSongsCodes.get_size() <= 0)
      return -1;
   else
   {
      int i = m_dwaSongsCodes.get_at(0);
      m_dwaSongsCodes.remove_at(0);
      return i;
   }
}

/*void XfplayerDoc::UpdateProgress(::userbase::view * pview)
{
   XfplayerViewUpdateHint uh;
   uh.GetUpdateFlags().signalize(XfplayerViewUpdateHint::UpdateProgress);
   update_all_views(pview, 0L, &uh);
   
}*/


bool XfplayerDoc::do_save(const char * lpszPathName, bool bReplace)
// Save the document data to a file
// lpszPathName = path name where to save document file
// if lpszPathName is NULL then the ::fontopus::user will be prompted (SaveAs)
// note: lpszPathName can be different than 'm_strPathName'
// if 'bReplace' is TRUE will change file name if successful (SaveAs)
// if 'bReplace' is FALSE will not change path name (SaveCopyAs)
{
   string newName = lpszPathName;
   if (newName.is_empty())
   {
      document_template * ptemplate = get_document_template();
      ASSERT(ptemplate != NULL);
      
      newName = ::userbase::document::m_strPathName;
      if (bReplace && newName.is_empty())
      {
         newName = m_strTitle;
         // check for dubious filename
         int iBad = newName.FindOneOf(" #%;/\\");
         if (iBad != -1)
            newName.ReleaseBuffer(iBad);
         
         // append the default suffix if there is one
         string strExt;
         if (ptemplate->GetDocString(strExt, ::userbase::document_template::filterExt) &&
            !strExt.is_empty())
         {
            ASSERT(strExt[0] == '.');
            
            int nSemi;                       //added
            if(nSemi = strExt.find(';'))   //added
               strExt = strExt.Left(nSemi);     //added
            
            newName += strExt;
         }
      }
      
/*      XfplayerSaveFileDialog sfd;
      
      if (!sfd.do_prompt_file_name(newName,
         bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
         OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, dynamic_cast < ::userbase::document_template * > (ptemplate)))
         return FALSE;       // don't even attempt to save*/
   }
   
   wait_cursor wait(get_app());
   
   if (!on_save_document(newName))
   {
      if (lpszPathName == NULL)
      {
         // be sure to delete the file
         try
         {
            //System.file().::remove(newName);
         }
         catch(base_exception * pe)
         {
            TRACE0("Warning: failed to delete file after failed SaveAs.\n");
            pe->Delete();
         }
         
      }
      return FALSE;
   }
   
   // reset the title and change the document name
   if (bReplace)
      set_path_name(newName);
   
   return TRUE;        // success
}

void XfplayerDoc::OnViewMidievents() 
{
   // TODO: add your command handler code here
   // create frame - set as main document frame
   //   BOOL bAutoDelete = pdocument->m_bAutoDelete;
   
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   pApp->GetMidiDocTemplate()->open_document_file(::mediaplay::document::get_data()->get_path_name());
   
   //    XfplayerFrame * pFrame = new XfplayerFrame();
   //  create_context context;
   //context.m_pCurrentDoc = this;
   //    context.m_pCurrentFrame = pFrame;
   //  context.m_pLastView = GetLyricView();
   //context.m_pNewDocTemplate = NULL;
   //    context.m_typeinfoNewView = &typeid(CMidiEventsView);
   //  pFrame->LoadFrame(IDR_MIDIEVENTS, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
   //    System.GetMainWnd(), &context);
}

void XfplayerDoc::OnUpdateViewMidievents(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

//bool XfplayerDoc::IsSaving()
//{
//  return m_bSaving;
//}

bool XfplayerDoc::IsClosing()
{
   return m_bClosing;
}

void XfplayerDoc::OnFileProperties() 
{
   // TODO: add your command handler code here
   
/*     CXfPropertiesDialog propertiesDialog(this);
   propertiesDialog.DoModal();*/
   
}

void XfplayerDoc::OnUpdateFileProperties(cmd_ui * pcmdui) 
{
   ASSERT(this != NULL);
   pcmdui->Enable(
      GetMidiSequenceState() !=
      ::mus::midi::sequence::StatusNoFile);
}




afx_msg LRESULT XfplayerDoc::OnXfplayerDocMessage(WPARAM wParam, LPARAM lParam)
{
   if(wParam == 1)
   {
      LPXFPLAYERDOCINIT lpdocinit = (LPXFPLAYERDOCINIT) lParam;
      //        m_pthreadV1 = lpdocinit->pthreadV1;
   }
   
   return 0;
}



bool XfplayerDoc::Attach(PlaylistDoc *pplaylistdoc)
{
   if(m_pplaylistdoc != NULL)
   {
      DetachPlaylistDoc();
   }
   m_pplaylistdoc = pplaylistdoc;
   pha(PlaylistDoc)::add(pplaylistdoc);
   XfplayerViewUpdateHint uh;
   uh.AddType(XfplayerViewUpdateHint::UpdateOnAttachPlaylistDoc);
   update_all_views(NULL, 0, &uh);
   return true;

}

PlaylistDoc * XfplayerDoc::DetachPlaylistDoc()
{
   PlaylistDoc * lpPlaylistDoc = m_pplaylistdoc;
   if(m_pplaylistdoc != NULL)
   {
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::UpdateOnAttachPlaylistDoc);
      update_all_views(NULL, 0, &uh);
      pha(PlaylistDoc)::remove(m_pplaylistdoc);
      m_pplaylistdoc = NULL;
   }
   return lpPlaylistDoc;
}


PlaylistDoc * XfplayerDoc::GetPlaylistDoc()
{
   return m_pplaylistdoc;
}

void XfplayerDoc::OnPointerClear(PlaylistDoc * pdoc)
{
   if(pdoc == m_pplaylistdoc)
   {
      DetachPlaylistDoc();
   }
   
}


/*void XfplayerDoc::OnDeactivate() 
{
   m_pInPlaceFrame->SendMessage(WM_USER, 173, 0);   
   ::userbase::document::OnDeactivate();
}*/

::userbase::single_document_template * XfplayerDoc::GetAudioSpectrumDocTemplate()
{
   return ((dynamic_cast < vmsp::application *> (get_app())))->GetDocumentManager().m_pdoctemplateAudioSpectrum;
}

/*::userbase::single_document_template * XfplayerDoc::GetLevelMeterDocTemplate()
{
   return m_pdoctemplateLevelMeter;
}*/

AudioSpectrumDoc * XfplayerDoc::OpenAudioSpectrumDoc(XfplayerView * pxfplayerview, bool bMakeVisible)
{
   if(m_paudiospectrumdoc != NULL)
   {
      return m_paudiospectrumdoc;
   }
   else
   {
      ASSERT(GetAudioSpectrumDocTemplate()!= NULL);
      m_paudiospectrumdoc = dynamic_cast < AudioSpectrumDoc * > (GetAudioSpectrumDocTemplate()->open_document_file(NULL, bMakeVisible));
      if(m_paudiospectrumdoc == NULL)
         return NULL;
      ::view * pview = m_paudiospectrumdoc->get_view();
      simple_frame_window * pwnd = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
      pwnd->m_pupdowntarget = dynamic_cast < window_frame::UpDownTarget * > (pxfplayerview);
      pwnd->window_frame::CWorkSetDownUpInterface::m_iType = vmsp::ViewAudioSpectrum;
      pwnd->WfiDown();
      pha(AudioSpectrumDoc)::add(m_paudiospectrumdoc);
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
/*      CGenericViewUpdateHint uh(8792, 0, &papp->GetAudioWaveCentral().GetWaveIn()->GetBuffer());
      m_paudiospectrumdoc->update_all_views(NULL, 0, &uh);*/
      return m_paudiospectrumdoc;
   }
}

/*CLevelMeterDoc * XfplayerDoc::OpenLevelMeterDoc(bool bMakeVisible)
{
   if(m_plevelmeterdoc != NULL)
   {
      return m_plevelmeterdoc;
   }
   else
   {
      ASSERT(m_pdoctemplateLevelMeter!= NULL);
      m_plevelmeterdoc = (CLevelMeterDoc *) m_pdoctemplateLevelMeter->open_document_file(NULL, bMakeVisible);
      pointer_array<CLevelMeterDoc>::add((pointer <CLevelMeterDoc > *)m_plevelmeterdoc);
/*      CGenericViewUpdateHint uh(8791, 0, &HelperGetMidiSequence());
      m_plevelmeterdoc->update_all_views(NULL, 0, &uh);*/
   /*   return m_plevelmeterdoc;
   }
   
}*/

AudioSpectrumDoc * XfplayerDoc::GetAudioSpectrumDoc()
{
   return m_paudiospectrumdoc;
}

/*CLevelMeterDoc * XfplayerDoc::GetLevelMeterDoc()
{
   return m_plevelmeterdoc;
}*/

bool XfplayerDoc::IsAudioSpectrumOpened()
{
   return m_paudiospectrumdoc != NULL;
}

/*bool XfplayerDoc::IsLevelMeterOpened()
{
   return m_plevelmeterdoc != NULL;
}*/


AudioSpectrumView * XfplayerDoc::GetAudioSpectrumView()
{
   return m_paudiospectrumdoc->get_typed_view < AudioSpectrumView > ();
}

/*CLevelMeterView * XfplayerDoc::GetLevelMeterView()
{
   return (CLevelMeterView *) 
      GetDocumentFirstView(
      m_plevelmeterdoc,
      &typeid(CLevelMeterView));
   
}*/

simple_frame_window * XfplayerDoc::GetAudioSpectrumFrame()
{
   ::userbase::view * pview = GetAudioSpectrumView();
   if(pview == NULL)
      return NULL;
   else
   {
      frame_window * pframe = pview->GetParentFrame();
      if(pframe != NULL
         && base < simple_frame_window >::bases(pframe))
      {
         return dynamic_cast < simple_frame_window * > (pframe);
      }
      else
         return NULL;
   }
   
}

/*CTransparentFrameWndV8 * XfplayerDoc::GetLevelMeterFrame()
{
   ::userbase::view * pview = GetLevelMeterView();
   if(pview == NULL)
      return NULL;
   else
   {
      simple_frame_window * pframe = pview->GetParentFrame();
      if(pframe != NULL
         && base < CTransparentFrameWndV8 >::bases(pframe))
      {
         return (CTransparentFrameWndV8 *) pframe;
      }
      else
         return NULL;
   }
}*/

void XfplayerDoc::OnPointerClear(AudioSpectrumDoc * pdoc)
{
   ASSERT(pdoc == m_paudiospectrumdoc);
   m_paudiospectrumdoc = NULL;
   
}

/*void XfplayerDoc::OnPointerClear(CLevelMeterDoc *pdoc)
{
   ASSERT(pdoc == m_plevelmeterdoc);
   m_plevelmeterdoc = NULL;
   
}*/

void XfplayerDoc::CloseAllAudioSpectrumDocuments()
{
   GetAudioSpectrumDocTemplate()->close_all_documents(FALSE);
}

/*void XfplayerDoc::CloseAllLevelMeterDocuments()
{
   m_pdoctemplateLevelMeter->close_all_documents(FALSE);
}*/


BOOL XfplayerDoc::open_document_file(const VARIANT FAR& varwszFilePath) 
{
   string str;
   ASSERT(varwszFilePath.vt == VT_BSTR);
   str = varwszFilePath.bstrVal;
   return get_document_template()->open_document_file(str, true) != NULL;
   
   //return TRUE;
}

BOOL XfplayerDoc::OpenFile(const char * bstrFilePath, BOOL bMakeVisible) 
{
   string str;
   str = bstrFilePath;
   return get_document_template()->open_document_file(str, true) != NULL;
}

CPlayerDoc * XfplayerDoc::GetPlayerDoc()
{
   return m_pplayerdoc;
}

CPlayerDoc * XfplayerDoc::OpenPlayerDoc(bool bMakeVisible)
{
   if(m_pplayerdoc != NULL)
   {
      return m_pplayerdoc;
   }
   else
   {
      ASSERT(m_pdoctemplateLevelMeter!= NULL);
      m_pplayerdoc = (CPlayerDoc *) m_pdoctemplatePlayer->open_document_file(NULL, bMakeVisible);
      if(m_pplayerdoc != NULL)
      {
/*         m_pplayerdoc->SetXfplayerDoc(this);
         pointer_array<CPlayerDoc>::add(m_pplayerdoc);*/
      }
      return m_pplayerdoc;
   }
}

/*void XfplayerDoc::OnPointerClear(CPlayerDoc *pdoc)
{
   ASSERT(m_pplayerdoc == pdoc);
   m_pplayerdoc = NULL;
}*/

/*CPlayerControlSetV19Frame * XfplayerDoc::GetPlayerControlSetV19Frame()
{
   ::userbase::view * pview = GetPlayerControlSetV19View();
   if(pview == NULL)
      return NULL;
   else
   {
      simple_frame_window * pframe = pview->GetParentFrame();
      if(pframe != NULL
         && base < CPlayerControlSetV19Frame >::bases(pframe))
      {
         return (CPlayerControlSetV19Frame *) pframe;
      }
      else
         return NULL;
   }
   
}

CPlayerControlSetV19View * XfplayerDoc::GetPlayerControlSetV19View()
{
   return (CPlayerControlSetV19View *) 
      GetDocumentFirstView(
      m_pplayerdoc,
      &typeid(CPlayerControlSetV19View));
   
}*/

bool XfplayerDoc::IsPlayerDocOpened()
{
   return m_pplayerdoc != NULL;
}

/*
bool XfplayerDoc::IsPlayerControlSetV19ViewOpened()
{
   return GetPlayerControlSetV19View() != NULL;
}
*/



bool XfplayerDoc::ShouldShow(EShow eshow)
{
   return m_eshowaVisible.contains(eshow);
}

void XfplayerDoc::Show(EShow eshow, bool bShow)
{
   if(bShow)
   {
      m_eshowaVisible.add_unique(eshow);
   }
   else
   {
      m_eshowaVisible.remove(eshow);
   }
}



void XfplayerDoc::DBSaveSongEncoding(const char * lpszPathName)
{
   string strPathName(lpszPathName);
   if(strPathName.is_empty())
   {
      strPathName = "Default";
   }
   if(!strPathName.is_empty())
   {
      string str;
      str.Format("%s.Encoding", strPathName);
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
      data_set(str, (int) papp->GetKaraokeEncoding());
   }
}

void XfplayerDoc::DBLoadSongEncoding(const char * lpszPathName)
{
   ASSERT(lpszPathName != NULL);
   string strPathName(lpszPathName);
   ASSERT(!strPathName.is_empty());
   if(!strPathName.is_empty())
   {
      string str;
      str.Format("%s.Encoding", strPathName);
      int i = 0;
      if(data_get(str, i))
      {
         vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
         papp->SetKaraokeEnconding((DWORD) i);
      }
   }
}

DWORD XfplayerDoc::GetSongEncoding()
{
/*   if(!get_path_name().is_empty())
{
string str;
str.Format("%s.Encoding", get_path_name());
int i;
if(DILoad(str, i))
{
return (DWORD) i;
}
}*/
   
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   return papp->GetKaraokeEncoding();
}

/*void XfplayerDoc::SetSongEncoding(DWORD dwCodePage)
{
vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
papp->SetKaraokeEnconding(dwCodePage);
DBSaveSongEncoding();
update_all_views(NULL, 1314151617);
}*/

void XfplayerDoc::OnKaraokeEncodingChange()
{
   if(!IsOpening())
   {
      DBSaveSongEncoding(::mediaplay::document::get_data()->get_path_name());
   }
   XfplayerViewUpdateHint uh;
   uh.AddType(XfplayerViewUpdateHint::UpdateKaraokeEncoding);
   update_all_views(NULL, 0, &uh);
   
}







int XfplayerDoc::GetGuessingMelodyTrack()
{
   return m_iGuessMelodyTrack;
}

void XfplayerDoc::SetLyricDelay(int iDelay)
{
   ::mediaplay::document::get_data()->HelperGetMidiSequence().GetFile().GetTracks().SetLyricDelay(iDelay);
   GetLyricView()->m_lpbouncingball->m_iDelay = iDelay;
   
}

void XfplayerDoc::OnChangeMidiPlayerTempoShift()
{
   update_all_views(NULL);
}
void XfplayerDoc::OnChangeMidiPlayerTranspose()
{
   update_all_views(NULL);
}

::radix::thread * XfplayerDoc::GetMidiPlayerCallbackThread()
{
/*   return &gen::CHighThreadContainer::AppGetHighThread();*/
   return NULL;
}

::radix::thread * XfplayerDoc::HelperGetMidiPlayerCallbackThread()
{
   //return &gen::CHighThreadContainer::AppGetHighThread();
   return NULL;
}


/*void XfplayerDoc::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   XfplayerViewUpdateHint uh;

   uh.m_pevents = pevents;
   
   uh.AddType(XfplayerViewUpdateHint::MidiLyricEvent);
   update_all_views(NULL, 0L, &uh);

}*/



XfplayerDoc::EMode XfplayerDoc::GetMode()
{
   return m_emode;
}



ex1::filesp & XfplayerDoc::GetWaveFile()
{
   return m_fileWave;
}


void XfplayerDoc::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   ::mus::midi::sequence & seq = pdata->m_pplayer->GetSequence();
   ASSERT(&seq == &::mediaplay::document::get_data()->HelperGetMidiSequence());
   
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(papp != NULL);
   
   
   ::radix::thread * pThreadV2  = papp->GetThreadV2();
   ASSERT(pThreadV2 != NULL);
   
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   
   m_evMMDone.SetEvent();
}


void XfplayerDoc::OnMmsgDone(::mus::midi::sequence *pseq, LPMIDIDONEDATA lpmdd)
{
   ASSERT(pseq == &::mediaplay::document::get_data()->HelperGetMidiSequence());
   
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(papp != NULL);
   
   ::radix::thread * pThreadV2  = papp->GetThreadV2();
   ASSERT(pThreadV2 != NULL);
   
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   ASSERT(pwavein != NULL);

   
   m_evMMDone.SetEvent();
   
}

void XfplayerDoc::on_delete(::ca::ca * pca)
{
}
