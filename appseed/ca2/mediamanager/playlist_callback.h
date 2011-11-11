#pragma once

namespace mediamanager
{

class playlist_callback :
   public PlaylistCallbackInterface
{
public:
   playlist_callback(
      musctrl::MusicalPlayerCentral * pplayercentral,
      mediaplay::MediaDocInterface * pdoc);
	virtual ~playlist_callback();

   musctrl::MusicalPlayerCentral * m_pplayercentral;
   mediaplay::MediaDocInterface * m_pdoc;

	bool PlaylistOnBeforePlay(
		LPCSTR lpcwsz, 
		_vmspl::ESetCurrentSongHint ehint, 
		bool bMakeVisible);

	virtual EPlaylistPlay PlaylistPlay(
		PlaylistDoc * pdoc,
		LPCSTR lpcwsz, 
		_vmspl::ESetCurrentSongHint ehint, 
		bool bMakeVisible);


   virtual void PlaylistOnBeforeOpen();

};

} // namespace mediamanager