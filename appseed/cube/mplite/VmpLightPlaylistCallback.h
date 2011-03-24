// VmpPlaylistCallback.h: interface for the CVmpLightPlaylistCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_)
#define AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class MusicalPlayerLightDoc;
namespace musctrl
{
   class MusicalPlayerCentral;
}

class MusicalPlayerLightPlaylistCallback :
   public PlaylistCallbackInterface
{
public:
   MusicalPlayerLightPlaylistCallback(
      musctrl::MusicalPlayerCentral * pplayercentral,
      MusicalPlayerLightDoc * pdoc);
	virtual ~MusicalPlayerLightPlaylistCallback();

   musctrl::MusicalPlayerCentral * m_pplayercentral;
   MusicalPlayerLightDoc * m_pdoc;

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

#endif // !defined(AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_)
