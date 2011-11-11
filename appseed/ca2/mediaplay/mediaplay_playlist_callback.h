#pragma once


namespace mediaplay
{

   
   class document;

   
   class CLASS_DECL_ca playlist_callback :
      public mediaplaylist::callback_interface
   {
   public:


      musctrl::MusicalPlayerCentral *        m_pplayercentral;
      mediaplay::document *                  m_pmediadoc;

      gen::var_property_array                m_propaBatch;

      playlist_callback(musctrl::MusicalPlayerCentral * pplayercentral, mediaplay::document * pmediadoc);
      virtual ~playlist_callback();


      bool PlaylistOnBeforePlay(mediaplaylist::info * pinfo);
      virtual mediaplaylist::e_play PlaylistPlay(mediaplaylist::info * pinfo);
      virtual void PlaylistOnBeforeOpen();
      virtual void PlaylistOnPlaybackEnd();

      virtual bool is_playing();


   };


} // namespace mediaplay


