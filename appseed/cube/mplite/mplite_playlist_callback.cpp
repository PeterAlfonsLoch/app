#include "StdAfx.h"

namespace mplite
{

   playlist_callback::playlist_callback(
      musctrl::MusicalPlayerCentral * pplayercentral,
      mediaplay::document * pmediadoc,
      document * pdoc) :
      ca(pplayercentral->get_app()),
      mediaplay::playlist_callback(pplayercentral, pmediadoc)
   {
      ASSERT(m_pplayercentral != NULL);
      m_pdoc = pdoc;
   }

   playlist_callback::~playlist_callback()
   {

   }
   /*bool playlist_callback::OnBeforeSetCurrentSong(
      const wchar_t * lpcwsz, 
      mediaplaylist::ESetCurrentSongHint ehint, 
      bool bMakeVisible)
   {
      return true;
   }*/

/*   EPlaylistPlay playlist_callback::PlaylistPlay(
      PlaylistDoc * pdoc,
      const char * lpcwsz, 
      mediaplaylist::ESetCurrentSongHint ehint, 
      bool bMakeVisible)
   {
      
      ASSERT(m_pplayercentral != NULL);
      //musctrl::single_document_template * pdoctemplate =
      //   m_pplayercentral->get_document_template();

      string str(lpcwsz);
      string str;
      str = str;
      //document * pplayerdoc = (document *) pdoctemplate->OpenDocumentFileNoReserve(str);
      
      document * pplayerdoc = m_pdoc;
      
      musctrl::single_document_template * pdoctemplate =
         dynamic_cast < musctrl::single_document_template * > (pplayerdoc->get_document_template());

      if(pplayerdoc != NULL)
      {
         
         ::mediaplay::view_update_hint uh;

         if(ehint == mediaplaylist::SetCurrentSongHintDoPlay)
         {
            try
            {
               if(pdoctemplate->OpenDocumentFileNoReserve(str) == NULL)
               {
                  string str;
                  throw not_implemented_exception();
                  //str.load_string(IDS_FILE_OPEN_ERROR);
                  wait_message_dialog dialog(get_app());
                  dialog.m_dwDelay = 5000;
                  gen::property_set propset;
                  dialog.show(System.dir().matter("system\\wait_dialog.html"), propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }
               }
            }
            catch(ex1::file_exception_sp * pe)
            {
               string str;
               pe->m_p->GetErrorMessage(str);
                  string str;
                  throw not_implemented_exception();
                  //str.load_string(IDS_FILE_OPEN_ERROR);
                  wait_message_dialog dialog(get_app());
                  dialog.m_dwDelay = 5000;
                  gen::property_set propset;
                  dialog.show(System.dir().matter("system\\wait_dialog.html"), propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }
            }
/*            catch(ex1::file_exception_sp * pe)
            {
               string str;
               pe->GetErrorMessage(str);
               string str;
               str.load_string(IDS_FILE_OPEN_ERROR);
               wait_message_dialog dialog(get_app());
               dialog.m_dwDelay = 5000;
               gen::property_set propset;
               dialog.show(System.dir().matter("system\\wait_dialog.html"), propset);
               if(dialog.m_strResponse == "continue"
               || dialog.m_strResponse == "timeout")
               {
                  return PlaylistPlayErrorContinue;
               }
               else
               {
                  return PlaylistPlayErrorCancel;
               }
            }*/

  /*          uh.set_type(::mediaplay::view_update_hint::TypeDoPlay);
            pplayerdoc->update_all_views(NULL, 0, &uh);
         }
         else if(ehint == mediaplaylist::SetCurrentSongHintPlayIfNotPlaying)
         {
            uh.set_type(::mediaplay::view_update_hint::TypeGetMidiPlayerInterface);
            pplayerdoc->update_all_views(NULL, 0, &uh);
            if(uh.m_pmidiplayer != NULL)
            {
               if(uh.m_pmidiplayer->GetMidiSequence().GetState() 
                  == ::mus::midi::sequence::StatusOpened
                  ||
                  uh.m_pmidiplayer->GetMidiSequence().GetState() 
                  == ::mus::midi::sequence::StatusNoFile)
               {
                  if(pdoctemplate->OpenDocumentFileNoReserve(str) == NULL)
                     return PlaylistPlayErrorCancel;
                  uh.set_type(::mediaplay::view_update_hint::TypeDoPlay);
                  pplayerdoc->update_all_views(NULL, 0, &uh);
               }
               else
               {
                  return PlaylistPlayErrorBusy;
               }
            }
         }
      }
      return PlaylistPlaySuccess;
   }
*/

   void playlist_callback::PlaylistOnBeforeOpen()
   {
      if(m_pdoc != NULL)
      {
         pane_view * pview = m_pdoc->GetPaneView();
         if(pview != NULL)
         {
            pview->ensure(PaneViewPlaylist);
         }
      }

   }

} // namespace mplite