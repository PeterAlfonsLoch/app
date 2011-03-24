#include "StdAfx.h"

PlaylistCallbackInterface::PlaylistCallbackInterface()
{
   m_pplaylistdoc = NULL;
}

PlaylistCallbackInterface::~PlaylistCallbackInterface()
{

}

EPlaylistPlay PlaylistCallbackInterface::PlaylistPlay(playlist_info * pinfo)
{
   UNREFERENCED_PARAMETER(pinfo);
   return PlaylistPlayErrorCancel;
}

bool PlaylistCallbackInterface::DoesImplementSongNumber()
{
   return false;
}

int PlaylistCallbackInterface::GetSongNumber(const wchar_t * lpcwsz)
{
   UNREFERENCED_PARAMETER(lpcwsz);
   return -1;
}

void PlaylistCallbackInterface::PlaylistPlay(int iOffset)
{
   if(m_pplaylistdoc != NULL)
   {
      playlist_info info;
      info.m_iCurrentSong     = m_pplaylistdoc->m_iCurrentSong + iOffset;
      info.m_ehint            = mediaplaylist::SetCurrentSongHintDoPlay;
      info.m_bMakeVisible     = true;
      m_pplaylistdoc->play(&info);
   }
}

void PlaylistCallbackInterface::OnClosePlayer()
{
   if(m_pplaylistdoc != NULL)
      m_pplaylistdoc->SetCallback(NULL);
}


void PlaylistCallbackInterface::PlaylistOnBeforeOpen()
{
}


void PlaylistCallbackInterface::PlaylistOnPlaybackEnd()
{
   PlaylistPlay(1);
}


bool PlaylistCallbackInterface::is_playing()
{
   return false;
}