#pragma once

class midi_player_interface;

namespace mediaplaylist
{

   class document;

} // namespace mediaplaylist

namespace mediaplay
{

   class data;

   class CLASS_DECL_ca view_update_hint : public ::radix::object  
   {
      
   public:
      enum e_type
      {
         type_none,
         TypePlayIfNotPlaying,
         TypeDoPlay,
         TypeExecuteStop,
         TypeCloseDevice,
         TypeDeleteContents,
         TypeGetMidiPlayerInterface,
         TypeGetPlaylistCallback,
         TypeGetWavePlayer,
         TypeAttachPlaylist,
         TypeFullScreen,
         TypeInitialUpdate,
         TypeBeforeOpenDocument,
         TypeAfterOpenDocument,
      };
      // Attributes
   protected:
      e_type                        m_etype;
   public:
      midi_player_interface *         m_pmidiplayer;
      ::mediaplaylist::document *                 m_pplaylistdoc;
      mediaplaylist::callback_interface *  m_pplaylistcallback;
      bool                          m_bFullScreen;
      ::mediaplay::data *           m_pdata;
      audWavePlayer *               m_pwaveplayer;
      imedia::position              m_position;
   public:
      bool is_type_of(e_type e_type);
      void set_type(e_type e_type);
      view_update_hint();
      virtual ~view_update_hint();

   };

} // namespace mediaplay

