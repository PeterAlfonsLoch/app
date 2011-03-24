// VmsseDll.cpp: implementation of the CVmsseDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../vmsp/resource.h"
#include "VmsseDll.h"
#include "util.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVmsseDll CVmsseDll::theDll;

CVmsseDll::CVmsseDll()
{
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	VERIFY(m_fontMenu.CreateFontIndirect(&ncm.lfMenuFont));

}

CVmsseDll::~CVmsseDll()
{

}

CFont * CVmsseDll::MenuV033GetFont()
{
    return theDll.GetMenuFont();
}

CFont * CVmsseDll::GetMenuFont()
{
    return &m_fontMenu;
}

VMSRESULT CVmsseDll::MenuV033CreateImageMap()
{
    UINT uiaMenuV003Map [][2] =
    {
        {ID_FILE_NEW, 0},
        {ID_FILE_OPEN, 1},
        {ID_FILE_SAVE, 2},
        {ID_VIEW_FULL_SCREEN, 7},
        {ID_TOOLS_ALBUM, 8},
        {ID_VIEW_PLAYLIST, 9},
        {ID_VIEW_LYRICS, 10},
        {ID_TOOLS_MIXER, 11},
        {ID_PLAY, 12},
        {ID_STOP, 13},
        {ID_PAUSE, 14},
        {ID_NEXTSONG, 15},
        {ID_ALBUM_NAVIGATOR, 20},
        {ID_ALBUM_FULLLIST, 21},
        {ID_ALBUM_TREELIST, 22},
        {ID_ALBUM_SEARCHLIST, 23},
        {ID_ALBUM_RESERVESONG, 24},
        {ID_CHECK, 25},
        {ID_ALBUM_DUPLICATESLIST, 27},
    };
    
    UINT uiSize = sizeof(uiaMenuV003Map) / (sizeof(UINT) * 2);
    for(UINT ui = 0; ui < uiSize; ui++)
    {
        theDll.m_relMenuV033ImageMap.Add(uiaMenuV003Map[ui][0], uiaMenuV003Map[ui][1]);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CVmsseDll::MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel)
{
    *pprel = &theDll.m_relMenuV033ImageMap;
    return VMSR_SUCCESS;
}

CImageList * CVmsseDll::MenuV033GetImageList()
{
    return &theDll.m_ilMenuV033;
}

void CVmsseDll::AlbumSongCreateImageList()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    theDll.AlbumSongCreateImageList_();

}
void CVmsseDll::AlbumSongCreateImageList_()
{
	CDC dc;
	dc.CreateDC(
		_T("DISPLAY"),
		NULL,
		NULL,
		NULL);

	int iBitCount = dc.GetDeviceCaps(BITSPIXEL);
	if(iBitCount > 8)
	{
		m_SmallImageListBitmap.DeleteObject();
		m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_256);
		m_SmallImageListBitmapV001.DeleteObject();
		m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_256);
		m_SmallImageList.Create(
			16, 16,
			ILC_COLOR32 |
			ILC_MASK,
			2,
			1);
		m_SmallImageListV001.Create(
			16, 16,
			ILC_COLOR32 |
			ILC_MASK,
			2,
			1);
        //m_SmallImageList.SetBkColor(CLR_NONE);
        m_SmallImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
		m_SmallImageList.Add(&m_SmallImageListBitmap, RGB(255, 0, 255));
        m_SmallImageListV001.SetBkColor(GetSysColor(COLOR_BTNFACE));
		m_SmallImageListV001.Add(&m_SmallImageListBitmapV001, RGB(255, 0, 255));
        
	}
	else
	{
		m_SmallImageListBitmap.DeleteObject();
		m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_16);
		m_SmallImageListBitmapV001.DeleteObject();
		m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_16);
		m_SmallImageList.Create(
			16, 16,
			ILC_COLOR32 |
			ILC_MASK,
			2,
			1);
		m_SmallImageListV001.Create(
			16, 16,
			ILC_COLOR32 |
			ILC_MASK,
			2,
			1);
        m_SmallImageList.SetBkColor(CLR_NONE);
		m_SmallImageList.Add(&m_SmallImageListBitmap, RGB(255, 0, 255));
        m_SmallImageListV001.SetBkColor(CLR_NONE);
		m_SmallImageListV001.Add(&m_SmallImageListBitmapV001, RGB(255, 0, 255));
        
	}
	dc.DeleteDC();

}

CImageList * CVmsseDll::AlbumSongGetSmallImageList()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return theDll.AlbumSongGetSmallImageList_();
}

CImageList * CVmsseDll::AlbumSongGetSmallImageList_()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return &m_SmallImageList;
}

