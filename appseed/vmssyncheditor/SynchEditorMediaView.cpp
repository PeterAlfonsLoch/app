// SynchEditorMediaView.cpp : implementation file
//

#include "stdafx.h"
#include "vmssyncheditor.h"
#include "SynchEditorMediaView.h"

#include "_vmssyncheditorDoc.h"

#include "KaraokeData.h"
#include "KaraokeDynamicData.h"

#include "VmsDataUpdateHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SynchEditorMediaView

IMPLEMENT_DYNCREATE(SynchEditorMediaView, MediaView)

SynchEditorMediaView::SynchEditorMediaView()
{
}

SynchEditorMediaView::~SynchEditorMediaView()
{
}


BEGIN_MESSAGE_MAP(SynchEditorMediaView, MediaView)
	//{{AFX_MSG_MAP(SynchEditorMediaView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SynchEditorMediaView drawing


/////////////////////////////////////////////////////////////////////////////
// SynchEditorMediaView diagnostics

#ifdef _DEBUG
void SynchEditorMediaView::AssertValid() const
{
	MediaView::AssertValid();
}

void SynchEditorMediaView::Dump(CDumpContext& dc) const
{
	MediaView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SynchEditorMediaView message handlers


void SynchEditorMediaView::OnUpdate(SimpleView* psender, LPARAM lhint, CObject* phint) 
{
   if(lhint == 13)
   {
      RedrawWindow();
   }
   if(lhint == 100)
   {
      PrepareLyricLines();
   }
   else if(lhint == 122)
   {
      PrepareLyricLines();
   }
   else if(lhint == 123)
   {
      //GetMediaViewData()->GetKaraokeData().Prepare();
//      PrepareLyricLines();
//      m_lpbouncingball->SetQuarterNoteDuration(
  //        GetMidiSequence().GetFile().m_pFileHeader->GetQuarterNoteTicks());
      _ExecutePlay(TRUE);
   }
   else if(lhint == 124)
   {
      _ExecuteStop();
   }
   else if(lhint == 1017)
   {
      m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_COMMAND, MidiPlayerCommandStopAndRestart, 0);
   }
	
   MediaView::OnUpdate(psender, lhint, phint);
	
}

void SynchEditorMediaView::KaraokeGetPosition(_vmsmediai::Position &position)
{
   if(GetMidiSequence().IsPlaying())
   {
      _vmskar::KaraokeData & data = GetKaraokeData();
      _vmskaraokei::KaraokeInterface * pinterface = data.GetInterface();
      pinterface->GetPosition(position);
   }
   else
   {
      _vmssyncheditorDoc * pdoc = (_vmssyncheditorDoc *) GetDocument();
      pdoc->GetPosition(position);
   }

}

void SynchEditorMediaView::OnTimer(UINT nIDEvent) 
{
	MediaView::OnTimer(nIDEvent);

   if(GetMidiSequence().IsPlaying())
   {
      _vmssyncheditorDoc * pdoc = (_vmssyncheditorDoc *) GetDocument();
      pdoc->m_iCurrentToken = GetKaraokeData().GetDynamicData().m_iPlayingTokenIndex;
      pdoc->UpdateAllViews(NULL, 101);
   }
}

void SynchEditorMediaView::OnInitialUpdate() 
{
	MediaView::OnInitialUpdate();
	
   VmsDataInitialize((_vmssyncheditorDoc *) GetDocument());	

   ((_vmssyncheditorDoc *)GetDocument())->AddClient(this);
}

void SynchEditorMediaView::VmsDataOnAfterChange(
   int iConfigId, 
   int iLine, 
   int iColumn, 
   VmsDataUpdateHint * puh)
{
   if((puh == NULL || !puh->GetUpdateFlags().IsSignalized(VmsDataUpdateHint::UpdateInternal))
      && iConfigId == _vmssyncheditorDoc::ConfigIdToken)
   {
      PrepareLyricLines();
   }

}
