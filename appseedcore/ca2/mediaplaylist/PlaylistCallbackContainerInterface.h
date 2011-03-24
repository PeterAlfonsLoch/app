#pragma once

class PlaylistCallbackInterface;

class CLASS_DECL_ca PlaylistCallbackContainerInterface  
{
public:
   PlaylistCallbackContainerInterface();
   virtual ~PlaylistCallbackContainerInterface();

   virtual PlaylistCallbackInterface * GetPlaylistCallback() = 0;

};
