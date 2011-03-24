#pragma once

class PlaylistDoc;

namespace mplite
{

   class CLASS_DECL_CA2_CUBE view_update_hint : public ::radix::object  
   {
   public:
      enum e_type
      {
         type_none,
         TypePlayIfNotPlaying,
         TypeDoPlay,
         TypeGetMidiPlayerInterface,
         TypeGetPlaylistCallback,
         TypeAttachPlaylist,
         TypeFullScreen,
         TypeInitialUpdate,
      };
      // Attributes
   protected:
      e_type                         m_etype;
   public:
      MidiPlayerInterface *         m_pmidiplayer;
      PlaylistDoc *                 m_pplaylistdoc;
      PlaylistCallbackInterface *   m_pplaylistcallback;
      bool                          m_bFullScreen;
   public:
      bool is_type_of(e_type e_type);
      void set_type(e_type e_type);
      view_update_hint();
      virtual ~view_update_hint();

   };

} // namespace mplite