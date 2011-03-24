#pragma once

class CVmpPlaylistCallback :
   public PlaylistCallbackInterface,
   virtual public ::radix::object
{
public:
   CVmpPlaylistCallback();
   virtual ~CVmpPlaylistCallback();


   void OnSetCurrentSong(
      PlaylistDoc * pdoc,
      const char * lpcwsz, 
      bool bDoPlay, 
      bool bMakeVisible);

};
