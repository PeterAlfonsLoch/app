#include "StdAfx.h"

namespace vmssyncheditor
{

   media_view::media_view(::ca::application * papp) :
      ::ca::ca(papp),
      gcom::backview::WndInterface(papp),
      mediaplay::MediaViewInterface(papp),
      mediaplay::MediaView(papp)
{
}

media_view::~media_view()
{
}

/*
BEGIN_MESSAGE_MAP(media_view, MediaView)
//{{AFX_MSG_MAP(media_view)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

#ifdef _DEBUG
void media_view::AssertValid() const
{
   MediaView::AssertValid();
}

void media_view::Dump(CDumpContext& dc) const
{
   MediaView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// media_view message handlers


void media_view::OnUpdate(view* psender, LPARAM lhint, base_object* phint) 
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

void media_view::KaraokeGetPosition(imedia::Position &position)
{
   if(GetMidiSequence().IsPlaying())
   {
      ikar::KaraokeData & data = GetKaraokeData();
      ikar::KaraokeInterface * pinterface = data.GetInterface();
      pinterface->GetPosition(position);
   }
   else
   {
      document * pdoc = (document *) get_document();
      pdoc->GetPosition(position);
   }

}

void media_view::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj);

   if(GetMidiSequence().IsPlaying())
   {
      document * pdoc = (document *) get_document();
      pdoc->m_iCurrentToken = GetKaraokeData().GetDynamicData().m_iPlayingTokenIndex;
      pdoc->UpdateAllViews(NULL, 101);
   }
}

void media_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   MediaView::_001OnInitialUpdate(pobj);

   initialize((document *) get_document());	

}

void media_view::data_on_after_change(gen::signal_object * pobj)
{
   SCAST_PTR(idb::event::data_change, pchange, pobj);
   if((pchange->m_puh == NULL || !pchange->m_puh->GetUpdateFlags().IsSignalized(data_update_hint::UpdateInternal))
      && pchange->m_dataidKey == document::ConfigIdToken)
   {
      PrepareLyricLines();
   }

}

} // namespace vmssyncheditor