// MusicalPlayerLightPlaylistCentralCallback.h: interface for the MusicalPlayerLightPlaylistCentralCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICALPLAYERLIGHTPLAYLISTCENTRALCALLBACK_H__994471A8_DD3E_4FE2_BD04_7610C18E480C__INCLUDED_)
#define AFX_MUSICALPLAYERLIGHTPLAYLISTCENTRALCALLBACK_H__994471A8_DD3E_4FE2_BD04_7610C18E480C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mediapl/PlaylistCentralCallbackInterface.h"



class MusicalPlayerLightPlaylistCentralCallback :
   public PlaylistCentralCallbackInterface
{
public:
	MusicalPlayerLightPlaylistCentralCallback();
	virtual ~MusicalPlayerLightPlaylistCentralCallback();

   virtual PlaylistDoc * OnBeforeOpenPlaylist();
   //virtual void OnEvent(EPlaylistEvent eevent);
};

#endif // !defined(AFX_MUSICALPLAYERLIGHTPLAYLISTCENTRALCALLBACK_H__994471A8_DD3E_4FE2_BD04_7610C18E480C__INCLUDED_)
