#include "StdAfx.h"
#include "RecentFileList.h"



AFX_DATADEF WCHAR afxWchNil = '\0';

#ifndef _UNICODE
inline wchar_t * _wcsinc(const wchar_t * pc)
{
   return (wchar_t *) pc + 1;
}
#endif

//#define _countof(base_array) (sizeof(base_array)/sizeof(base_array[0]))


/////////////////////////////////////////////////////////////////////////////
// lpszCanon = C:\MYAPP\DEBUGS\C\TESWIN.C
//
// cchMax   b   Result
// ------   -   ---------
//  1- 7    F   <is_empty>
//  1- 7    T   TESWIN.C
//  8-14    x   TESWIN.C
// 15-16    x   C:\...\TESWIN.C
// 17-23    x   C:\...\C\TESWIN.C
// 24-25    x   C:\...\DEBUGS\C\TESWIN.C
// 26+      x   C:\MYAPP\DEBUGS\C\TESWIN.C

AFX_STATIC void _AfxAbbreviateName(string & strCanon, int cchMax, BOOL bAtLeastName)
{
   int cchFullPath, cchFileName, cchVolName;
   const CHAR* lpszCur;
   const CHAR* lpszBase;
   string strFileName;

   lpszBase = strCanon;
   cchFullPath = lstrlen(strCanon);

   strFileName = ::ca::get_thread()->m_papp->m_psystem->file().title_(strCanon);

   // If cchMax is more than enough to hold the full path name, we're done.
   // This is probably a pretty common case, so we'll put it first.
   if (cchMax >= cchFullPath)
      return;

   cchFileName = strFileName.get_length();

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

RecentFileList::RecentFileList(UINT nStart, const char * lpszSection,
   const char * lpszEntryFormat, int nSize, 
   ::database::id key, int nMaxDispLen)
{
   UNREFERENCED_PARAMETER(lpszSection);

   ASSERT(nSize != 0);
   m_arrNames.set_size(nSize);

   m_datakey = key;

   m_nStart = nStart;
//   m_strSectionName = lpszSection;
   m_strEntryFormat = lpszEntryFormat;
   m_nMaxDisplayLength = nMaxDispLen;
}

RecentFileList::~RecentFileList()
{
}

// Operations
void RecentFileList::add(const char * lpszPathName)
{
   ASSERT(lpszPathName != NULL);
   ASSERT(AfxIsValidString(lpszPathName));

   // fully qualify the path name
   string strTemp;
   System.file_system().FullPath(strTemp, lpszPathName);

   int iMRU;
   // update the MRU list, if an existing MRU string matches file name
   for (iMRU = 0; iMRU < get_size()-1; iMRU++)
   {
      if (System.file_system().ComparePath(m_arrNames[iMRU], strTemp))
         break;      // iMRU will point to matching entry
   }
   // move MRU strings before this one down
   for (; iMRU > 0; iMRU--)
   {
      ASSERT(iMRU > 0);
      ASSERT(iMRU < get_size());
      m_arrNames[iMRU] = m_arrNames[iMRU-1];
   }
   // place this one at the beginning
   m_arrNames[0] = strTemp;
}

void RecentFileList::remove(int nIndex)
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < get_size());

   m_arrNames[nIndex].Empty();
   int iMRU;
   for (iMRU = nIndex; iMRU < get_size()-1; iMRU++)
      m_arrNames[iMRU] = m_arrNames[iMRU+1];

   ASSERT(iMRU < get_size());
   m_arrNames[iMRU].Empty();
}

