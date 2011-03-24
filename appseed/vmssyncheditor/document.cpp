#include "StdAfx.h"




/////////////////////////////////////////////////////////////////////////////
// document

/*IMPLEMENT_DYNCREATE(document, Document)

BEGIN_MESSAGE_MAP(document, Document)
	//{{AFX_MSG_MAP(document)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PLAY, OnUpdateExecutePlay)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_STOP, OnUpdateExecuteStop)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()
*/
//BEGIN_DISPATCH_MAP(document, Document)
	//{{AFX_DISPATCH_MAP(document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
//END_DISPATCH_MAP()

// Note: we add support for IID_IVmssyncheditor to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3B4D4283-AE8A-40D4-AAFB-BB509183EA00}
//static const IID IID_IVmssyncheditor =
//{ 0x3b4d4283, 0xae8a, 0x40d4, { 0xaa, 0xfb, 0xbb, 0x50, 0x91, 0x83, 0xea, 0x0 } };

//BEGIN_INTERFACE_MAP(document, Document)
	//INTERFACE_PART(document, IID_IVmssyncheditor, Dispatch)
//END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// document construction/destruction

document::document()
{
	// TODO: add one-time construction code here
   m_iCurrentToken = -1;
   m_iLyricTrack = -1;
   m_bMuteAll = false;
	EnableAutomation();

	AfxOleLockApp();

   m_pmediaviewdata = new _vmsmediaplay::MediaViewData();
   m_pmediaviewdata->m_pdocument = this;
}

document::~document()
{
	AfxOleUnlockApp();
}

BOOL document::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// document serialization

void document::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// document diagnostics

#ifdef _DEBUG
void document::AssertValid() const
{
	Document::AssertValid();
}

void document::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// document commands

/*CMidiSequence & document::GetMidiSequence()
{
   return m_midisequence;
}*/

bool document::OnSetData(int iConfigurationId, int iLine, int iColumn, COleVariant & var, data_update_hint * puh)
{
   if(iConfigurationId == 2)
   {
      ASSERT(var.vt == VT_BSTR
         || var.vt == VT_EMPTY);
      string str;
      if(var.vt == VT_BSTR)
      {
         str = var.bstrVal;
      }
      str.Replace(" ", "^");
      GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0][iLine] = str;
   }
   else if(iConfigurationId == 0
      || iConfigurationId == 1)
   {
      ASSERT(var.vt == VT_I4);
      EventsTracksV1 * peventsarray
      = &GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventstracks;

      LyricEventsV2 * pevents;
      if(peventsarray == NULL ||
         peventsarray->get_size() <= 0)
         pevents = NULL;
      else
      {
         pevents = (LyricEventsV2 *) peventsarray->element_at(0);
         ASSERT(pevents != NULL);
         ASSERT(pevents->GetClassOrder() == 2);
      }

      pevents->m_tkaTokensPosition[iLine] = var.intVal;
   }
   return true;
}

bool document::GetData(
   int iConfigurationId, 
   int iLine, 
   int iColumn, 
   COleVariant & var)
{
   WString wstr;
   if(iConfigurationId == 0)
   {
      EventsTracksV1 * peventsarray
         = &GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventstracks;

      LyricEventsV2 * pevents;
      if(peventsarray == NULL ||
         peventsarray->get_size() <= 0)
         pevents = NULL;
      else
      {
         pevents = (LyricEventsV2 *) peventsarray->element_at(0);
         ASSERT(pevents != NULL);
         ASSERT(pevents->GetClassOrder() == 2);
      }

      wstr.Format(L"%d", pevents->m_tkaTokensPosition[iLine]);
   }
   else if(iConfigurationId == 2)
   {
      International::ACPToUnicode(wstr, GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0][iLine]);
   }

   // Free up previous VARIANT
	var.Clear();
	var.vt = VT_BSTR;
	var.bstrVal = wstr.AllocSysString();
	if (var.bstrVal == NULL)
		AfxThrowMemoryException();

	return true;
}


void document::OnExecutePlay() 
{
	UpdateAllViews(NULL, 123, 0);
	
}

void document::OnUpdateExecutePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	
}

void document::OnExecuteStop() 
{
	UpdateAllViews(NULL, 124, 0);
	
}

