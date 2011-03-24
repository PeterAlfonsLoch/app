// VmpLightViewUpdateHint.h: interface for the CVmpLightViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPLIGHTVIEWUPDATEHINT_H__15434019_9C47_49BA_A9F2_2A403F0C2D6D__INCLUDED_)
#define AFX_VMPLIGHTVIEWUPDATEHINT_H__15434019_9C47_49BA_A9F2_2A403F0C2D6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMidiPlayerInterface;
class PlaylistDoc;

class CVmpLightViewUpdateHint : public CObject  
{
   DECLARE_DYNAMIC(CVmpLightViewUpdateHint)
public:
   enum EType
   {
      TypeNone,
      TypePlayIfNotPlaying,
      TypeDoPlay,
      TypeGetMidiPlayerInterface,
      TypeGetPlaylistCallback,
      TypeAttachPlaylist,
      TypeFullScreen,
      TypeInitialUpdate,
   };
   // Attributes
protected:
   EType                   m_etype;
public:
   CMidiPlayerInterface *  m_pmidiplayer;
   PlaylistDoc *          m_pplaylistdoc;
   PlaylistCallbackInterface *          m_pplaylistcallback;
   bool                    m_bFullScreen;
public:
	bool IsTypeOf(EType etype);
	void SetType(EType etype);
	CVmpLightViewUpdateHint();
	virtual ~CVmpLightViewUpdateHint();

};

#endif // !defined(AFX_VMPLIGHTVIEWUPDATEHINT_H__15434019_9C47_49BA_A9F2_2A403F0C2D6D__INCLUDED_)
