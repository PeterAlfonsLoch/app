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

   EPlaylistPlay playlist_callback::PlaylistPlay(playlist_info * pinfo)
   {
      ASSERT(m_pplayercentral != NULL);

      mediaplay::document * pmediadoc = m_pmediadoc;
      
      if(pmediadoc != NULL)
      {
         
         ::mediaplay::view_update_hint uh;

         if(pinfo->m_ehint == mediaplaylist::SetCurrentSongHintDoPlay)
         {
            if(is_playing())
            {
               m_propaBatch.remove_all();
               gen::var_property prop;
               prop["command"]         = "PlaylistPlay";
               prop["doc"]             = new raw_pointer(pinfo->m_pdoc);
               prop["path"]            = pinfo->m_strFilePath;
               prop["hint"]            = (int) pinfo->m_ehint;
               prop["make_visible"]    = pinfo->m_bMakeVisible;
               prop["position"]        = 0;
               m_propaBatch.add(prop);
               pmediadoc->GetMediaView()->_ExecuteStop();
               return PlaylistPlaySuccess;
            }
            try
            {
               if(m_pplayercentral->get_document_template()->OpenDocumentFileNoReserve(pinfo->m_strFilePath) == NULL)
               {
                  string str;
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
                  }
               }
            }
            catch(ex1::file_exception * pe)
            {
               string str;
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
                  }
            }
            pmediadoc->GetMediaView()->_ExecutePlay(true, pinfo->m_position);
         }
         else if(pinfo->m_ehint == mediaplaylist::SetCurrentSongHintPlayIfNotPlaying)
         {
            if(!pmediadoc->GetMediaView()->_ExecuteIsEntertaining())
            {
               if(m_pplayercentral->get_document_template()->OpenDocumentFileNoReserve(pinfo->m_strFilePath) == NULL)
                     return PlaylistPlayErrorCancel;
               pmediadoc->GetMediaView()->_ExecutePlay(true, pinfo->m_position);
            }
            else
            {
               return PlaylistPlayErrorBusy;
            }
         }
      }
      return PlaylistPlaySuccess;
   }


   void playlist_callback::PlaylistOnBeforeOpen()
   {
      PlaylistCallbackInterface::PlaylistOnBeforeOpen();
   }

   void playlist_callback::PlaylistOnPlaybackEnd()
   {
      if(m_propaBatch.get_count() > 0)
      {
         gen::var_property & prop = m_propaBatch[0];
         if(prop["command"] == "PlaylistPlay")
         {
            playlist_info info;
            info.m_pdoc          = prop["doc"].get_value().ca2 < raw_pointer > ()->ca2 < PlaylistDoc >();
            info.m_strFilePath   = prop["path"];
            info.m_ehint         = (mediaplaylist::ESetCurrentSongHint) (int) prop["hint"];
            info.m_bMakeVisible  = prop["make_visible"];
            PlaylistPlay(&info);
         }
         m_propaBatch.remove_at(0);
      }
      else
      {
         PlaylistCallbackInterface::PlaylistOnPlaybackEnd();
      }
   }
} // namespace mediaplay