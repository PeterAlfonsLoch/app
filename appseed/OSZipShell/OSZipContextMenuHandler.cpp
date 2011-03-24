// OSZipContextMenuHandler.cpp : implementation file
//

#include "stdafx.h"
#include "OSZipShell.h"
#include "OSZipContextMenuHandler.h"
#include "SplitFileDialog.h"

#define UNCOMPRESS 5

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GetFileTitle(CString str)
{
    int iFind = str.ReverseFind('\\');
    str = str.Mid(iFind + 1);
    return str;
}

CString GetZipPath(CStringArray & straFiles)
{
   CString str;
   if(straFiles.GetSize() == 1)
   {
      str = straFiles[0];
      int iFindDot = str.ReverseFind('.');
      int iFindSlash = str.ReverseFind('\\');
      if(iFindDot > iFindSlash)
      {
         str = str.Left(iFindDot) + ".zip";
      }
      else
      {
         str = ".zip";
      }
   }
   else if(straFiles.GetSize() > 1)
   {
      str = straFiles[0];
      int iFind1 = str.ReverseFind('\\');
      CString str2 = str.Left(iFind1);
      int iFind2 = str2.ReverseFind('\\');
      CString strName = str2.Mid(iFind2 + 1);
      strName.Replace(":", "");
      strName += ".zip";
      str = str.Left(iFind1) + '\\' + strName;
   }
   return str;
}

CString GetZipTitle(CStringArray & straFiles)
{
   return GetFileTitle(GetZipPath(straFiles));
}

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler

IMPLEMENT_DYNCREATE(OSZipContextMenuHandler, CCmdTarget)

OSZipContextMenuHandler::OSZipContextMenuHandler()
{

   m_window.Create();
   EnableAutomation();
   
   // To keep the application running as long as an OLE automation 
   //	object is active, the constructor calls AfxOleLockApp.
   
   AfxOleLockApp();
}

OSZipContextMenuHandler::~OSZipContextMenuHandler()
{
   // To terminate the application when all objects created with
   // 	with OLE automation, the destructor calls AfxOleUnlockApp.
   
   AfxOleUnlockApp();
}

void OSZipContextMenuHandler::OnFinalRelease()
{
   // When the last reference for an automation object is released
   // OnFinalRelease is called.  The base class will automatically
   // deletes the object.  Add additional cleanup required for your
   // object before calling the base class.
   
   CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(OSZipContextMenuHandler, CCmdTarget)
//{{AFX_MSG_MAP(OSZipContextMenuHandler)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(OSZipContextMenuHandler, CCmdTarget)
//{{AFX_DISPATCH_MAP(OSZipContextMenuHandler)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOSZipContextMenuHandler to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E6E88C89-911C-4EC2-93B2-DF1D1BAFB12D}
static const IID IID_IOSZipContextMenuHandler =
{ 0xe6e88c89, 0x911c, 0x4ec2, { 0x93, 0xb2, 0xdf, 0x1d, 0x1b, 0xaf, 0xb1, 0x2d } };

BEGIN_INTERFACE_MAP(OSZipContextMenuHandler, CCmdTarget)
INTERFACE_PART(OSZipContextMenuHandler, IID_IOSZipContextMenuHandler, Dispatch)
INTERFACE_PART(OSZipContextMenuHandler, IID_IShellExtInit, ShellExtInit)
INTERFACE_PART(OSZipContextMenuHandler, IID_IContextMenu, ContextMenu)
END_INTERFACE_MAP()

// {D8A11407-DA73-47B3-B09D-60A99D688BC4}
IMPLEMENT_OLECREATE(OSZipContextMenuHandler, "fontopus.OSZip.ContextMenuHandler", 0xd8a11407, 0xda73, 0x47b3, 0xb0, 0x9d, 0x60, 0xa9, 0x9d, 0x68, 0x8b, 0xc4)

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler message handlers

ULONG FAR EXPORT OSZipContextMenuHandler::XShellExtInit::AddRef()
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ShellExtInit)
      return pThis->ExternalAddRef();
}

