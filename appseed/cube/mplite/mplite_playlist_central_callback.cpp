#include "StdAfx.h"
#include "document.h"

namespace mplite
{

   playlist_central_callback::playlist_central_callback(::ca::application * papp) :
      ca(papp)
   {
      m_ppaneview = NULL;
   }

   playlist_central_callback::~playlist_central_callback()
   {
   }

   PlaylistDoc *  playlist_central_callback::OnBeforeOpenPlaylist()
   {
      PlaylistCentral & playlistcentral = Application.GetPlaylistCentral();

      ::document * pdoc = dynamic_cast < ::document * > (playlistcentral.m_pplaylistdocCurrent.get_p());

      if(pdoc == NULL && m_ppaneview != NULL)
      {
         m_ppaneview->set_cur_tab_by_id(PaneViewPlaylist);
         pdoc = dynamic_cast < ::document * > (playlistcentral.m_pplaylistdocCurrent.get_p());
      }

      return dynamic_cast < PlaylistDoc * > (pdoc);
   }

} // namespace mplite