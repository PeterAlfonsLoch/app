#include "StdAfx.h"

namespace mplite
{

   command_view::command_view(::ca::application * papp) :
      ca(papp),
      user::scroll_view(papp),
      ::userbase::view(papp),
      userbase::scroll_view(papp),
      user::form(papp),
      userbase::form_view(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp)
   {
   }

   command_view::~command_view()
   {
   }

      
#ifdef _DEBUG
   void command_view::assert_valid() const
   {
      form_view::assert_valid();
   }

   void command_view::dump(dump_context & dumpcontext) const
   {
      form_view::dump(dumpcontext);
   }
#endif

   bool command_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked
         || pevent->m_eevent == ::user::event_enter_key)
      {
         if(pevent->m_puie->m_id == "submit" ||
            pevent->m_eevent == ::user::event_enter_key)
         {
            
            GetTypedParent < ::mplite::command_frame > ()->ShowWindow(SW_HIDE);

            ::user::interaction * pguie = GetChildByName("query");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            string strQuery;
            ptext->_001GetText(strQuery);
            ptext->_001SetText("");
            
            string strFilter1 = strQuery;
            strFilter1.trim();
            if(gen::str::begins_ci(strFilter1, "http:")
            || gen::str::begins_ci(strFilter1, "https:"))
            {
               PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
               PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
               {
                  string strScript = System.url().url_decode(System.url().get_script(strFilter1));
                  strFilter1 = System.url().set_script(strFilter1, strScript);
               }
               pdoc->AddSong(strFilter1, PlaylistDoc::AddSongAndPlayIfNotPlaying, true, true);
            }
            else if(strQuery == "open")
            {
               m_pmainframe->m_ppaneview->set_cur_tab_by_id(::mplite::PaneViewFileManager);
            }
            else
            {
               m_pmainframe->m_ppaneview->set_cur_tab_by_id(::mplite::PaneViewFileManager);
               ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pmainframe->m_ppaneview->get(::mplite::PaneViewFileManager)->m_pdoc);

               FileManagerViewUpdateHint uh;
               uh.set_type(FileManagerViewUpdateHint::TypeFilter);
               uh.m_wstrFilter = strQuery;
               pdoc->update_all_views(NULL, 0, &uh);
            }
            return true;
         }
      }
      /*else if(pevent->m_eevent == ::user::event_timer
         && pevent->m_uiEvent == 1984)
      {
         string strDir;
         string strUsername;
         string strPasshash;
         System.crypt().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
         m_loginthread.m_strUsername = strUsername;
         System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
         if(strUsername.has_char() && strPasshash.has_char())
         {
            m_pviewAuth->KillTimer(1984);
            m_loginthread.m_strPassword.Empty();
            m_loginthread.m_strPasshash = strPasshash;
            m_loginthread.m_pcallback = this;
            m_loginthread.Begin();
         }
         return true;
      }*/
      return false;
   }

   void command_view::on_key(::user::win::message::key * pkey)
   {
      ::user::interaction * pguie = GetChildByName("query");
      System.set_keyboard_focus(pguie);
      pguie->SendMessage(pkey);
   }

}