#pragma once

class PlaylistCentral;
class PlaylistCallbackInterface;

class CLASS_DECL_ca PlaylistCentralContainer : 
   virtual public gen::signalizable
{
public:
   PlaylistCentralContainer();
   virtual ~PlaylistCentralContainer();

protected:
   PlaylistCentral *   m_pplaylistcentral;
public:
   virtual PlaylistCallbackInterface * GetNewPlaylistCallback();

   static PlaylistCentralContainer & AppGetPlaylistAppInterface(::ca::application * papp);

   static PlaylistCentral & AppGetPlaylistCentral(::ca::application * papp);

   inline PlaylistCentral & GetPlaylistCentral();

   bool initialize(::ca::application * papp);

};

