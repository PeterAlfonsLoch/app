#pragma once

enum EPlaylistEvent
{
   PlaylistEventBeforeOpen,
};

class PlaylistDoc;

class CLASS_DECL_ca PlaylistCentralCallbackInterface :
   virtual public ::radix::object
{
public:
   PlaylistCentral * m_pcentral;

   virtual void OnEvent(EPlaylistEvent eevent);
   PlaylistCentralCallbackInterface();
   virtual ~PlaylistCentralCallbackInterface();

   virtual PlaylistDoc * OnBeforeOpenPlaylist();

};
