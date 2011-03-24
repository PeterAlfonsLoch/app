// RecentFileList.cpp: implementation of the RecentFileList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecentFileList.h"



AFX_DATADEF WCHAR afxWchNil = '\0';
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef _UNICODE
inline LPWSTR _wcsinc(LPCWSTR pc)
{
	return (LPWSTR) pc + 1;
}
#endif

#define _countof(array) (sizeof(array)/sizeof(array[0]))


/////////////////////////////////////////////////////////////////////////////
// lpszCanon = C:\MYAPP\DEBUGS\C\TESWIN.C
//
// cchMax   b   Result
// ------   -   ---------
//  1- 7    F   <empty>
//  1- 7    T   TESWIN.C
//  8-14    x   TESWIN.C
// 15-16    x   C:\...\TESWIN.C
// 17-23    x   C:\...\C\TESWIN.C
// 24-25    x   C:\...\DEBUGS\C\TESWIN.C
// 26+      x   C:\MYAPP\DEBUGS\C\TESWIN.C

AFX_STATIC void AFXAPI _AfxAbbreviateName(CString & strCanon, int cchMax, BOOL bAtLeastName)
{
	int cchFullPath, cchFileName, cchVolName;
	const CHAR* lpszCur;
	const CHAR* lpszBase;
	CString strFileName;

	lpszBase = strCanon;
	cchFullPath = lstrlen(strCanon);

   Ex1::GetApp()->GetFileSystem()->GetFileName(strCanon, strFileName);

	// If cchMax is more than enough to hold the full path name, we're done.
	// This is probably a pretty common case, so we'll put it first.
	if (cchMax >= cchFullPath)
		return;

	// If cchMax isn't enough to hold at least the basename, we're done
	if (cchMax < cchFileName)
	{
		strCanon = (bAtLeastName) ? strFileName : "";
		return;
	}

	// Calculate the length of the volume name.  Normally, this is two characters
	// (e.g., "C:", "D:", etc.), but for a UNC name, it could be more (e.g.,
	// "\\server\share").
	//
	// If cchMax isn't enough to hold at least <volume_name>\...\<base_name>, the
	// result is the base filename.

	lpszCur = lpszBase + 2;                 // Skip "C:" or leading "\\"

	if (lpszBase[0] == '\\' && lpszBase[1] == '\\') // UNC pathname
	{
		// First skip to the '\' between the server name and the share name,
		while (*lpszCur != '\\')
		{
			lpszCur = _tcsinc(lpszCur);
			ASSERT(*lpszCur != '\0');
		}
	}
	// if a UNC get the share name, if a drive get at least one directory
	ASSERT(*lpszCur == '\\');
	// make sure there is another directory, not just c:\filename.ext
	if (cchFullPath - cchFileName > 3)
	{
		lpszCur = _tcsinc(lpszCur);
		while (*lpszCur != '\\')
		{
			lpszCur = _tcsinc(lpszCur);
			ASSERT(*lpszCur != '\0');
		}
	}
	ASSERT(*lpszCur == '\\');

	cchVolName = lpszCur - lpszBase;
	if (cchMax < cchVolName + 5 + cchFileName)
	{
		strCanon = strFileName;
		return;
	}

	// Now loop through the remaining directory components until something
	// of the form <volume_name>\...\<one_or_more_dirs>\<base_name> fits.
	//
	// Assert that the whole filename doesn't fit -- this should have been
	// handled earlier.

	ASSERT(cchVolName + (int)lstrlen(lpszCur) > cchMax);
	while (cchVolName + 4 + (int)lstrlen(lpszCur) > cchMax)
	{
		do
		{
			lpszCur = _tcsinc(lpszCur);
			ASSERT(*lpszCur != '\0');
		}
		while (*lpszCur != '\\');
	}

	// Form the resultant string and we're done.
	strCanon = strCanon.Mid(0, cchVolName);
	strCanon += "\\...";
	strCanon += lpszCur;
}

/////////////////////////////////////////////////////////////////////////////
// RecentFileList

