#if !defined(AFX_OPTIONSSONGSDIRECTORIESDIALOG_H__6D8A909F_6F11_43CD_BCC0_871CA38099D8__INCLUDED_)
#define AFX_OPTIONSSONGSDIRECTORIESDIALOG_H__6D8A909F_6F11_43CD_BCC0_871CA38099D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsSongsDirectoriesDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OptionsSongDirectoriesView dialog

class CWStrArray;

class OptionsSongDirectoriesView :
	public SimpleListView,
   public VmsDataClientInterface
{
DECLARE_DYNCREATE(OptionsSongDirectoriesView)
// Construction
public:
    virtual ~OptionsSongDirectoriesView();
	bool IsModified();
	OptionsSongDirectoriesView();   // standard constructor
	//OptionsSongDirectoriesView(CWnd* pParent = NULL);   // standard constructor
	OptionsSongDirectoriesView(CWnd* pParent);   // standard constructor
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);
	BOOL Update(BOOL bSaveAndValidate = TRUE);
	

// Attributes
public:
	void SetModifiedFlag(bool bModified = true);
protected:
	bool			m_bModified;
public:
	bool Apply();
	//BOOL Create(CWnd * pwndParent = NULL);
protected:
// Dialog Data
	//{{AFX_DATA(OptionsSongDirectoriesView)
	enum { IDD = IDD_OPTIONS_SONGS_DIRECTORIES };
	//}}AFX_DATA


// Overrides
   virtual void _001InitializeFormPreData();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsSongDirectoriesView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsSongDirectoriesView)
	DECL_GEN_SIGNAL(_001OnAdd)
	DECL_GEN_SIGNAL(_001OnRemove)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSONGSDIRECTORIESDIALOG_H__6D8A909F_6F11_43CD_BCC0_871CA38099D8__INCLUDED_)
