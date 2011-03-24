// VmsseDll.h: interface for the CVmsseDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VmsseDll_H__7AD0F994_3BD1_4C03_8DEB_E7E934C69B8E__INCLUDED_)
#define AFX_VmsseDll_H__7AD0F994_3BD1_4C03_8DEB_E7E934C69B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelationV001.h"
#include "..\vms\vms.h"
#include "resource.h"

class CVmsseDll
{
    static CVmsseDll theDll;
public:
	CVmsseDll();
	virtual ~CVmsseDll();
protected:
    CRelationV001<UINT, UINT, UINT, UINT> m_relMenuV033ImageMap;
    CImageList                            m_ilMenuV033;
    CFont                                 m_fontMenu;
	CImageList		        m_SmallImageList;
	CBitmap			        m_SmallImageListBitmap;
    CImageList              m_SmallImageListV001;
    CBitmap			        m_SmallImageListBitmapV001;
    
public:
	CImageList * AlbumSongGetSmallImageList_();
    void AlbumSongCreateImageList_();
	static CImageList * AlbumSongGetSmallImageList();
	static void AlbumSongCreateImageList();
  	static CImageList * MenuV033GetImageList();
	static VMSRESULT MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel);
	static VMSRESULT MenuV033CreateImageMap();
    static CFont * MenuV033GetFont();
    CFont * GetMenuFont();
};

#endif // !defined(AFX_VmsseDll_H__7AD0F994_3BD1_4C03_8DEB_E7E934C69B8E__INCLUDED_)