RecentFileList::RecentFileList(UINT nStart, LPCTSTR lpszSection,
	LPCTSTR lpszEntryFormat, int nSize, 
   VmsDataKeyInterface & key, int nMaxDispLen)
{
	ASSERT(nSize != 0);
	m_arrNames.SetSize(nSize);

   m_datakey = key;

	m_nStart = nStart;
//	m_strSectionName = lpszSection;
	m_strEntryFormat = lpszEntryFormat;
	m_nMaxDisplayLength = nMaxDispLen;
}

RecentFileList::~RecentFileList()
{
}

// Operations
void RecentFileList::Add(LPCTSTR lpszPathName)
{
	ASSERT(lpszPathName != NULL);
	ASSERT(AfxIsValidString(lpszPathName));

	// fully qualify the path name
	CString strTemp;
   Ex1::GetApp()->GetFileSystem()->FullPath(strTemp, lpszPathName);

   int iMRU;
	// update the MRU list, if an existing MRU string matches file name
	for (iMRU = 0; iMRU < GetSize()-1; iMRU++)
	{
		if (Ex1::GetApp()->GetFileSystem()->ComparePath(m_arrNames[iMRU], strTemp))
			break;      // iMRU will point to matching entry
	}
	// move MRU strings before this one down
	for (; iMRU > 0; iMRU--)
	{
		ASSERT(iMRU > 0);
		ASSERT(iMRU < GetSize());
		m_arrNames[iMRU] = m_arrNames[iMRU-1];
	}
	// place this one at the beginning
	m_arrNames[0] = strTemp;
}

void RecentFileList::Remove(int nIndex)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetSize());

	m_arrNames[nIndex].Empty();
   int iMRU;
	for (int iMRU = nIndex; iMRU < GetSize()-1; iMRU++)
		m_arrNames[iMRU] = m_arrNames[iMRU+1];

	ASSERT(iMRU < GetSize());
	m_arrNames[iMRU].Empty();
}

BOOL RecentFileList::GetDisplayName(CString& strName, int nIndex,
	LPCTSTR lpszCurDir, int nCurDir, BOOL bAtLeastName) const
{
/*	ASSERT(lpszCurDir == NULL || AfxIsValidString(lpszCurDir, nCurDir));

	ASSERT(nIndex < GetSize());
	if (m_arrNames[nIndex].IsEmpty())
		return FALSE;

	CString str1;
	str1 = m_arrNames[nIndex];
   CString str2;
	// nLenDir is the length of the directory part of the full path
	int nLenDir = str1.GetLength() - (Ex1::GetApp()->GetFileSystem()->GetFileName(str1, str2) - 1);
	BOOL bSameDir = FALSE;
	if (nLenDir == nCurDir)
	{
		CHAR chSave = lpch[nLenDir];
		lpch[nCurDir] = 0;  // terminate at same location as current dir
		bSameDir = lstrcmpi(lpszCurDir, lpch) == 0;
		lpch[nLenDir] = chSave;
	}
	// copy the full path, otherwise abbreviate the name
	if (bSameDir)
	{
		// copy file name only since directories are same
		CHAR szTemp[_MAX_PATH];
		Ex1::GetApp()->GetFileSystem()->GetFileTitle(lpch+nCurDir, szTemp, _countof(szTemp));
		lstrcpyn(lpch, szTemp, _MAX_PATH);
	}
	else if (m_nMaxDisplayLength != -1)
	{
		// strip the extension if the system calls for it
		CHAR szTemp[_MAX_PATH];
		Ex1::GetApp()->GetFileSystem()->GetFileTitle(lpch+nLenDir, szTemp, _countof(szTemp));
		lstrcpyn(lpch+nLenDir, szTemp, _MAX_PATH-nLenDir);

		// abbreviate name based on what will fit in limited space
		_AfxAbbreviateName(lpch, m_nMaxDisplayLength, bAtLeastName);
	}
	strName.ReleaseBuffer();*/
	return TRUE;
}

