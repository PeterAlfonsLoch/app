// MusicalPlayerLightPlaylistCentralCallback.cpp: implementation of the MusicalPlayerLightPlaylistCentralCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "vmplightDoc.h"
#include "MusicalPlayerLightPlaylistCentralCallback.h"
#include "PaneView1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MusicalPlayerLightPlaylistCentralCallback::MusicalPlayerLightPlaylistCentralCallback()
{

}

MusicalPlayerLightPlaylistCentralCallback::~MusicalPlayerLightPlaylistCentralCallback()
{

}

PlaylistDoc *  MusicalPlayerLightPlaylistCentralCallback::OnBeforeOpenPlaylist()
{
   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
   musctrl::MusicalPlayerCentral & playercentral = papp->GetMusicalPlayerCentral();

   MusicalPlayerLightDoc * pdoc =
      (MusicalPlayerLightDoc *) playercentral.GetDocTemplate()->GetOnlyDoc();

   if(pdoc == NULL)
   {
      pdoc = (MusicalPlayerLightDoc *)  playercentral.GetDocTemplate()->OpenDocumentFile(NULL);
   }

   PaneView::ViewData * pviewdata = NULL;
   if(pdoc != NULL)
   {
      PaneView * pview = pdoc->GetPaneView();
      if(pview != NULL)
      {
          pviewdata = pview->CreateView(PaneViewPlaylist);
      }
   }

   if(pviewdata != NULL)
   {
      return (PlaylistDoc *) pviewdata->m_pdoc;
   }
   else
      return NULL;

}