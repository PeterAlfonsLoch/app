#include "StdAfx.h"
#include "PlaylistCentralCallbackInterface.h"

PlaylistCentralCallbackInterface::PlaylistCentralCallbackInterface()
{

}

PlaylistCentralCallbackInterface::~PlaylistCentralCallbackInterface()
{

}

void PlaylistCentralCallbackInterface::OnEvent(EPlaylistEvent eevent)
{
   UNREFERENCED_PARAMETER(eevent);
}


PlaylistDoc * PlaylistCentralCallbackInterface::OnBeforeOpenPlaylist()
{
   return NULL;
}