void RecentFileList::UpdateMenu(CCmdUI* pCmdUI)
{

	CMenu* pMenu = pCmdUI->m_pMenu;

   if(pCmdUI->m_pSubMenu != NULL)
      pMenu = pCmdUI->m_pSubMenu;
//xxx	if (m_strOriginal.IsEmpty() && pMenu != NULL)
//xxx		pMenu->GetMenuString(pCmdUI->m_nID, m_strOriginal, MF_BYCOMMAND);

	if (m_arrNames[0].IsEmpty())
	{
		// no MRU files
//		if (!m_strOriginal.IsEmpty())
//			pCmdUI->SetText(m_strOriginal);
		pCmdUI->Enable(FALSE);
		return;
	}

	if (pMenu == NULL)
		return;

	//for (int iMRU = 0; iMRU < GetSize(); iMRU++)
	pMenu->DeleteMenu(pCmdUI->m_nID, MF_BYCOMMAND);

	CString strCurDir;
   win::GetCurrentDirectory(strCurDir);
	int nCurDir = lstrlen(strCurDir);
	ASSERT(nCurDir >= 0);
	strCurDir += "\\";

   pCmdUI->m_nID = ID_FILE_MRU_FILE1;

	CString strName;
	CString strTemp;
	for (int iMRU = 0; iMRU < GetSize(); iMRU++)
	{
		if (!GetDisplayName(strName, iMRU, strCurDir, nCurDir))
			break;

		// double up any '&' characters so they are not underlined
		LPCTSTR lpszSrc = strName;
		LPTSTR lpszDest = strTemp.GetBuffer(strName.GetLength()*2);
		while (*lpszSrc != 0)
		{
			if (*lpszSrc == '&')
				*lpszDest++ = '&';
			if (_istlead(*lpszSrc))
				*lpszDest++ = *lpszSrc++;
			*lpszDest++ = *lpszSrc++;
		}
		*lpszDest = 0;
		strTemp.ReleaseBuffer();

		// insert mnemonic + the file name
		CHAR buf[10];
		wsprintf(buf, "&%d ", (iMRU+1+m_nStart) % 10);

      SimpleMenu::_InsertMenuItem(
            *pMenu,
            *pMenu,
            pCmdUI->m_nIndex++,
            MF_BYPOSITION,
            pCmdUI->m_nID++,
            CString(buf) + strTemp);

		//pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex++,
		//	MF_STRING | MF_BYPOSITION, pCmdUI->m_nID++,
		//	WString(buf) + strTemp);
	}

	// update end menu count
	pCmdUI->m_nIndex--; // point to last menu added
	pCmdUI->m_nIndexMax = pCmdUI->m_pMenu->GetMenuItemCount();

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
}

void RecentFileList::WriteList()
{
	//ASSERT(!m_strSectionName.IsEmpty());
	//ASSERT(!m_strEntryFormat.IsEmpty());
	/*LPTSTR pszEntry = new TCHAR[m_strEntryFormat.GetLength()+5];
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString(m_strSectionName, NULL, NULL);
	for (int iMRU = 0; iMRU < GetSize(); iMRU++)
	{
		wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
		if (!m_arrNames[iMRU].IsEmpty())
		{
			
		}
	}
	delete[] pszEntry;*/

   VmsDataSet(m_datakey, 0, 0, m_arrNames);
}

void RecentFileList::ReadList()
{
//	ASSERT(!m_strSectionName.IsEmpty());
	ASSERT(!m_strEntryFormat.IsEmpty());
/*	LPTSTR pszEntry = new TCHAR[m_strEntryFormat.GetLength()+5];
	CWinApp* pApp = AfxGetApp();
	for (int iMRU = 0; iMRU < GetSize(); iMRU++)
	{
		wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
		m_arrNames[iMRU] = pApp->GetProfileString(
			m_strSectionName, pszEntry, &afxChNil);
	}
	delete[] pszEntry;*/

   VmsDataGet(m_datakey, 0, 0, m_arrNames);
}

/////////////////////////////////////////////////////////////////////////////
