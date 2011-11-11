#include "StdAfx.h"


namespace mediaplaylist
{


   callback_interface::callback_interface()
   {
      m_pplaylistdoc = NULL;
   }

   callback_interface::~callback_interface()
   {

   }

   e_play callback_interface::PlaylistPlay(info * pinfo)
   {
      UNREFERENCED_PARAMETER(pinfo);
      return play_error_cancel;
   }

   bool callback_interface::DoesImplementSongNumber()
   {
      return false;
   }

   int callback_interface::GetSongNumber(const wchar_t * lpcwsz)
   {
      UNREFERENCED_PARAMETER(lpcwsz);
      return -1;
   }

   void callback_interface::PlaylistPlay(int iOffset)
   {
      if(m_pplaylistdoc != NULL)
      {
         info info;
         info.m_iCurrentSong     = m_pplaylistdoc->m_iCurrentSong + iOffset;
         info.m_ehint            = mediaplaylist::hint_do_play;
         info.m_bMakeVisible     = true;
         m_pplaylistdoc->play(&info);
      }
   }

   void callback_interface::OnClosePlayer()
   {
      if(m_pplaylistdoc != NULL)
         m_pplaylistdoc->SetCallback(NULL);
   }


   void callback_interface::PlaylistOnBeforeOpen()
   {
   }


   void callback_interface::PlaylistOnPlaybackEnd()
   {
      PlaylistPlay(1);
   }


   bool callback_interface::is_playing()
   {
      return false;
   }


} // namespace mediaplaylist

