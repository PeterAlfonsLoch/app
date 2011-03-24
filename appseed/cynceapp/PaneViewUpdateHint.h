// PaneViewUpdateHint.h: interface for the PaneViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANEVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_)
#define AFX_PANEVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum EPaneView
{
   PaneViewNone,
   PaneViewContextMenu,
   PaneViewKaraoke,
   PaneViewFileManager,
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};


class PaneViewUpdateHint :
   public CObject  
{
public:
   enum EType
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
   };
   DECLARE_DYNAMIC(PaneViewUpdateHint)
public:
	void SetType(EType etype);
	bool IsTypeOf(EType etype);

	PaneViewUpdateHint();
	virtual ~PaneViewUpdateHint();

   EPaneView m_eview;
protected:
   EType m_etype;

};

#endif // !defined(AFX_PANEVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_)
