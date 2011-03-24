#pragma once



// RemoveTwoDirDuplicatesDialog form view

class RemoveTwoDirDuplicatesDialog : public CFormView
{
	DECLARE_DYNCREATE(RemoveTwoDirDuplicatesDialog)

protected:
	RemoveTwoDirDuplicatesDialog();           // protected constructor used by dynamic creation
	virtual ~RemoveTwoDirDuplicatesDialog();

public:
	enum { IDD = IDD_FILEDUP_DIR_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnEnChangeEditKeep();
public:
   CEdit m_editKeep;
public:
   CEdit m_editRemove;
public:
   afx_msg void OnBnClickedEditPasteKeep();
public:
   afx_msg void OnBnClickedEditPasteRemove();
public:
   afx_msg void OnBnClickedButtonProcess();

   void GetDirFiles(LPCTSTR lpcszDir, AStrArray & stra);
   void CalcLongPathName(String & str);
   int GetFileSize(LPCTSTR lpcszFile);
   bool RemoveDuplicate(LPCTSTR lpcszKeep, LPCTSTR lpcszRemove, LPCTSTR lpcszRemoved);
   void GetFilesSize(AStrArray & stra, BaseIntArray & ia);



public:
   afx_msg void OnBnClickedEditPasteRemoved();
public:
   CEdit m_editRemoved;
};


