// WinAppImpl.cpp: implementation of the WinAppImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "WinAppImpl.h"
#include "WinFileSystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "gen/CommandLineInfo.h"
#include "WinFile.h"
#include "WindowsShell.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WinAppImpl::WinAppImpl()
{
   m_pwszExeName = NULL;
   m_atomApp = NULL;
   m_atomSystemTopic = NULL;
   WindowsShell::theWindowsShell.Initialize();
   m_pszCmdLine = NULL;
   m_argv = NULL;

}

WinAppImpl::~WinAppImpl()
{
   if(m_pszCmdLine != NULL)
   {
      delete[] m_pszCmdLine;
   }
   if(m_argv != NULL)
   {
      delete[] m_argv;
   }
}

void WinAppImpl::_001ParseCommandLine(gen::CommandLineInfo& rCmdInfo)
{
   LPWSTR lpwstr = ::GetCommandLineW();
   int numargs;
   int numchars;
   wparse_cmdline(
      lpwstr, 
      NULL, 
      NULL,
      &numargs,
      &numchars);

   m_pszCmdLine = new WCHAR[numchars];
   m_argv = new WCHAR*[numargs];

   wparse_cmdline(
      lpwstr, 
      m_argv, 
      m_pszCmdLine,
      &numargs,
      &numchars);

   m_argc = numargs - 1;

   bool bTwoDots = false;
	for (int i = 1; i < m_argc; i++)
	{
		LPCWSTR pszParam = m_argv[i];
		BOOL bFlag = bTwoDots;
		BOOL bLast = ((i + 1) == m_argc);
      if(bFlag)
      {
      }
		else if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			// remove flag specifier
			bFlag = TRUE;
			++pszParam;
		}
      else if (wcscmp(pszParam, L":") == 0)
		{
         bTwoDots = true;
         continue;
		}
      string strParam;
      gen::international::UnicodeToUtf8(strParam, pszParam);
		rCmdInfo.ParseParam(strParam, bFlag, bLast);
	}

   string strCmdLine;
   gen::international::UnicodeToUtf8(strCmdLine, lpwstr);
   rCmdInfo.m_propertysetParameters._008Parse(strCmdLine);
}

bool WinAppImpl::_001ProcessShellCommand(gen::CommandLineInfo& rCmdInfo)
{
	bool bResult = true;
	switch (rCmdInfo.m_nShellCommand)
	{
   case gen::CommandLineInfo::FileNew:
      if (!AfxGetApp()->_001SendCommand("file::new"))
		   _001OnFileNew();
		if (AfxGetApp()->m_pMainWnd == NULL)
			bResult = false;
		break;

		// If we've been asked to open a file, call OpenDocumentFile()

	case gen::CommandLineInfo::FileOpen:
		if (!AfxGetApp()->OpenDocumentFile(rCmdInfo.m_strFileName))
			bResult = false;
		break;

		// If the user wanted to print, hide our main window and
		// fire a message to ourselves to start the printing

	case gen::CommandLineInfo::FilePrintTo:
	case gen::CommandLineInfo::FilePrint:
		AfxGetApp()->m_nCmdShow = SW_HIDE;
		ASSERT(AfxGetApp()->m_pCmdInfo == NULL);
		_001OpenDocumentFile(rCmdInfo.m_strFileName);
		m_pcmdinfo = &rCmdInfo;
		AfxGetApp()->m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
		m_pcmdinfo = NULL;
		bResult = false;
		break;

		// If we're doing DDE, hide ourselves

	case gen::CommandLineInfo::FileDDE:
      m_pcmdinfo = (gen::CommandLineInfo*)AfxGetApp()->m_nCmdShow;
		AfxGetApp()->m_nCmdShow = SW_HIDE;
		break;

	// If we've been asked to unregister, unregister and then terminate
	case gen::CommandLineInfo::AppUnregister:
		{
			//((CVmsGenApp *) AfxGetApp())->UnregisterShellFileTypes();
//xxx         AfxGetApp()->UnregisterShellFileTypes();
//xxx			BOOL bUnregistered = ((CVmsGenApp *) AfxGetApp())->Unregister();

			// if you specify /EMBEDDED, we won't make an success/failure box
			// this use of /EMBEDDED is not related to OLE

/*			if (!rCmdInfo.m_bRunEmbedded)
			{
				if (bUnregistered)
					Application.simple_message_box(AFX_IDP_UNREG_DONE);
				else
					Application.simple_message_box(AFX_IDP_UNREG_FAILURE);
			}
			bResult = FALSE;    // that's all we do

			// If nobody is using it already, we can use it.
			// We'll flag that we're unregistering and not save our state
			// on the way out. This new object gets deleted by the
			// cast object destructor.

			if (m_pcmdinfo == NULL)
			{
				m_pcmdinfo = new CommandLineInfo;
				m_pcmdinfo->m_nShellCommand = CommandLineInfo::AppUnregister;
			}*/
		}
		break;
	}
	return bResult;
}

