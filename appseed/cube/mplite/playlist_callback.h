#pragma once

namespace mplite
{

   class document;

   class playlist_callback :
      public mediaplay::playlist_callback
   {
   public:
      playlist_callback(
         musctrl::MusicalPlayerCentral * pplayercentral,
         mediaplay::document * pmediadoc,
         document * pdoc);
      virtual ~playlist_callback();


      document * m_pdoc;


      bool PlaylistOnBeforePlay(
         const char * lpcwsz, 
         mediaplaylist::ESetCurrentSongHint ehint, 
         bool bMakeVisible);

      virtual void PlaylistOnBeforeOpen();

   };

} // namespace mplite
