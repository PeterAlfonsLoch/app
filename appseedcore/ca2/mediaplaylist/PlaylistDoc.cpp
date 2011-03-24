#include "StdAfx.h"


const LPARAM PlaylistDoc::LHINT_FRAMEDOWN = 1;
const LPARAM PlaylistDoc::LHINT_FRAMEUP = 2;

playlist_info::playlist_info()
{
   m_pdoc            = NULL;
   m_bUser           = false;
   m_iCurrentSong    = -1;
   m_ehint           = mediaplaylist::SetCurrentSongHintPlayIfNotPlaying;
   m_bMakeVisible    = true;
}

playlist_info::~playlist_info()
{
}


PlaylistDoc::PlaylistDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
   m_bLoop           = true;
   m_bShuffle        = false;
   m_iCurrentSong    = 0;

   PlaylistCallbackContainerInterface * pplaylistcallbackcontainerinterface =
      dynamic_cast < PlaylistCallbackContainerInterface * >
      (&System);
   if(pplaylistcallbackcontainerinterface != NULL)
   {
      m_xpcallback = pplaylistcallbackcontainerinterface->GetPlaylistCallback();
      if(m_xpcallback != NULL)
      {
         m_xpcallback->m_pplaylistdoc = this;
      }
   }
   else
   {
      m_xpcallback = NULL;
   }
}

BOOL PlaylistDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   return TRUE;
}

PlaylistDoc::~PlaylistDoc()
{
}

void PlaylistDoc::on_final_release()
{
   // When the last reference for an automation object is released
   // on_final_release is called.  The base class will automatically
   // deletes the object.  add additional cleanup required for your
   // object before calling the base class.

   ::userbase::document::on_final_release();
}


#ifdef _DEBUG
void PlaylistDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void PlaylistDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PlaylistDoc serialization

void PlaylistDoc::write(ex1::output_stream & outputstream)
{
   outputstream << m_wstraSong;
}

void PlaylistDoc::read(ex1::input_stream & inputstream)
{
   inputstream >> m_wstraSong;
}

/////////////////////////////////////////////////////////////////////////////
// PlaylistDoc commands

/*::userbase::view * PlaylistDoc::GetPlaylistView()
{
POSITION pos = get_view_count();
while(pos != NULL)
{
::userbase::view * pview = get_view(pos);
if(base < CPlaylistListView >::bases(pview))
return pview;
}
return NULL;

}*/


/*bool PlaylistDoc::PeekSongPath(string & str, int iOffset, bool bLoop)
{
   int iSong = m_iCurrentSong;

   iSong += iOffset;

   if(iSong < 0)
   {
      if(!bLoop)
         return false;
      iSong = m_wstraSongs.get_size() - 1;
   }
   else if(iSong >= m_wstraSongs.get_size())
   {
      if(!bLoop)
         return false;
      iSong = 0;
   }

   if(iSong >= 0 &&
      iSong <= m_wstraSongs.get_size())
   {
      m_iCurrentSong = iSong;

      str = m_wstraSongs.element_at(m_iCurrentSong);


      PlaylistViewUpdateHint plvuh;
      plvuh.SetHint(PlaylistViewUpdateHint::HintCurrentSong);

      update_all_views(NULL, 0, &plvuh);


      return true;
   }
   else
   {
      return false;
   }

}*/

bool PlaylistDoc::has_next_song()
{
   if(m_wstraSong.get_count() <= 0)
      return false;
   if(m_bLoop)
      return true;
   if(m_iaQueue.get_count() <= 0)
      return false;
   return true;
}

bool PlaylistDoc::get_songs(stringa & stra)
{
   stra = m_wstraSong;
   return true;
}

bool PlaylistDoc::get_song_current_queue(stringa & stra)
{
   for(int i = 0; i < m_iaQueue.get_count(); i++)
   {
      stra.add(m_wstraSong[m_iaQueue[i]]);
   }
   return true;
}

int PlaylistDoc::GetCurrentSong()
{
   return m_iCurrentSong;
}