void WinAppImpl::_001OnFileNew()
{
   ((Ex2Application *) m_pinterface)->_001OnFileNew();
}

void * WinAppImpl::_001OpenDocumentFile(LPCSTR lpcsz)
{
   return ((Ex2Application *) m_pinterface)->_001OpenDocumentFile(lpcsz);
}

   void WinAppImpl::_001EnableShellOpen()
   {
	   // get path of executable
	   WCHAR wszBuff[_MAX_PATH];
      VERIFY(WindowsShell::GetModuleFileName(GetHinstance(), wszBuff, _MAX_PATH));

	   LPWSTR lpwszExt = wcsrchr(wszBuff, '.');
	   ASSERT(lpwszExt != NULL);
	   ASSERT(*lpwszExt == '.');
	   *lpwszExt = 0;       // no suffix

  	   WCHAR wszExeName[_MAX_PATH];
   //xxx	WCHAR wszTitle[256];
	   // get the exe title from the full path name [no extension]
      VERIFY(vfxGetFileName(wszBuff, wszExeName, _MAX_PATH) == 0);
	   if (m_pwszExeName == NULL)
	   {
		   BOOL bEnable = AfxEnableMemoryTracking(FALSE);
		   m_pwszExeName = wcsdup(wszExeName); // save non-localized name
		   AfxEnableMemoryTracking(bEnable);
	   }

      ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

	   m_atomApp = ::GlobalAddAtomW(m_pwszExeName);
	   m_atomSystemTopic = ::GlobalAddAtomW(L"system");
   }

   BOOL WinAppImpl::_001OnDDECommand(LPCSTR lpcsz)
   {
      return FALSE;
   }

   HINSTANCE WinAppImpl::GetHinstance()
   {
      return NULL;
   }



void WinAppImpl::Ex1SetCommandLineInfo(gen::CommandLineInfo & rCmdInfo)
{
   m_cmdinfo = rCmdInfo;
   m_pcmdinfo = &m_cmdinfo;
}

void WinAppImpl::Ex1GetCommandLineInfo(gen::CommandLineInfo & rCmdInfo)
{
   rCmdInfo = m_cmdinfo;
}


string WinAppImpl::get_version()
{

	TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

   DWORD dw;
   
   DWORD dwResSize = GetFileVersionInfoSize(      
      lpszModuleFilePath,
      &dw);


   if(dwResSize > 0)
   {
      LPVOID lpdata = new BYTE[dwResSize];
      if(GetFileVersionInfo(      
         lpszModuleFilePath,
         0,
         dwResSize,
         lpdata))
      {
         UINT cbTranslate;
         struct LANGANDCODEPAGE {
            WORD wLanguage;
            WORD wCodePage;
            } *lpTranslate;

         // Read the list of languages and code pages.

         VerQueryValue(lpdata, 
              TEXT("\\VarFileInfo\\Translation"),
              (LPVOID*)&lpTranslate,
              &cbTranslate);

         string strKey;
         //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
         for(int i=0; i < 1; i++ )
         {
           LPTSTR lpsz;
           UINT uiSize;

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           


           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (LPCTSTR) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 


           string strVersion(lpsz, uiSize);

           return strVersion;
         }
      }
      delete [] (LPBYTE) lpdata;
   }


	return "";

}
