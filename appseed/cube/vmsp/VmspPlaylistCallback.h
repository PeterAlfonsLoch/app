// VmpPlaylistCallback.h: interface for the CVmpLightPlaylistCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_)
#define AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class XfplayerDoc;
namespace musctrl
{
   class MusicalPlayerCentral;
}

class MusicalPlayerPlaylistCallback :
   public PlaylistCallbackInterface
{
public:
   MusicalPlayerPlaylistCallback(
      musctrl::MusicalPlayerCentral * pplayercentral,
      XfplayerDoc * pdoc);
   virtual ~MusicalPlayerPlaylistCallback();

   musctrl::MusicalPlayerCentral * m_pplayercentral;
   XfplayerDoc * m_pdoc;

   bool PlaylistOnBeforePlay(
      const char * lpcwsz, 
      mediaplaylist::ESetCurrentSongHint ehint, 
      bool bMakeVisible);

   virtual EPlaylistPlay PlaylistPlay(
      PlaylistDoc * pdoc,
      const char * lpcwsz, 
      mediaplaylist::ESetCurrentSongHint ehint, 
      bool bMakeVisible);


   virtual void PlaylistOnBeforeOpen();


};

#endif // !defined(AFX_VMPPLAYLISTCALLBACK_H__111E6E0B_1C12_441B_B46B_D45B62DC8825__INCLUDED_)
