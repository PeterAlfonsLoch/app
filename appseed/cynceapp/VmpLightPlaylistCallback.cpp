// VmpPlaylistCallback.cpp: implementation of the MusicalPlayerLightPlaylistCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "VmpLightPlaylistCallback.h"

#include "VmpLightDoc.h"
#include "VmpLightViewUpdateHint.h"



#include "PaneView1.h"



#include "WaitMessageDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MusicalPlayerLightPlaylistCallback::MusicalPlayerLightPlaylistCallback(
   musctrl::MusicalPlayerCentral * pplayercentral,
   MusicalPlayerLightDoc * pdoc)
{
   ASSERT(m_pplayercentral != NULL);
   m_pplayercentral = pplayercentral;
   m_pdoc = pdoc;
}

MusicalPlayerLightPlaylistCallback::~MusicalPlayerLightPlaylistCallback()
{

}
/*bool MusicalPlayerLightPlaylistCallback::OnBeforeSetCurrentSong(
	LPCWSTR lpcwsz, 
	_vmspl::ESetCurrentSongHint ehint, 
	bool bMakeVisible)
{
   return true;
}*/

EPlaylistPlay MusicalPlayerLightPlaylistCallback::PlaylistPlay(
	PlaylistDoc * pdoc,
	LPCSTR lpcwsz, 
	_vmspl::ESetCurrentSongHint ehint, 
	bool bMakeVisible)
{
	
   ASSERT(m_pplayercentral != NULL);
	//musctrl::CSingleDocTemplate * pdoctemplate =
	//	m_pplayercentral->GetDocTemplate();

	CString wstr(lpcwsz);
	CString str;
	str = wstr;
	//MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) pdoctemplate->OpenDocumentFileNoReserve(str);
   
   MusicalPlayerLightDoc * pplayerdoc = m_pdoc;
   
   musctrl::SingleDocTemplate * pdoctemplate =
      (musctrl::SingleDocTemplate *) pplayerdoc->GetDocTemplate();

	if(pplayerdoc != NULL)
	{
      
      mediaplay::MediaViewUpdateHint uh;

      if(ehint == _vmspl::SetCurrentSongHintDoPlay)
      {
         try
         {
            if(pdoctemplate->OpenDocumentFileNoReserve(wstr) == NULL)
            {
               WString wstr;
               wstr.LoadString(IDS_FILE_OPEN_ERROR);
               WaitMessageDialog dialog(wstr, 5000);
               int iModalResult = dialog.DoModal();
               if(iModalResult == ID_CONTINUE)
               {
                  return PlaylistPlayErrorContinue;
               }
               else
               {
                  return PlaylistPlayErrorCancel;
               }
            }
         }
         catch(Ex1FileException * pe)
         {
            WString wstr;
            CString str;
            LPTSTR lpsz = str.GetBuffer(2048);
            pe->GetErrorMessage(lpsz, 2048);
            wstr.Format(L"%S", lpsz);
            WaitMessageDialog dialog(wstr, 5000);
            int iModalResult = dialog.DoModal();
            pe->Delete();
            if(iModalResult == ID_CONTINUE)
            {
               return PlaylistPlayErrorContinue;
            }
            else
            {
               return PlaylistPlayErrorCancel;
            }
         }
         catch(CFileException * pe)
         {
            WString wstr;
            CString str;
            LPTSTR lpsz = str.GetBuffer(2048);
            pe->GetErrorMessage(lpsz, 2048);
            wstr.Format(L"%S", lpsz);
            WaitMessageDialog dialog(wstr, 5000);
            int iModalResult = dialog.DoModal();
            pe->Delete();
            if(iModalResult == ID_CONTINUE)
            {
               return PlaylistPlayErrorContinue;
            }
            else
            {
               return PlaylistPlayErrorCancel;
            }
         }

         uh.SetType(mediaplay::MediaViewUpdateHint::TypeDoPlay);
         pplayerdoc->UpdateAllViews(NULL, 0, &uh);
      }
      else if(ehint == _vmspl::SetCurrentSongHintPlayIfNotPlaying)
      {
         uh.SetType(mediaplay::MediaViewUpdateHint::TypeGetMidiPlayerInterface);
         pplayerdoc->UpdateAllViews(NULL, 0, &uh);
         if(uh.m_pmidiplayer != NULL)
         {
            if(uh.m_pmidiplayer->GetMidiSequence().GetState() 
               == MidiSequence::StatusOpened
               ||
               uh.m_pmidiplayer->GetMidiSequence().GetState() 
               == MidiSequence::StatusNoFile)
            {
               if(pdoctemplate->OpenDocumentFileNoReserve(wstr) == NULL)
                  return PlaylistPlayErrorCancel;
               uh.SetType(mediaplay::MediaViewUpdateHint::TypeDoPlay);
               pplayerdoc->UpdateAllViews(NULL, 0, &uh);
            }
            else
            {
               return PlaylistPlayErrorBusy;
            }
         }
      }
	}
   return PlaylistPlaySuccess;
}


void MusicalPlayerLightPlaylistCallback::PlaylistOnBeforeOpen()
{
   if(m_pdoc != NULL)
   {
      PaneView * pview = m_pdoc->GetPaneView();
      if(pview != NULL)
      {
         pview->CreateView(PaneViewPlaylist);
      }
   }

}
