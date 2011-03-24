#if !defined(AFX_ALBUMSONGMAINWND_H__98DF7AD3_E20F_484E_8AAC_4555D486AEC5__INCLUDED_)
#define AFX_ALBUMSONGMAINWND_H__98DF7AD3_E20F_484E_8AAC_4555D486AEC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DWArray.h"
#include "DBClient.h"
#include "SplitLayout.h"


// InPlaceWndV033.h : header file
//

class CAlbumSongView;
class COptionsDialog;
class CAlbumSongList;
class CDBSongSet;
class CAlbumSearchFormView;


/////////////////////////////////////////////////////////////////////////////
// CAlbumSongMainWnd window

class CAlbumSongMainWnd
	:
	public CWnd,
	public CDBClient
{
// Construction
public:
	CAlbumSongMainWnd(CAlbumSongView * pview);

    CAlbumSongView * m_palbsngview;
// Attributes
public:
    CMenu *     m_pmenuShared;
    CAlbumSongList *        m_pfulllist;
	CSplitLayout			m_splitlayout;
	CAlbumSearchFormView *   m_psearchform;
	CAlbumSongList *        m_psearchlist;
//    CDWArray                m_dwaQueryKeys;
protected:
    
//    CDBSongSet *            m_psongsetAsynch;
//    CDBSongSet *            m_psongsetSynch;
    
//    bool                    m_bFirstProgress;
//    CComPtr <IDBAsynchStatus> m_spIdbas;


// Operations
public:
    bool IsChildValid();
    void ReserveSelectedItems(CListCtrl *pList);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlbumSongMainWnd)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool Layout(bool bForceNonVisible = false);
	bool InsertMenus();
    void SetImageLists();
//	void Populate(IDBAsynchStatus * pDbas = NULL);
	VMSRESULT UpdateList();
	UINT GetPopupMenuId(UINT nID);
	virtual BOOL Create(
        DWORD dwStyle,
        LPCRECT lprect,
        CWnd * pwndParent,
        UINT nID,
        CCreateContext * pccontext);
	virtual ~CAlbumSongMainWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAlbumSongMainWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnToolsOptionsSongs();
	void OnViewSearchForm();


    LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
    LRESULT OnVmsmV001(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMSONGMAINWND_H__98DF7AD3_E20F_484E_8AAC_4555D486AEC5__INCLUDED_)