ULONG FAR EXPORT OSZipContextMenuHandler::XShellExtInit::Release()
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ShellExtInit)
      return pThis->ExternalRelease();
}

HRESULT FAR EXPORT OSZipContextMenuHandler::XShellExtInit::QueryInterface(
                                                                          REFIID iid, void FAR* FAR* ppvObj)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ShellExtInit)
      return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

HRESULT OSZipContextMenuHandler::XShellExtInit::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ShellExtInit)
      
      COleDataObject dataobj;
   
   dataobj.Attach(lpdobj, FALSE);
   
   HGLOBAL  hGlobal;
   LPCSTR   pData;
   
   pThis->m_straFiles.RemoveAll();
   
   FORMATETC fmtetc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
   STGMEDIUM stgmed;
   TCHAR szFileName[_MAX_PATH + 1];
   
   if(dataobj.GetData(CF_HDROP, &stgmed, &fmtetc))
   {
      HDROP hdrop = (HDROP)GlobalLock(stgmed.hGlobal);
      if (NULL != hdrop)
      {
         UINT nFiles = DragQueryFile(hdrop, (UINT)-1, NULL, 0);
         
         for(UINT nNames = 0; nNames < nFiles; nNames++)
         {
            ZeroMemory(szFileName, _MAX_PATH + 1);
            DragQueryFile(hdrop, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);
            pThis->m_straFiles.Add(szFileName);
         }
         GlobalUnlock(hdrop);
      }
      ReleaseStgMedium(&stgmed);
      return S_OK;
   }
   
   return E_FAIL;
}

ULONG FAR EXPORT OSZipContextMenuHandler::XContextMenu::AddRef()
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      return pThis->ExternalAddRef();
}

ULONG FAR EXPORT OSZipContextMenuHandler::XContextMenu::Release()
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      return pThis->ExternalRelease();
}

HRESULT FAR EXPORT OSZipContextMenuHandler::XContextMenu::QueryInterface(
                                                                         REFIID iid, void FAR* FAR* ppvObj)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

#define IDM_DISPLAY 3

HRESULT FAR EXPORT OSZipContextMenuHandler::XContextMenu::QueryContextMenu(HMENU hMenu,
                                                                           UINT indexMenu,
                                                                           UINT idCmdFirst,
                                                                           UINT idCmdLast,
                                                                           UINT uFlags)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      if(!(CMF_DEFAULTONLY & uFlags))
      {
         int iCommandCount = pThis->GetMenuCommandCount();
         int iResultCount = 0;
         for(int iCommandIndex = 0; iCommandIndex < iCommandCount; iCommandIndex++)
         {
            CString strCommand = pThis->GetMenuCommand(iCommandIndex);
            if(strCommand.IsEmpty())
            {
               continue;
            }
            
            InsertMenu(hMenu, 
               indexMenu, 
               MF_STRING | MF_BYPOSITION, 
               idCmdFirst + IDM_DISPLAY + iCommandIndex, 
               strCommand);
            iResultCount++;
         }
         if(iResultCount == 0)
            return E_FAIL;

         return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_DISPLAY + iCommandCount));
         
         //        StrCpyA(m_pszVerb, "display"); 
         //   StrCpyW(m_pwszVerb, L"display"); 
         
         
      }
      
      return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

