#pragma once

namespace imediamanager
{

   class playlist_interface;

   class CLASS_DECL_ca player_interface  
   {
   protected:
      playlist_interface   * m_pplaylist;
   public:
      void set_playlist(playlist_interface * pplaylist);
      player_interface();
      virtual ~player_interface();

   //   virtual void PlayerPlay(playlist_document * pdoc, const wchar_t * lpcwsz, mediaplaylist::ESetCurrentSongHint ehint, bool bMakeVisible);
      virtual void player_on_next_song();

   };

} // namespace imediamanager
