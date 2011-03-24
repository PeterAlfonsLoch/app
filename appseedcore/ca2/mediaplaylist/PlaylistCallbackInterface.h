#pragma once

class PlaylistDoc;
class playlist_info;

class CLASS_DECL_ca PlaylistCallbackInterface : 
   virtual public ::radix::object
{
public:


   PlaylistDoc *                    m_pplaylistdoc;



   PlaylistCallbackInterface();
   virtual ~PlaylistCallbackInterface();

   virtual void OnClosePlayer();

   virtual bool DoesImplementSongNumber();
   virtual int GetSongNumber(const wchar_t * lpcwsz);

   virtual void PlaylistOnBeforeOpen();

   virtual void PlaylistOnPlaybackEnd();

   void PlaylistPlay(int iOffset);
   virtual EPlaylistPlay PlaylistPlay(playlist_info * pinfo);

   virtual bool is_playing();
};

