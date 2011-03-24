#pragma once

namespace imediamanager
{

   class player_interface;

   class CLASS_DECL_ca playlist_interface  
   {
   protected:
      player_interface   * m_pplayer;
   public:
      void SetPlayer(player_interface * pplayer);
      playlist_interface();
      virtual ~playlist_interface();
      virtual void playlist_on_next_song();

   };

} // namespace imediamanager

