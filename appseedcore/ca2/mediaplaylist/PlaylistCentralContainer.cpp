#include "StdAfx.h"

PlaylistCentralContainer::PlaylistCentralContainer()
{
   m_pplaylistcentral = NULL;
}

PlaylistCentralContainer::~PlaylistCentralContainer()
{
   delete m_pplaylistcentral;
}

bool PlaylistCentralContainer::initialize(::ca::application * papp)
{
   set_app(papp);
   m_pplaylistcentral = new PlaylistCentral(papp);
   if(m_pplaylistcentral == NULL)
      return false;
   System.factory().creatable_small < PlaylistDoc >();
   System.factory().creatable_small < PlaylistFrame >();
   System.factory().creatable_small < PlaylistListView >();
   System.factory().creatable_small < CPlaylistView >();
   return true;
}


PlaylistCallbackInterface * PlaylistCentralContainer::GetNewPlaylistCallback()
{
   return NULL;
}


PlaylistCentral & PlaylistCentralContainer::GetPlaylistCentral()
{
   return *m_pplaylistcentral;
}

PlaylistCentralContainer & PlaylistCentralContainer::AppGetPlaylistAppInterface(::ca::application * papp)
{
   return *(dynamic_cast < PlaylistCentralContainer * > (papp));
}

PlaylistCentral & PlaylistCentralContainer::AppGetPlaylistCentral(::ca::application * papp)
{
   return AppGetPlaylistAppInterface(papp).GetPlaylistCentral();
}
