// RecentFileList.h: interface for the RecentFileList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECENTFILELIST_H__E1E7211F_9FE6_4E9D_8CD2_6C85DD69B915__INCLUDED_)
#define AFX_RECENTFILELIST_H__E1E7211F_9FE6_4E9D_8CD2_6C85DD69B915__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// RecentFileList

#define AFX_ABBREV_FILENAME_LEN 30

class RecentFileList :
   public VmsDataClientInterface
{
// Constructors
public:
	RecentFileList(UINT nStart, LPCTSTR lpszSection,
		LPCTSTR lpszEntryFormat, int nSize,
      VmsDataKeyInterface & key,
		int nMaxDispLen = AFX_ABBREV_FILENAME_LEN);

// Attributes
	int GetSize() const;
	CString& operator[](int nIndex);

// Operations
	virtual void Remove(int nIndex);
	virtual void Add(LPCSTR lpszPathName);
	BOOL GetDisplayName(CString& strName, int nIndex,
		LPCSTR lpszCurDir, int nCurDir, BOOL bAtLeastName = TRUE) const;
	virtual void UpdateMenu(CCmdUI* pCmdUI);
	virtual void ReadList();    // reads from registry or ini file
	virtual void WriteList();   // writes to registry or ini file

// Implementation
	virtual ~RecentFileList();

	//int m_nSize;                // contents of the MRU list
	//WString* m_arrNames;
   AStrArray  m_arrNames;
	//CString m_strSectionName;   // for saving
	CString m_strEntryFormat;
	UINT m_nStart;              // for displaying
	int m_nMaxDisplayLength;
	CString m_strOriginal;      // original menu item contents
   _vms::DataKey       m_datakey;
};

inline int RecentFileList::GetSize() const
	{ return m_arrNames.GetSize(); }
inline CString& RecentFileList::operator[](int nIndex)
	{ ASSERT(nIndex < GetSize()); return m_arrNames[nIndex]; }

#endif // !defined(AFX_RECENTFILELIST_H__E1E7211F_9FE6_4E9D_8CD2_6C85DD69B915__INCLUDED_)