bool PlaylistDoc::play(playlist_info * pinfo)
{
   string str;


   if(m_xpcallback == NULL)
   {
      m_xpcallback = PlaylistCentralContainer::AppGetPlaylistAppInterface(get_app()).GetNewPlaylistCallback();
   }

   if(pinfo->m_bUser
   || pinfo->m_ehint == mediaplaylist::SetCurrentSongHintDoPlay   
   || (pinfo->m_ehint == mediaplaylist::SetCurrentSongHintPlayIfNotPlaying && (m_xpcallback == NULL || !m_xpcallback->is_playing())))
   {
      populate_queue(pinfo->m_iCurrentSong);
   }

   int iSong = -1;

   if(m_xpcallback != NULL)
   {
      EPlaylistPlay eplay;
      while(true)
      {
         if(!pick_a_song(iSong, str))
            return false;
         if(m_setFile[str].is_empty())
            m_setFile[str] = str;
         pinfo->m_strFilePath = m_setFile[str];
         pinfo->m_pdoc = this;
         eplay = m_xpcallback->PlaylistPlay(pinfo);
         if(eplay == PlaylistPlaySuccess)
         {
            m_iCurrentSong = iSong;
            data_set("current_song", m_iCurrentSong);
            return true;
         }
         else if(eplay != PlaylistPlayErrorContinue)
         {
            return false;
         }
      }
   }
   return false;
}

void PlaylistDoc::restart(bool bUser) 
{
   playlist_info info;

   data_get("current_song", info.m_iCurrentSong);
   data_get("current_song_position", info.m_position.m_i);

   if(info.m_iCurrentSong < 0)
   {
      info.m_iCurrentSong     = 0;
      info.m_position         = 0;
   }

   if(info.m_iCurrentSong >= GetSongCount())
   {
      info.m_iCurrentSong     = 0;
      info.m_position         = 0;
   }

   if(info.m_iCurrentSong >= GetSongCount())
      return;

   info.m_ehint               = mediaplaylist::SetCurrentSongHintPlayIfNotPlaying;
   info.m_bMakeVisible        = true;
   info.m_bUser               = bUser;

   play(&info);

}

void PlaylistDoc::OnPlay() 
{
   playlist_info info;
   info.m_iCurrentSong     = GetCurrentSong();
   info.m_ehint            = mediaplaylist::SetCurrentSongHintDoPlay;
   info.m_bMakeVisible     = true;
   play(&info);
}

VMSRESULT PlaylistDoc::AddSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible)
{

   bool bFirst = bDoPlay;

   for(int i = 0; i < iSongCount; i++)
   {
      AddSong(lpiaSongs[i], bFirst, bMakeVisible, false);
      //        if(pSongsSet->FindCode(lpiaSongs[i]))
      //      {
      //        pSongsSet->GetData(3);
      //      string str(pSongsSet->m_bstrPath);
      //    AddSong(str, bFirst, bMakeVisible, false);
      //  bFirst = false;
      //}
   }
   update_all_views(NULL);

   OnAddSong();

   return VMSR_SUCCESS;
}

