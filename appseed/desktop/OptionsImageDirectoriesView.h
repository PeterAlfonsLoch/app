#if !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
#define AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsImagesDirectoriesDialog.h : header file
//

// vmsguibase
//#include "vmsguibase/SimpleListCtrlData.h"

/////////////////////////////////////////////////////////////////////////////
// OptionsImageDirectoriesView dialog

class OptionsImageDirectoriesView :
	public SimpleListView,
   public VmsDataClientInterface
{
	DECLARE_DYNCREATE(OptionsImageDirectoriesView)

// Construction
public:
	bool IsModified();
	OptionsImageDirectoriesView();   // standard constructor
	//OptionsImageDirectoriesView(CWnd* pParent = NULL);   // standard constructor
	OptionsImageDirectoriesView(CWnd* pParent);   // standard constructor

// Attributes
protected:
   bool			         m_bModified;
   Ex1SimpleListData    m_listdata;
   _vms::DataKey        m_datakey;

   bool RemoveItem(Range & range);
   void GetData(AStrArray &wstra);
   void SetData(AStrArray &wstra);

   void VmsDataOnAfterChange(
      const VmsDataKeyInterface & key, int iLine, int iColumn, 
      VmsDataUpdateHint * puh);

// Operations
public:
	void _001UpdateList();
	virtual void _001InitializeFormPreData();
	void SetModifiedFlag(bool bModified = true);
	BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

// Dialog Data
	//{{AFX_DATA(OptionsImageDirectoriesView)
	enum { IDD = IDD_OPTIONS_IMAGES_DIRECTORIES };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsImageDirectoriesView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsImageDirectoriesView)
	virtual BOOL OnInitDialog();
	DECL_GEN_SIGNAL(_001OnAdd)
	DECL_GEN_SIGNAL(_001OnRemove)
	DECL_GEN_SIGNAL(_001OnEditAdd)
	DECL_GEN_SIGNAL(_001OnUpdateEditAdd)
	DECL_GEN_SIGNAL(_001OnEditRemove)
	DECL_GEN_SIGNAL(_001OnUpdateEditRemove)
	DECL_GEN_SIGNAL(_001OnCreate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
