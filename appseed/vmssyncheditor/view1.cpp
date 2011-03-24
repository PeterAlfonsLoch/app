#include "StdAfx.h"

namespace vmssyncheditor
{


   view1::view1(::ca::application * papp) :
      ::ca::ca(papp),
      BaseSplitLayout(papp),
      BaseSplitView(papp),
      m_karaokeutil(papp)
{
}

view1::~view1()
{
}

/*
BEGIN_MESSAGE_MAP(view1, BaseSplitView)
	//{{AFX_MSG_MAP(view1)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_INSERT, OnFileInsert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

#ifdef _DEBUG
void view1::AssertValid() const
{
	BaseSplitView::AssertValid();
}

void view1::Dump(CDumpContext& dc) const
{
	BaseSplitView::Dump(dc);
}
document* view1::get_document() // non-debug version is inline
{
   ASSERT(base<document>::bases(m_pDocument));
	return dynamic_cast < document*> (m_pDocument);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// view1 message handlers

void view1::_001OnCreate(gen::signal_object * pobj)
{
   pobj->previous();
   if(pobj->m_bRet)
      return;

	m_pdoctemplateMidiTrackSelect = new MultipleDocumentTemplate(
      "vmssyncheditor/miditrackselect",
		typeid(CMidiTrackSelectDoc),
		typeid(CMidiTrackSelectFrame), 
		typeid(CMidiTrackSelectView));

   
   SetPaneCount(2);

   SetSplitOrientation(OrientationHorizontal);
  
   SetPosition(0, 200);

   

   CreateContext cc;
   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  typeid(token_list_view);

   token_list_view * plist = dynamic_cast < token_list_view * > (create_view(&cc, this, 100));


   

   SetPane(0, plist, false);

   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  typeid(media_view);

   media_view * pmediaview = dynamic_cast < media_view * > (create_view(&cc, this, 101));
   //CXView * pmediaview = (CXView*)RUNTIME_CLASS(CXView)->CreateObject();
   //media_view * pmediaview = (media_view *) RUNTIME_CLASS(media_view)->CreateObject();
   //delete pmediaview;
   

   SetPane(1, pmediaview, false);

   Layout();
	
}

void view1::_001OnFileInsert(gen::signal_object * pobj) 
{

/* xxx  CXfplayerOpenFileDialog dlgFile;
	
	dlgFile.DoPrompt(IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_FILEMUSTEXIST
		| OFN_EXPLORER);

   AStrArray & stra = dlgFile.m_straFile;*/
/*
   string str = stra[0];

	OpenDocument(str);

   get_document()->m_iLyricTrack = -1;

   EventsTracksV1 * peventsarray
      = &get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventsTracksForPositionCB;

   LyricEventsV2 * pevents;
   if(peventsarray == NULL ||
      peventsarray->get_size() <= 0)
      pevents = NULL;
   else
   {
//      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.get_size());
      pevents = (LyricEventsV2 *) peventsarray->element_at(0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }

   m_pdocMidiTrackSelect = (CMidiTrackSelectDoc *) m_pdoctemplateMidiTrackSelect->OpenDocumentFile(NULL);
   MidiTrackSelectDDX * pddx = new MidiTrackSelectDDX();
   pddx->m_pcontrol = get_document();
   pddx->m_pselect = m_pdocMidiTrackSelect;
   m_pdocMidiTrackSelect->m_pddx = pddx;
   get_document()->m_pddx = pddx;
   pddx->m_pselect->Initialize(&get_document()->GetMediaViewData()->GetMidiSequence(), true);

   get_document()->UpdateAllViews(NULL, 100, 0);
*/
}

bool view1::OpenDocument(LPCTSTR lpszPathName)
{
	if(lpszPathName == NULL)
	{
        return true;
	}

   WString wstr;

   International::ACPToUnicode(wstr, lpszPathName);

   get_document()->GetMediaViewData()->OnOpenDocument(wstr);

   get_document()->UpdateAllViews(NULL, 100);

/*   CMidiFile & midifile = GetMidiSequence().GetFile();
	CMidiUtil midiutil;
   if(m_microke1.IsMicroke1File(lpszPathName))
   {
      CMidiSequence seqKar;
      CMemoryStorage storage;
      if(!m_microke1.GetFile(lpszPathName, storage))
         return false;
      seqKar.OpenFile(&storage, CMidiFile::OpenForPlaying, false);
      midiutil.ConvertKarToXF(seqKar, GetMidiSequence(), CMidiFile::OpenForPlaying);
   }
   else if(m_karaokeutil.IsStar350File(lpszPathName))
   {
      CFile file(
         lpszPathName,
         CFile::modeRead |
         CFile::shareDenyWrite |
         CFile::typeBinary);
        
      CArchive ar(&file, CArchive::load);
      CStar350File starFile;
      starFile.OpenFile(ar, 0);
      m_karaokeutil.ConvertStar350ToXF(&starFile, &GetMidiSequence(), CMidiFile::OpenForPlaying);
      GetMidiSequence().GetFile().ToWorkStorage();
    }
   else
   {
      CFile file(
         lpszPathName,
         CFile::modeRead |
         CFile::shareDenyWrite |
         CFile::typeBinary);
        
      CArchive ar(&file, CArchive::load);
      GetMidiSequence().OpenFile(ar, CMidiFile::OpenForPlaying);
      midiutil.ConvertToXF(GetMidiSequence(), CMidiFile::OpenForPlaying);
   }
	GetMidiSequence().GetFile().GetTracks().GetXFInfoHeaders(&m_xfInfoHeaders);
   PrepareMidiLyrics();*/
   return TRUE;
}

MidiSequence & view1::GetMidiSequence()
{
   return get_document()->GetMediaViewData()->GetMidiSequence();
}

void view1::PrepareMidiLyrics()
{
/*   CMidiTracks & tracks = get_document()->GetMidiSequence().GetFile().GetTracks();

   CBaseArray <CStrArray, CStrArray &> & str2aTokens = get_document()->m_str2aRawTokens;
   imedia::CPosition2DArray & tk2aTokensTicks = get_document()->m_tk2aTokensTicks;

   tracks.WorkSeekBegin();
   tracks.WorkGetXFTokens(
      str2aTokens,
      tk2aTokensTicks,
      NULL);

   get_document()->UpdateAllViews(NULL, 0, NULL);*/
   
}

} // namespace vmssyncheditor