void document::OnUpdateExecuteStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	
}

void document::GetPosition(imedia::Position &position)
{
   ikar::KaraokeData & data = GetMediaViewData()->GetKaraokeData();
   ikar::KaraokeStaticData & staticdata = data.GetStaticData();
   ikar::KaraokeDynamicData & dynamicdata = data.GetDynamicData();
   ikar::KaraokeInterface * pinterface = data.GetInterface();




   
   
   
   
   
   LyricEventsV2 * pevents = NULL;
   LyricEventsV2 * peventsBB = NULL;
   if(staticdata.m_eventstracksV002.get_size() > 0)
   {
      pevents = (LyricEventsV2 *) staticdata.m_eventstracksV002.operator [](0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   if(staticdata.m_eventsTracksForBouncingBall.get_size() > 0)
   {
      peventsBB = (LyricEventsV2 *) staticdata.m_eventsTracksForBouncingBall.operator [](0);
      ASSERT(peventsBB != NULL);
      ASSERT(peventsBB->GetClassOrder() == 2);
   }
   if(pevents == NULL)
      return;


   if(m_iCurrentToken < 0)
   {
      position = 0;
   }
   else if(m_iCurrentToken + 1 >= pevents->m_tkaTokensPosition.get_size())
   {
      position = 0x7fffffff;
   }
   else
   {
      position = pevents->m_tkaTokensPosition[m_iCurrentToken + 1];
   }
}

void document::OnFileExport() 
{
   CXfplayerSaveFileDialog dlgFile;

   string str;
	
	dlgFile.DoPromptFileName(
      str,
      IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_EXPLORER, false, NULL);

   ikar::KaraokeData & data = GetMediaViewData()->GetKaraokeData();
   ikar::KaraokeStaticData & staticdata = data.GetStaticData();
   ikar::KaraokeDynamicData & dynamicdata = data.GetDynamicData();
   ikar::KaraokeInterface * pinterface = data.GetInterface();




   
   
   
   
   
   LyricEventsV2 * pevents = NULL;
   LyricEventsV2 * peventsBB = NULL;
   if(staticdata.m_eventstracksV002.get_size() > 0)
   {
      pevents = (LyricEventsV2 *) staticdata.m_eventstracksV002.operator [](0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   if(staticdata.m_eventsTracksForBouncingBall.get_size() > 0)
   {
      peventsBB = (LyricEventsV2 *) staticdata.m_eventsTracksForBouncingBall.operator [](0);
      ASSERT(peventsBB != NULL);
      ASSERT(peventsBB->GetClassOrder() == 2);
   }
   if(pevents == NULL)
      return;

   MidiFile & midifile = GetMediaViewData()->GetMidiSequence().GetFile();


   CXFInfoHeader xfinfoheader;

   midifile.WorkWriteXFTracks(
      staticdata.m_str2aRawTokens[0], 
      pevents->m_tkaTokensPosition,
      xfinfoheader);

   midifile.FromWorkStorage();

   midifile.MergeTracks();

   try
   {
      CFile file(str, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);

      file.Write(midifile.GetImage(), midifile.GetImageSize());

  	}
   catch(...)
   {
   }

//   midifile.ToWorkStorage();
}

void document::OnSelectTrack(int iTrack)
{
   if(m_bMuteAll)
   {
      GetMediaViewData()->GetMidiSequence().GetFile().MuteAll(false);
      m_bMuteAll = false;
   }
   else
   {
      m_bMuteAll = true;
      GetMediaViewData()->GetMidiSequence().GetFile().MuteAll(true, iTrack);
      m_iLyricTrack = iTrack;
   }
      
   UpdateAllViews(NULL, 1017);
   
   //GetMediaViewData()->GetMidiSequence().Prepare(iTrack, GetMediaViewData()->GetKaraokeData());
   //UpdateAllViews(NULL, 100);
}

void document::OnTrackSelectApply()
{
   GetMediaViewData()->GetKaraokeData().DeleteContents();
   GetMediaViewData()->GetMidiSequence().Prepare(m_iLyricTrack, GetMediaViewData()->GetKaraokeData());
   UpdateAllViews(NULL, 100);

}