HRESULT FAR EXPORT OSZipContextMenuHandler::XContextMenu::GetCommandString(UINT idCommand,
                                                                           UINT uFlags,
                                                                           UINT * lpReserved,
                                                                           LPSTR pszName,
                                                                           UINT uMaxNameLen)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      HRESULT  hr = E_INVALIDARG;
   
   if(idCommand != IDM_DISPLAY && idCommand != IDM_DISPLAY + 1)
   {
      return hr;
   }
   
   switch(uFlags)
   {
   case GCS_HELPTEXTA:
      lstrcpynA(pszName, "Display File Name", uMaxNameLen);
      hr = S_OK;
      break; 
      
   case GCS_HELPTEXTW: 
      lstrcpynW((LPWSTR)pszName, L"Display File Name",  
         uMaxNameLen); 
      hr = S_OK;
      break; 
      
   case GCS_VERBA:
      //            lstrcpynA(pszName, m_pszVerb, uMaxNameLen); 
      hr = S_OK;
      break; 
      
   case GCS_VERBW:
      //          lstrcpynW((LPWSTR)pszName, m_pwszVerb, uMaxNameLen); 
      hr = S_OK;
      break; 
      
   default:
      hr = S_OK;
      break; 
   }
   return hr;
}

HRESULT FAR EXPORT OSZipContextMenuHandler::XContextMenu::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
   METHOD_PROLOGUE(OSZipContextMenuHandler, ContextMenu)
      BOOL fEx = FALSE;
   BOOL fUnicode = FALSE;
   
   if(lpcmi->cbSize = sizeof(CMINVOKECOMMANDINFOEX))
   {
      fEx = TRUE;
      if((lpcmi->fMask & CMIC_MASK_UNICODE))
      {
         fUnicode = TRUE;
      }
   }
   
   /*    if( !fUnicode && HIWORD(lpcmi->lpVerb))
   {
   if(StrCmpIA(lpcmi->lpVerb, m_pszVerb))
   {
   return E_FAIL;
   }
}*/
   
