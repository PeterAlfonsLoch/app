#if !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
#define AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsImagesDirectoriesDialog.h : header file
//

// vmsguibase
#include "vmsguibase/SimpleListCtrlData.h"

/////////////////////////////////////////////////////////////////////////////
// OptionsFolderView dialog

class OptionsFolderView :
   public BaseSplitView
{
	DECLARE_DYNCREATE(OptionsFolderView)

// Construction
public:
	bool IsModified();
	OptionsFolderView();   // standard constructor
	//OptionsFolderView(CWnd* pParent = NULL);   // standard constructor
	OptionsFolderView(CWnd* pParent);   // standard constructor

// Attributes
protected:
   bool			         m_bModified;
   SimpleListData       m_listctrldata;
   _vms::DataKey        m_datakey;

   bool RemoveItem(Range & range);
   void GetData(WStrArray &wstra);
   void SetData(WStrArray &wstra);

   void VmsDataOnAfterChange(
      const VmsDataKeyInterface & key, int iLine, int iColumn, 
      VmsDataUpdateHint * puh);

   void CreateViews();

// Operations
public:
	void _001UpdateList();
	virtual void _001InitializeFormPreData();
	void SetModifiedFlag(bool bModified = true);
	BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

// Dialog Data
	//{{AFX_DATA(OptionsFolderView)
	enum { IDD = IDD_OPTIONS_IMAGES_DIRECTORIES };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsFolderView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsFolderView)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnEditAdd();
	afx_msg void OnUpdateEditAdd(CCmdUI* pCmdUI);
	afx_msg void OnEditRemove();
	afx_msg void OnUpdateEditRemove(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
