// vmpLightDoc.h : interface of the MusicalPlayerLightDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPLIGHTDOC_H__DB16CEA5_CBE9_4FB8_B545_D13E1D6BF7F8__INCLUDED_)
#define AFX_VMPLIGHTDOC_H__DB16CEA5_CBE9_4FB8_B545_D13E1D6BF7F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PaneViewUpdateHint.h"


class PaneView;
class PlaylistDoc;
class CVmpLightSrvrItem;

class MusicalPlayerLightDoc :
   public OleServerDoc,
   public mediaplay::MediaDocInterface 
{
protected: // create from serialization only
	MusicalPlayerLightDoc();
	DECLARE_DYNCREATE(MusicalPlayerLightDoc)

// Attributes
protected:
//   EMode          m_emode;
public:
   bool           m_bPlay;

	/*BEGIN_INTERFACE_PART(ViewObject, IViewObject)
		INIT_INTERFACE_PART(MusicalPlayerLightDoc, ViewObject)
		STDMETHOD(Draw)(DWORD, LONG, void *, DVTARGETDEVICE *, HDC, HDC, const LPRECTL, const LPRECTL,  BOOL (*) (DWORD), DWORD);
		STDMETHOD(GetColorSet)(DWORD, LONG, void *, DVTARGETDEVICE *,  HDC, LOGPALETTE **);
      STDMETHOD(Freeze)(DWORD, LONG, void *, DWORD *);
      STDMETHOD(Unfreeze)(DWORD);
      STDMETHOD(SetAdvise)(DWORD, DWORD, IAdviseSink *);
      STDMETHOD(GetAdvise)(DWORD, DWORD, IAdviseSink **);
	END_INTERFACE_PART(PersistStorage)*/
   
	CVmpLightSrvrItem* GetEmbeddedItem()
		{ return (CVmpLightSrvrItem*)OleServerDoc::GetEmbeddedItem(); }
   DocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
// Operations
public:

// Overrides
   virtual CWinThread * HelperGetMidiPlayerCallbackThread();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicalPlayerLightDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	protected:
	virtual OleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	PaneView * GetPaneView();
	EPaneView GetViewId();
	void AttachPlaylist(PlaylistDoc * pdoc);
	//CMediaViewDataEMode GetMode();
	virtual ~MusicalPlayerLightDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(MusicalPlayerLightDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(MusicalPlayerLightDoc)
   afx_msg BOOL OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible);
   //}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMPLIGHTDOC_H__DB16CEA5_CBE9_4FB8_B545_D13E1D6BF7F8__INCLUDED_)