/*else if( fUnicode && HIWORD(((CMINVOKECOMMANDINFOEX *) lpcmi)>lpVerbW))
{
if(StrCmpIW(((CMINVOKECOMMANDINFOEX *)lpcmi)>lpVerbW, m_pwszVerb))
{
return E_FAIL;
}
}*/
   
   //else if(LOWORD(lpcmi>lpVerb) != IDM_DISPLAY)
   if(LOWORD(lpcmi->lpVerb) < IDM_DISPLAY ||
      LOWORD(lpcmi->lpVerb) >= IDM_DISPLAY + pThis->GetMenuCommandCount())
   {
      return E_FAIL;
   }
   
   else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY)
   {
      if(pThis->m_straFiles.GetSize() == 1)
      {
         CString strTopic;
         strTopic = pThis->m_straFiles[0];
         
         CString strDirectory;
         
         int iFind;
         int iFind1 = strTopic.ReverseFind('\\');
         int iFind2 = strTopic.ReverseFind('/');
         
         iFind = max(iFind1, iFind2);
         
         if(iFind > 0)
         {
            strDirectory = strTopic.Left(iFind);
         }
         
         
         LPCTSTR lpcszFolder = NULL;
         if(!strDirectory.IsEmpty())
            lpcszFolder = strDirectory;
         
         CString strTitle;
         strTitle = strTopic.Mid(iFind + 1);
         
         // Calculate temp dir
         CString strTempPath;
         ::GetTempPath(1024, strTempPath.GetBuffer(2048));
         strTempPath.ReleaseBuffer();
         if(strTempPath[strTempPath.GetLength() - 1] != '\\')
         {
            strTempPath += "\\";
         }
         strTempPath += "OSZipShell\\";
         
         DWORD dw = ::GetFileAttributes(strTempPath);
         if((dw & FILE_ATTRIBUTE_DIRECTORY) == 0 || dw == -1)
         {
            if(dw != -1)
            {
               ::DeleteFile(strTempPath);
            }
            ::CreateDirectory(strTempPath, NULL);
            
         }
         
         // Calculate tar file
         CString strTar;
         
         strTar = strTempPath + strTitle + ".tar";
         //          ::GetTempFileName(strTempPath, "tar", 0, strTar.GetBuffer(4096));
         //        strTar.ReleaseBuffer();
         
         CString strFileName;
         ::GetModuleFileName(AfxGetApp()->m_hInstance, strFileName.GetBufferSetLength(MAX_PATH * 4), MAX_PATH * 4);
         strFileName.ReleaseBuffer();

         CString strPath;
         LPTSTR lpszFilePath = strPath.GetBufferSetLength(MAX_PATH * 4);
         LPTSTR lpszFilePart;
         ::GetFullPathName(strFileName, MAX_PATH * 4, lpszFilePath, &lpszFilePart);
         lpszFilePart[0] = '\0';
         strPath.ReleaseBuffer();

         CString strDir(strPath);


         
         CString strParams;
         strParams.Format("%sbin\\compress\\tar -c -f\"%s\" -C\"%s\" \"%s\"", strDir, strTitle + ".tar", lpcszFolder, strTitle);
         
         PROCESS_INFORMATION pi;
         STARTUPINFO si;
         memset(&si, 0, sizeof(si));
         si.cb = sizeof(si);
         if(CreateProcess(
            NULL,
            (LPTSTR) (LPCTSTR) strParams,
            NULL,
            NULL,
            FALSE,
            NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
            NULL,
            strTempPath,
            &si,
            &pi))
         {
            
            DWORD dwExitCode;
            while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
            {
               if(dwExitCode != STILL_ACTIVE)
               {
                  break;
               }
               Sleep(200);
            }
            strParams.Format("%sbin\\compress\\bzip2 \"%s\"",  strDir, strTar);
            memset(&si, 0, sizeof(si));
            si.cb = sizeof(si);
            if(CreateProcess(
               NULL,
               (LPTSTR) (LPCTSTR) strParams,
               NULL,
               NULL,
               FALSE,
               NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
               NULL,
               strTempPath,
               &si,
               &pi))
            {
               DWORD dwExitCode;
               while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
               {
                  if(dwExitCode != STILL_ACTIVE)
                  {
                     break;
                  }
                  Sleep(200);
               }
               ::MoveFile(strTar + ".bz2", strTopic + ".tar.bz2");
            }
         }
         
         
       }
       else
       {
          MessageBox(lpcmi->hwnd,
             "In this version, operation available only for single file or directory",
             "File Name",
             MB_OK|MB_ICONINFORMATION);
          
       }
    }
    else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY + 1)
    {
       if(pThis->m_straFiles.GetSize() >= 1)
       {
          CString strTopic;
          strTopic = pThis->m_straFiles[0];
          
          CString strDirectory;
          
          int iFind;
          int iFind1 = strTopic.ReverseFind('\\');
          int iFind2 = strTopic.ReverseFind('/');
          
          iFind = max(iFind1, iFind2);
          
          if(iFind > 0)
          {
             strDirectory = strTopic.Left(iFind);
          }
          
          int i = 0;
          CString strListFile;
          while(true)
          {
             if(i == 0)
             {
                strListFile = strDirectory + "\\OSShellUtilFileList.txt";
             }
             else
             {
                strListFile.Format(strDirectory + "\\OSShellUtilFileList%d.txt", i);
             }
             if(::GetFileAttributes(strListFile) == -1)
             {
                break;
             }
             else
             {
                i++;
                if(i > 1000)
                   return E_FAIL;
             }
          }
          CStdioFile file;
          
          if(!file.Open(strListFile, CFile::modeWrite | CFile::typeText | CFile::modeCreate))
          {
             return E_FAIL;
          }

          int iCount = pThis->m_straFiles.GetSize();

          CString str;
          for(i = 0; i < iCount; i++)
          {
             str = pThis->m_straFiles[i];
            int iFind;
            int iFind1 = str.ReverseFind('\\');
            int iFind2 = str.ReverseFind('/');
          
            iFind = max(iFind1, iFind2);

            if(iFind >= 0)
            {
               str = str.Mid(iFind + 1);
               if(str.Left(11) != "OSShellUtil")
               {
                  file.WriteString(str);

                  file.WriteString("\n");
               }
            }
          }

          file.Close();


       }
    }
    else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY + 2)
    {
       if(pThis->m_straFiles.GetSize() >= 1)
       {
          CString strTopic;
          strTopic = pThis->m_straFiles[0];
          
          CString strDirectory;
          
          int iFind;
          int iFind1 = strTopic.ReverseFind('\\');
          int iFind2 = strTopic.ReverseFind('/');
          
          iFind = max(iFind1, iFind2);
          
          if(iFind > 0)
          {
             strDirectory = strTopic.Left(iFind);
          }
          
          int i = 0;
          CString strListFile;
          while(true)
          {
             if(i == 0)
             {
                strListFile = strDirectory + "\\OSShellUtilFileList.txt";
             }
             else
             {
                strListFile.Format(strDirectory + "\\OSShellUtilFileList%d.txt", i);
             }
             if(::GetFileAttributes(strListFile) == -1)
             {
                break;
             }
             else
             {
                i++;
                if(i > 1000)
                   return E_FAIL;
             }
          }

          CString strCopy;

          int iCount = pThis->m_straFiles.GetSize();

          CString str;
          for(i = 0; i < iCount; i++)
          {
             str = pThis->m_straFiles[i];
            int iFind;
            int iFind1 = str.ReverseFind('\\');
            int iFind2 = str.ReverseFind('/');
          
            iFind = max(iFind1, iFind2);

            if(iFind >= 0)
            {
               str = str.Mid(iFind + 1);
               if(str.Left(11) != "OSShellUtil")
               {
                  strCopy += str;

                  strCopy += "\n";
               }
            }
          }
          if(pThis->m_window.OpenClipboard())
          {
             if(::EmptyClipboard())
             {
                HLOCAL hlocal = ::LocalAlloc(LPTR, strCopy.GetLength() + sizeof(TCHAR));
                LPTSTR lpsz = (LPTSTR) ::LocalLock(hlocal);
                _tcscpy(lpsz, (LPCTSTR) strCopy);
                ::LocalUnlock(hlocal);
                ::SetClipboardData(CF_TEXT, hlocal);
                ::CloseClipboard();
             }
          }


       }
    }
    else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY + 3)
    {
       if(pThis->m_straFiles.GetSize() == 1)
       {
          CString str = pThis->m_straFiles[0];
          SplitFileDialog dlg(str);
          dlg.DoModal();
       }
    }
   else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY + 4)
   {
      CString strTopic;
      strTopic = pThis->m_straFiles[0];
      
      CString strDirectory;
      
      int iFind;
      int iFind1 = strTopic.ReverseFind('\\');
      int iFind2 = strTopic.ReverseFind('/');
      
      iFind = max(iFind1, iFind2);
      
      if(iFind > 0)
      {
         strDirectory = strTopic.Left(iFind);
      }
      
      
      LPCTSTR lpcszFolder = NULL;
      if(!strDirectory.IsEmpty())
         lpcszFolder = strDirectory;
      
      CString strTitle;
      strTitle = strTopic.Mid(iFind + 1);
      
      // Calculate temp dir
      /*CString strTempPath;
      ::GetTempPath(1024, strTempPath.GetBuffer(2048));
      strTempPath.ReleaseBuffer();
      if(strTempPath[strTempPath.GetLength() - 1] != '\\')
      {
         strTempPath += "\\";
      }
      strTempPath += "OSZipShell\\";
      
      DWORD dw = ::GetFileAttributes(strTempPath);
      if((dw & FILE_ATTRIBUTE_DIRECTORY) == 0 || dw == -1)
      {
         if(dw != -1)
         {
            ::DeleteFile(strTempPath);
         }
         ::CreateDirectory(strTempPath, NULL);
         
      }
      
      // Calculate tar file
      CString strTar;
      
      strTar = strTempPath + strTitle + ".tar";
      //          ::GetTempFileName(strTempPath, "tar", 0, strTar.GetBuffer(4096));
      //        strTar.ReleaseBuffer();*/
      
      CString strFileName;
      ::GetModuleFileName(AfxGetApp()->m_hInstance, strFileName.GetBufferSetLength(MAX_PATH * 4), MAX_PATH * 4);
      strFileName.ReleaseBuffer();

      CString strPath;
      LPTSTR lpszFilePath = strPath.GetBufferSetLength(MAX_PATH * 4);
      LPTSTR lpszFilePart;
      ::GetFullPathName(strFileName, MAX_PATH * 4, lpszFilePath, &lpszFilePart);
      lpszFilePart[0] = '\0';
      strPath.ReleaseBuffer();

      CString strDir(strPath);

      CString strZipFile;
      strZipFile = GetZipPath(pThis->m_straFiles);
      
      CString strFileList;
      CString strFile;
      for(int j = 0; j < pThis->m_straFiles.GetSize(); j++)
      {
         strFile.Format("\"%s\"", pThis->m_straFiles[j]);
         strFileList += " " + strFile;

      }
      
      CString strParams;
      strParams.Format("%sbin\\compress\\zip -r \"%s\"%s", strDir, strZipFile, strFileList);
      
      PROCESS_INFORMATION pi;
      STARTUPINFO si;
      memset(&si, 0, sizeof(si));
      si.cb = sizeof(si);
      if(CreateProcess(
         NULL,
         (LPTSTR) (LPCTSTR) strParams,
         NULL,
         NULL,
         FALSE,
         NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
         NULL,
         strDirectory,
         &si,
         &pi))
      {
         
         DWORD dwExitCode;
         while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
         {
            if(dwExitCode != STILL_ACTIVE)
            {
               break;
            }
            Sleep(200);
         }
      }
    }
   else if(LOWORD(lpcmi->lpVerb) == IDM_DISPLAY + UNCOMPRESS)
   {
      CString strTopic;
      strTopic = pThis->m_straFiles[0];
      
      CString strDirectory;
      
      int iFind;
      int iFind1 = strTopic.ReverseFind('\\');
      int iFind2 = strTopic.ReverseFind('/');
      
      iFind = max(iFind1, iFind2);
      
      if(iFind > 0)
      {
         strDirectory = strTopic.Left(iFind);
      }
      
      
      LPCTSTR lpcszFolder = NULL;
      if(!strDirectory.IsEmpty())
         lpcszFolder = strDirectory;
      
      CString strTitle;
      strTitle = strTopic.Mid(iFind + 1);
      
      // Calculate temp dir
      /*CString strTempPath;
      ::GetTempPath(1024, strTempPath.GetBuffer(2048));
      strTempPath.ReleaseBuffer();
      if(strTempPath[strTempPath.GetLength() - 1] != '\\')
      {
         strTempPath += "\\";
      }
      strTempPath += "OSZipShell\\";
      
      DWORD dw = ::GetFileAttributes(strTempPath);
      if((dw & FILE_ATTRIBUTE_DIRECTORY) == 0 || dw == -1)
      {
         if(dw != -1)
         {
            ::DeleteFile(strTempPath);
         }
         ::CreateDirectory(strTempPath, NULL);
         
      }
      
      // Calculate tar file
      CString strTar;
      
      strTar = strTempPath + strTitle + ".tar";
      //          ::GetTempFileName(strTempPath, "tar", 0, strTar.GetBuffer(4096));
      //        strTar.ReleaseBuffer();*/
      
      CString strFileName;
      ::GetModuleFileName(AfxGetApp()->m_hInstance, strFileName.GetBufferSetLength(MAX_PATH * 4), MAX_PATH * 4);
      strFileName.ReleaseBuffer();

      CString strPath;
      LPTSTR lpszFilePath = strPath.GetBufferSetLength(MAX_PATH * 4);
      LPTSTR lpszFilePart;
      ::GetFullPathName(strFileName, MAX_PATH * 4, lpszFilePath, &lpszFilePart);
      lpszFilePart[0] = '\0';
      strPath.ReleaseBuffer();

      CString strDir(strPath);

      CString strZipFile;
      strZipFile = GetZipPath(pThis->m_straFiles);
      
      CString strFileList;
      CString strFile;
      for(int j = 0; j < pThis->m_straFiles.GetSize(); j++)
      {
	      strFile = pThis->m_straFiles[j];
		  while(true)
		  {
		  if(strFile.Right(4).CompareNoCase(".rar") == 0)
		  {
			  PROCESS_INFORMATION pi;
			  STARTUPINFO si;
			  memset(&si, 0, sizeof(si));
			  si.cb = sizeof(si);

			  CString strParams;
			  strParams.Format("%sbin\\compress\\unrar.exe \"%s\"", strDir, strFile);

			  TRACE(strParams);

			  if(CreateProcess(
				 NULL,
				 (LPTSTR) (LPCTSTR) strParams,
				 NULL,
				 NULL,
				 FALSE,
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
				 NULL,
				 strDirectory,
				 &si,
				 &pi))
			  {
		         
				 DWORD dwExitCode;
				 while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
				 {
					if(dwExitCode != STILL_ACTIVE)
					{
					   break;
					}
					Sleep(200);
				 }
			  }
				strFile = strFile.Left(strFile.GetLength() - 4);
			}

		  else if(strFile.Right(4).CompareNoCase(".zip") == 0)
		  {
			  PROCESS_INFORMATION pi;
			  STARTUPINFO si;
			  memset(&si, 0, sizeof(si));
			  si.cb = sizeof(si);

			  CString strParams;
			  strParams.Format("%sbin\\compress\\unzip.exe \"%s\"", strDir, strFile);

			  TRACE(strParams);

			  if(CreateProcess(
				 NULL,
				 (LPTSTR) (LPCTSTR) strParams,
				 NULL,
				 NULL,
				 FALSE,
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
				 NULL,
				 strDirectory,
				 &si,
				 &pi))
			  {
		         
				 DWORD dwExitCode;
				 while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
				 {
					if(dwExitCode != STILL_ACTIVE)
					{
					   break;
					}
					Sleep(200);
				 }
			  }
				strFile = strFile.Left(strFile.GetLength() - 4);
			}

		  else if(strFile.Right(4).CompareNoCase(".bz2") == 0)
		  {
			  PROCESS_INFORMATION pi;
			  STARTUPINFO si;
			  memset(&si, 0, sizeof(si));
			  si.cb = sizeof(si);

			  CString strParams;
			  strParams.Format("%sbin\\compress\\bunzip2.exe \"%s\"", strDir, strFile);

			  TRACE(strParams);

			  if(CreateProcess(
				 NULL,
				 (LPTSTR) (LPCTSTR) strParams,
				 NULL,
				 NULL,
				 FALSE,
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
				 NULL,
				 strDirectory,
				 &si,
				 &pi))
			  {
		         
				 DWORD dwExitCode;
				 while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
				 {
					if(dwExitCode != STILL_ACTIVE)
					{
					   break;
					}
					Sleep(200);
				 }
			  }
				strFile = strFile.Left(strFile.GetLength() - 4);
			}
		  else if(strFile.Right(3).CompareNoCase(".gz") == 0)
		  {
			  PROCESS_INFORMATION pi;
			  STARTUPINFO si;
			  memset(&si, 0, sizeof(si));
			  si.cb = sizeof(si);

			  CString strParams;
			  strParams.Format("%sbin\\compress\\gzip.exe -d \"%s\"", strDir, strFile);

			  TRACE(strParams);

			  if(CreateProcess(
				 NULL,
				 (LPTSTR) (LPCTSTR) strParams,
				 NULL,
				 NULL,
				 FALSE,
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
				 NULL,
				 strDirectory,
				 &si,
				 &pi))
			  {
		         
				 DWORD dwExitCode;
				 while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
				 {
					if(dwExitCode != STILL_ACTIVE)
					{
					   break;
					}
					Sleep(200);
				 }
			  }
				strFile = strFile.Left(strFile.GetLength() - 3);
			}
		  else if(strFile.Right(4).CompareNoCase(".tar") == 0)
		  {
			  PROCESS_INFORMATION pi;
			  STARTUPINFO si;
			  memset(&si, 0, sizeof(si));
			  si.cb = sizeof(si);

			  CString strFileDir;
			  LPTSTR lpszFilePath = strFileDir.GetBufferSetLength(MAX_PATH * 4);
			  LPTSTR lpszFilePart;
			  ::GetFullPathName(strFile, MAX_PATH * 4, lpszFilePath, &lpszFilePart);
			  CString strFileTitle;
			  strFileTitle = lpszFilePart;
			  lpszFilePart[0] = '\0';
			  strFileDir.ReleaseBuffer();


			  CString strParams;
			  strParams.Format("%sbin\\compress\\tar.exe -xvf \"%s\"", strDir, strFileTitle);

			  TRACE(strParams);

			  if(CreateProcess(
				 NULL,
				 (LPTSTR) (LPCTSTR) strParams,
				 NULL,
				 NULL,
				 FALSE,
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
				 NULL,
				 strFileDir,
				 &si,
				 &pi))
			  {
		         
				 DWORD dwExitCode;
				 while(GetExitCodeProcess(pi.hProcess, &dwExitCode))
				 {
					if(dwExitCode != STILL_ACTIVE)
					{
					   break;
					}
					Sleep(200);
				 }
			  }
			  break;
			}
		  else
		  {
			  break;
		  }
	  }
		}

      }
      
    
    return S_OK;
} 
    
    
    
    CString OSZipContextMenuHandler::GetMenuCommand(int iCommand)
    {

       if(iCommand == 0)
       {
          if(m_straFiles.GetSize() == 0)
          {
             return "";
          }
          else if(m_straFiles.GetSize() == 1)
          {
             //DWORD dw = ::GetFileAttributes(m_straFiles[0]);
             CString str;
             str.Format("tar and bzip2 %s", m_straFiles[0]);
             return str;
          }
          else
          {
             return "";
          }
       }
       else if(iCommand == 1)
       {
          if(m_straFiles.GetSize() == 0)
          {
             return "";
          }
          else if(m_straFiles.GetSize() >= 1)
          {
             //DWORD dw = ::GetFileAttributes(m_straFiles[0]);
             CString str;
             str = "list file names in OSShellUtilFileList.txt";
             return str;
          }
       }
       else if(iCommand == 2)
       {
          if(m_straFiles.GetSize() == 0)
          {
             return "";
          }
          else if(m_straFiles.GetSize() >= 1)
          {
             //DWORD dw = ::GetFileAttributes(m_straFiles[0]);
             CString str;
             str = "copy file names";
             return str;
          }
       }
       else if(iCommand == 3)
       {
          if(m_straFiles.GetSize() == 1)
          {
             return "split file";
          }
          else
          {
             return "";
          }
       }
       else if(iCommand == 4)
       {
          if(m_straFiles.GetSize() == 0)
          {
             return "";
          }
          else if(m_straFiles.GetSize() == 1)
          {
             CString strZipName = GetZipTitle(m_straFiles);
             CString str;
             str.Format("zip %s in %s", m_straFiles[0], str);
             return str;
          }
          else if(m_straFiles.GetSize() > 1)
          {
             CString strZipName = GetZipTitle(m_straFiles);
             CString str;
             str.Format("zip files in %s", m_straFiles[0], str);
             return str;
          }
          else
          {
             return "";
          }
       }
       else if(iCommand == UNCOMPRESS)
       {
          if(m_straFiles.GetSize() == 0)
          {
             return "";
          }
          else if(m_straFiles.GetSize() == 1)
          {
             CString str;
             str.Format("uncompress %s", m_straFiles[0]);
             return str;
          }
          else if(m_straFiles.GetSize() > 1)
          {
             CString str;
             str.Format("uncompress files");
             return str;
          }
          else
          {
             return "";
          }
       }
       
       
       
    }
    int OSZipContextMenuHandler::GetMenuCommandCount()
    {
       return 6;
    }