BOOL RecentFileList::GetDisplayName(string & strName, int nIndex,
   const char * lpszCurDir, int nCurDir, BOOL bAtLeastName) const
{
   UNREFERENCED_PARAMETER(strName);
   UNREFERENCED_PARAMETER(nIndex);
   UNREFERENCED_PARAMETER(lpszCurDir);
   UNREFERENCED_PARAMETER(nCurDir);
   UNREFERENCED_PARAMETER(bAtLeastName);
/*   ASSERT(lpszCurDir == NULL || AfxIsValidString(lpszCurDir, nCurDir));

   ASSERT(nIndex < get_size());
   if (m_arrNames[nIndex].is_empty())
      return FALSE;

   string str1;
   str1 = m_arrNames[nIndex];
   string str2;
   // nLenDir is the length of the directory part of the full path
   int nLenDir = str1.get_length() - (Ex1::GetApp()->file_system()->GetFileName(str1, str2) - 1);
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
      Ex1::GetApp()->file_system()->GetFileTitle(lpch+nCurDir, szTemp, _countof(szTemp));
      lstrcpyn(lpch, szTemp, _MAX_PATH);
   }
   else if (m_nMaxDisplayLength != -1)
   {
      // strip the extension if the system calls for it
      CHAR szTemp[_MAX_PATH];
      Ex1::GetApp()->file_system()->GetFileTitle(lpch+nLenDir, szTemp, _countof(szTemp));
      lstrcpyn(lpch+nLenDir, szTemp, _MAX_PATH-nLenDir);

      // abbreviate name based on what will fit in limited space
      _AfxAbbreviateName(lpch, m_nMaxDisplayLength, bAtLeastName);
   }
   strName.ReleaseBuffer();*/
   return TRUE;
}

void RecentFileList::UpdateMenu(cmd_ui * pcmdui)
{

   ::userbase::menu* pMenu = pcmdui->m_pMenu;

   if(pcmdui->m_pSubMenu != NULL)
      pMenu = pcmdui->m_pSubMenu;
//xxx   if (m_strOriginal.is_empty() && pMenu != NULL)
//xxx      pMenu->GetMenuString(pcmdui->m_nID, m_strOriginal, MF_BYCOMMAND);

   if (m_arrNames[0].is_empty())
   {
      // no MRU files
//      if (!m_strOriginal.is_empty())
//         pcmdui->SetText(m_strOriginal);
      pcmdui->Enable(FALSE);
      return;
   }

   if (pMenu == NULL)
      return;

   //for (int iMRU = 0; iMRU < get_size(); iMRU++)
/*   pMenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

   string strCurDir;
   win::GetCurrentDirectory(strCurDir);
   int nCurDir = lstrlen(strCurDir);
   ASSERT(nCurDir >= 0);
   strCurDir += "\\";

   pcmdui->m_nID = ID_FILE_MRU_FILE1;

   string strName;
   string strTemp;
   for (int iMRU = 0; iMRU < get_size(); iMRU++)
   {
      if (!GetDisplayName(strName, iMRU, strCurDir, nCurDir))
         break;

      // double up any '&' characters so they are not underlined
      const char * lpszSrc = strName;
      LPTSTR lpszDest = strTemp.GetBuffer(strName.get_length()*2);
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
            pcmdui->m_nIndex++,
            MF_BYPOSITION,
            pcmdui->m_nID++,
            string(buf) + strTemp);

      //pcmdui->m_pMenu->InsertMenu(pcmdui->m_nIndex++,
      //   MF_STRING | MF_BYPOSITION, pcmdui->m_nID++,
      //   string(buf) + strTemp);
   }

   // update end menu count
   pcmdui->m_nIndex--; // point to last menu added
   pcmdui->m_nIndexMax = pcmdui->m_pMenu->GetMenuItemCount();

   pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled*/
}

void RecentFileList::WriteList()
{
   //ASSERT(!m_strSectionName.is_empty());
   //ASSERT(!m_strEntryFormat.is_empty());
   /*LPTSTR pszEntry = new char[m_strEntryFormat.get_length()+5];
   application* pApp = &System;
   pApp->WriteProfileString(m_strSectionName, NULL, NULL);
   for (int iMRU = 0; iMRU < get_size(); iMRU++)
   {
      wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
      if (!m_arrNames[iMRU].is_empty())
      {
         
      }
   }
   delete[] pszEntry;*/

   data_set(m_datakey, ::ca::system::idEmpty, m_arrNames);
}

void RecentFileList::ReadList()
{
//   ASSERT(!m_strSectionName.is_empty());
   ASSERT(!m_strEntryFormat.is_empty());
/*   LPTSTR pszEntry = new char[m_strEntryFormat.get_length()+5];
   application* pApp = &System;
   for (int iMRU = 0; iMRU < get_size(); iMRU++)
   {
      wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
      m_arrNames[iMRU] = pApp->GetProfileString(
         m_strSectionName, pszEntry, &afxChNil);
   }
   delete[] pszEntry;*/

   data_get(m_datakey, ::ca::system::idEmpty, m_arrNames);
}

/////////////////////////////////////////////////////////////////////////////
