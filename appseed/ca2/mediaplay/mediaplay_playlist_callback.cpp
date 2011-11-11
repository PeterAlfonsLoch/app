#include "StdAfx.h"

namespace mediaplay
{

   playlist_callback::playlist_callback(
      musctrl::MusicalPlayerCentral    * pplayercentral,
      mediaplay::document     * pmediadoc)
   {
      ASSERT(pplayercentral != NULL);
      ASSERT(pmediadoc != NULL);
      m_pplayercentral  = pplayercentral;
      m_pmediadoc       = pmediadoc;
   }

   playlist_callback::~playlist_callback()
   {

   }

   bool playlist_callback::is_playing()
   {
      if(m_pmediadoc == NULL)
         return false;
      return m_pmediadoc->GetMediaView()->_ExecuteIsPlaying();
   }

   mediaplaylist::e_play playlist_callback::PlaylistPlay(mediaplaylist::info * pinfo)
   {
      ASSERT(m_pplayercentral != NULL);

      mediaplay::document * pmediadoc = m_pmediadoc;

      if(pmediadoc != NULL)
      {

         ::mediaplay::view_update_hint uh;

         if(pinfo->m_ehint == mediaplaylist::hint_do_play)
         {
            if(is_playing())
            {
               m_propaBatch.remove_all();
               gen::var_property prop;
               prop["command"]         = "PlaylistPlay";
               prop["doc"]             = new raw_pointer(pinfo->m_pdocument);
               prop["path"]            = pinfo->m_strFilePath;
               prop["hint"]            = (int) pinfo->m_ehint;
               prop["make_visible"]    = pinfo->m_bMakeVisible;
               prop["position"]        = 0;
               m_propaBatch.add(prop);
               pmediadoc->GetMediaView()->_ExecuteStop();
               return mediaplaylist::play_success;
            }
            try
            {
               if(m_pplayercentral->get_document_template()->OpenDocumentFileNoReserve(pinfo->m_strFilePath, NULL) == NULL)
               {
                  return mediaplaylist::play_error_continue;
                  /*string str;
                  str = "*file open error";
                  wait_message_dialog dialog(get_app());
                  dialog.m_dwDelay = 5000;
                  gen::property_set propset;
                  propset["message"] = str;
                  dialog.show("system\\wait_dialog.html", propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }*/
               }
            }
            catch(ex1::file_exception *)
            {
               return mediaplaylist::play_error_continue;
               /*string str;
               pe->GetErrorMessage(str);
                  str = "An error occurred while opening file: " + str;
                  wait_message_dialog dialog(get_app());
                  dialog.m_dwDelay = 5000;
                  gen::property_set propset;
                  propset["message"] = str;
                  dialog.show("system\\wait_dialog.html", propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }*/
            }
            pmediadoc->GetMediaView()->_ExecutePlay(true, pinfo->m_position);
         }
         else if(pinfo->m_ehint == mediaplaylist::hint_play_if_not_playing)
         {
            if(!pmediadoc->GetMediaView()->_ExecuteIsEntertaining())
            {
               if(m_pplayercentral->get_document_template()->OpenDocumentFileNoReserve(pinfo->m_strFilePath, NULL) == NULL)
                     return mediaplaylist::play_error_cancel;
               pmediadoc->GetMediaView()->_ExecutePlay(true, pinfo->m_position);
            }
            else
            {
               return mediaplaylist::play_success;
            }
         }
      }
      return mediaplaylist::play_success;
   }


   void playlist_callback::PlaylistOnBeforeOpen()
   {
      callback_interface::PlaylistOnBeforeOpen();
   }

   void playlist_callback::PlaylistOnPlaybackEnd()
   {
      if(m_propaBatch.get_count() > 0)
      {
         gen::var_property & prop = m_propaBatch[0];
         if(prop["command"] == "PlaylistPlay")
         {
            mediaplaylist::info info;
            info.m_pdocument     = prop["doc"].get_value().ca2 < raw_pointer > ()->ca2 < mediaplaylist::document >();
            info.m_strFilePath   = prop["path"];
            info.m_ehint         = (mediaplaylist::e_hint) (int) prop["hint"];
            info.m_bMakeVisible  = prop["make_visible"];
            PlaylistPlay(&info);
         }
         m_propaBatch.remove_at(0);
      }
      else
      {
         callback_interface::PlaylistOnPlaybackEnd();
      }
   }
} // namespace mediaplay
