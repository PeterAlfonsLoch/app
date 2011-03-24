// AlbumViewUpdateHint.h: interface for the CAlbumViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALBUMVIEWUPDATEHINT_H__72D6CFDA_D54F_4A5B_A2C3_7409A0951CE5__INCLUDED_)
#define AFX_ALBUMVIEWUPDATEHINT_H__72D6CFDA_D54F_4A5B_A2C3_7409A0951CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EMediaLibraryView
{
   MediaLibraryViewNone,
   MediaLibraryViewAllMedia,
   MediaLibraryViewMediaExplorer,
   MediaLibraryViewKaraokeLibraryExplorer,
};

class MediaLibraryViewUpdateHint :
   public CObject 
{
   DECLARE_DYNAMIC(MediaLibraryViewUpdateHint)
public:

   enum EType
   {
      TypeFilter,
      TypeSetView,
      TypeGetView,
   };

	MediaLibraryViewUpdateHint();
	virtual ~MediaLibraryViewUpdateHint();

   void SetType(EType etype);
	bool IsTypeOf(EType etype);

   
   CString m_strFilter;

public:
   EMediaLibraryView    m_eview;
protected:
   EType    m_etype;

};

#endif // !defined(AFX_ALBUMVIEWUPDATEHINT_H__72D6CFDA_D54F_4A5B_A2C3_7409A0951CE5__INCLUDED_)
