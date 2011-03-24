#pragma once

namespace mplite
{

   class pane_view;

   class playlist_central_callback :
      virtual public PlaylistCentralCallbackInterface
   {
   public:


      pane_view *    m_ppaneview;

      
      playlist_central_callback(::ca::application * papp);
      virtual ~playlist_central_callback();

      virtual PlaylistDoc * OnBeforeOpenPlaylist();
      //virtual void OnEvent(EPlaylistEvent eevent);
   };

} // namespace mplite