bool PlaylistDoc::AddSong(var varFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllViews)
{
   string strPathName;
   if(varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
   {
      strPathName = varFile.propset()["url"];
   }
   else if(varFile.ca2 < ::ex1::file > () != NULL)
   {
      strPathName = System.datetime().international().get_gmt_date_time() + "." + get_document_template()->m_set["default_extension"];
   }
   else
   {
      strPathName = varFile;
   }
   m_setFile[strPathName] = varFile;

   m_wstraSong.add(strPathName);
   switch(eaddsong)
   {
   case AddSongOnly:
      break;
   case AddSongAndPlay:
   case AddSongAndPlayIfNotPlaying:
      {
         playlist_info info;
         info.m_iCurrentSong  = m_wstraSong.get_upper_bound();
         info.m_pdoc          = this;
         info.m_bMakeVisible  = bMakeVisible;
         switch(eaddsong)
         {
         case AddSongAndPlay:
            info.m_ehint      = mediaplaylist::SetCurrentSongHintDoPlay;
            break;
         case AddSongAndPlayIfNotPlaying:
            info.m_ehint      = mediaplaylist::SetCurrentSongHintPlayIfNotPlaying;
            break;
         }

         play(&info);

      }
      break;
   default:
      ASSERT(FALSE);
      return false;
   }
   if(bUpdateAllViews)
   {
      update_all_views(NULL);
   }
   OnAddSong();
   return VMSR_SUCCESS;
}

VMSRESULT PlaylistDoc::AddSong(int nSong, bool bDoPlay, bool bMakeVisible, bool bUpdateAllViews)
{
   UNREFERENCED_PARAMETER(nSong);
   UNREFERENCED_PARAMETER(bDoPlay);
   UNREFERENCED_PARAMETER(bMakeVisible);
   UNREFERENCED_PARAMETER(bUpdateAllViews);
   return VMSR_E_FAIL;
   //   CVMSApp * pApp = (CVMSApp *) &System;
   //   ASSERT(pApp != NULL);
   //  db_server* pDataCentral = db();
   //ASSERT(pDataCentral != NULL);
   //   CDBSongSet * pSongsSet = pDataCentral->GetSongsSet();
   //ASSERT(pSongsSet != NULL);

   //    if(!pSongsSet->FindCode(nSong))
   //      return VMSR_E_FAIL;

   //pSongsSet->GetData(3);
   //   string str(pSongsSet->m_bstrPath);
   //   return AddSong(str, bDoPlay, bMakeVisible, bUpdateAllViews);


}

VMSRESULT PlaylistDoc::AddSong(stringa  & stra, bool bDoPlay, bool bMakeVisible)
{
   //DBCentralInterface * pDataCentral = db();
   //ASSERT(pDataCentral != NULL);

   bool bFirst = bDoPlay;

   for(int i = 0; i < stra.get_size(); i++)
   {
      AddSong(stra.element_at(i), bFirst ? (bDoPlay ? AddSongAndPlay : AddSongOnly) : AddSongOnly, bMakeVisible, false);
      //        if(pSongsSet->FindCode(lpiaSongs[i]))
      //      {
      //        pSongsSet->GetData(3);
      //      string str(pSongsSet->m_bstrPath);
      //    AddSong(str, bFirst, bMakeVisible, false);
      //  bFirst = false;
      //}
   }
   update_all_views(NULL);

   OnAddSong();

   return VMSR_SUCCESS;

}

bool PlaylistDoc::on_open_document(var varFile) 
{
   if (!::userbase::document::on_open_document(varFile))
      return FALSE;
   update_all_views(NULL,  0, NULL);
   return TRUE;
}

void PlaylistDoc::on_close_document() 
{
   if(IsDefaultPath())
   {
      PlaylistCentral::AppGetPlaylistCentral(get_app()).OnCloseDefaultPlaylist();
   }
   ::userbase::document::on_close_document();
}

BOOL PlaylistDoc::save_modified() 
{
   PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral(get_app());
   string wstrDefault;
   playlistcentral.GetDefaultPath(wstrDefault);
   if(IsDefaultPath())
      return do_save(wstrDefault, TRUE);
   return ::userbase::document::save_modified();
}

void PlaylistDoc::update_title()
{
   PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral(get_app());
   string wstrDefault;
   playlistcentral.GetDefaultPath(wstrDefault);
   if(IsDefaultPath())
   {
      string str;
      //      str.load_string(IDS_DEFAULT_PLAYLIST_TITLE);
      set_title(str);
   }
}

/*bool PlaylistDoc::Play(bool bDoPlay, int iOffset, bool bLoop)
{

   string wstrPath;
   //   bool bOpen = false;
   int iSong = m_iCurrentSong;
   int iNextSong;
   while(PeekSongPath(wstrPath, iOffset, bLoop))
   {
      iNextSong = m_iCurrentSong;
      if(iNextSong == iSong)
         break;
      try
      {
         playlist_info info;
         
         info.m_iCurrentSong  = iNextSong;
         info.m_ehint         = bDoPlay ? mediaplaylist::SetCurrentSongHintDoPlay : mediaplaylist::SetCurrentSongHintPlayIfNotPlaying;
         info.m_bMakeVisible  = true;
         info.m_position      = 0;

         SetCurrentSong(&info);

      }
      catch(...)
      {
         continue;
      }
      break;
   }

   return false;


}*/

int PlaylistDoc::GetSongCount()
{
   return m_wstraSong.get_size();
}

bool PlaylistDoc::get_song_at(string & str, int iSong)
{
   
   if(m_wstraSong.get_count() <= 0)
      return false;

   if(iSong < 0)
      return false;

   if(iSong >= GetSongCount())
      return false;

   str = m_wstraSong.element_at(iSong);

   return true;
}

void PlaylistDoc::populate_queue(int iSong)
{

   if(iSong < 0)
        iSong = 0;
   if(iSong >= m_wstraSong.get_size())
      iSong = 0;
   if(iSong >= m_wstraSong.get_size())
      return;
   m_iaQueue.remove_all();
   gen::lemon::array a(get_app());
   if(m_bShuffle)
      iSong = 0;
   a.populate(m_iaQueue, iSong, (int) m_wstraSong.get_upper_bound(), 1, true, true, true);
   if(m_bShuffle)
   {
      if(m_iaQueue.contains(iSong))
      {
         // maintains iSong the first song in queue;
         m_iaQueue.remove(iSong);
         a.randomize(m_iaQueue);
         m_iaQueue.insert_at(0, iSong);
      }
      else
      {
         a.randomize(m_iaQueue);
      }
   }
}

bool PlaylistDoc::pick_a_song(int & iSong, string & str)
{
   
   if(m_wstraSong.get_count() <= 0)
      return false;

   if(m_iaQueue.get_count() <= 0)
   {
      if(!m_bLoop)
         return false;
      populate_queue(0);
   }

   if(m_iaQueue.get_size() <= 0)
      return false;

   iSong = m_iaQueue[0];

   m_iaQueue.remove_at(0);

   str = m_wstraSong.element_at(iSong);

   return true;

}

bool PlaylistDoc::RemoveSong(int iSong, ::userbase::view * pview)
{
   if(iSong < 0)
      return false;
   if(iSong >= GetSongCount())
      return false;

   m_wstraSong.remove_at(iSong);

   OnRemoveSong(pview);


   return true;
}


void PlaylistDoc::OnAddSong()
{

   OnChangeSongs();

}

void PlaylistDoc::OnChangeSongs(::userbase::view * pview)
{
   UNREFERENCED_PARAMETER(pview);
   if(IsDefaultPlaylist())
   {
      DoDefaultPlaylistSave();
   }

   update_all_views(NULL);

}

void PlaylistDoc::DoDefaultPlaylistSave()
{
   if(IsDefaultPlaylist())
   {
      do_save(get_path_name(), TRUE);
   }
}

bool PlaylistDoc::IsDefaultPlaylist()
{
   return IsDefaultPath();
}

void PlaylistDoc::OnRemoveSong(::userbase::view * pview)
{
   OnChangeSongs(pview);
}


bool PlaylistDoc::IsDefaultPath(const char * lpcsz)
{
   PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral(get_app());
   string strDefault;
   playlistcentral.GetDefaultPath(strDefault);
   return System.file().path().is_equal(strDefault, lpcsz);
}

bool PlaylistDoc::IsDefaultPath()
{
   return IsDefaultPath(get_path_name());
}

::userbase::view * PlaylistDoc::GetFirstAttachableView()
{
   PlaylistViewUpdateHint uh;
   uh.SetHint(PlaylistViewUpdateHint::HintGetAttachableView);
   update_all_views(NULL, 0, &uh);
   base_array < ::userbase::view *, ::userbase::view * > viewpa;
   uh.GetAttachableViews(viewpa);
   if(viewpa.get_size() > 0)
      return viewpa[0];
   else
      return NULL;

}

void PlaylistDoc::PopViews()
{
   PlaylistViewUpdateHint uh;
   uh.SetHint(PlaylistViewUpdateHint::HintPop);
   update_all_views(NULL, 0, &uh);

}

void PlaylistDoc::SetCallback(PlaylistCallbackInterface *pcallback)
{
   m_xpcallback = pcallback;
}
