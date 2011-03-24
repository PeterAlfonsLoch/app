#include "StdAfx.h"
#include "VmpPlaylistCallback.h"

#include "XfplayerDoc.h"
#include "XfplayerViewUpdateHint.h"

CVmpPlaylistCallback::CVmpPlaylistCallback()
{

}

CVmpPlaylistCallback::~CVmpPlaylistCallback()
{

}

void CVmpPlaylistCallback::OnSetCurrentSong(
   PlaylistDoc * pdoc,
   const char * lpcsz, 
   bool bDoPlay,
   bool bMakeVisible)
{
   
   musctrl::MusicalPlayerCentral & playercentral = musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app());
   musctrl::single_document_template * pdoctemplate = playercentral.get_document_template();

   string str(lpcsz);

   XfplayerDoc * pplayerdoc = dynamic_cast < XfplayerDoc * > (pdoctemplate->OpenDocumentFileNoReserve(str));
   ASSERT_KINDOF(XfplayerDoc, pplayerdoc);
   if(pplayerdoc != NULL)
   {
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypePlay);
      pplayerdoc->update_all_views(NULL, 0, &uh);
   }

}
