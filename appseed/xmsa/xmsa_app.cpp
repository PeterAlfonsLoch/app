#include "StdAfx.h"

#include "win\win.h"
#include "gen/CommandLineInfo.h"


#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

#define BUFSIZE 4096 


//IMPLEMENT_DYNAMIC(xmsa_app, app )

xmsa_app::xmsa_app(void)
{
}

xmsa_app::~xmsa_app(void)
{
}

bool xmsa_app::InitInstance()
{
   if(!Ex2Application::InitInstance())
      return FALSE;
   //Ex2Application.initializAppInitialize();



   SetRegistryKey("ca2core");


   return TRUE;
}

int xmsa_app::Run()
{
   CMutex mutex(FALSE, "ca2_fontopus_xmsa");
   CSingleLock sl(&mutex, TRUE);
   m_hChildStd_IN_Rd = NULL;
   m_hChildStd_IN_Wr = NULL;
   m_hChildStd_OUT_Rd = NULL;
   m_hChildStd_OUT_Wr = NULL;

#ifdef XMSA_LOG
   CStdioFile file2;
   file2.Open("C:\\SA\\xmsa_loga.txt", CFile::typeText | CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);

   file2.SeekToEnd();
   file2.WriteString(::GetCommandLine());
   file2.WriteString("\r\n");
   file2.Flush();
#endif

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



   SECURITY_ATTRIBUTES saAttr; 
 
   TRACE("\n->Start of parent execution.\n");

// Set the bInheritHandle flag so pipe handles are inherited. 
 
   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
   saAttr.bInheritHandle = TRUE; 
   saAttr.lpSecurityDescriptor = NULL; 

// Create a pipe for the child process's STDOUT. 
 
   if ( ! CreatePipe(&m_hChildStd_OUT_Rd, &m_hChildStd_OUT_Wr, &saAttr, 0) ) 
      ErrorExit(TEXT("StdoutRd CreatePipe")); 

// Ensure the read handle to the pipe for STDOUT is not inherited.

   if ( ! SetHandleInformation(m_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      ErrorExit(TEXT("Stdout SetHandleInformation")); 

// Create a pipe for the child process's STDIN. 
 
   if (! CreatePipe(&m_hChildStd_IN_Rd, &m_hChildStd_IN_Wr, &saAttr, 0)) 
      ErrorExit(TEXT("Stdin CreatePipe")); 

// Ensure the write handle to the pipe for STDIN is not inherited. 
 
   if ( ! SetHandleInformation(m_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
      ErrorExit(TEXT("Stdin SetHandleInformation")); 
 
// Create the child process. 
   
   CreateChildProcess();

// Get a handle to an input file for the parent. 
// This example assumes a plain text file and uses string output to verify data flow. 

   LPWSTR lpwstrCmdLine = ::GetCommandLineW();
   string strCmdLine;
   gen::international::UnicodeToUtf8(strCmdLine, lpwstrCmdLine);
   gen::property_set params;
   params._008Parse(strCmdLine);


   string strFile(gen::international::UnicodeToUtf8(m_argv[1]));
   if(!m_file.Open(strFile, 
      Ex1File::typeText | Ex1File::modeRead))
   {
#ifdef XMSA_LOG
	   CStdioFile file2;
	   file2.Open("C:\\SA\\xmsa_prematureexit.txt", CFile::typeText | CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);

	   file2.SeekToEnd();
	   file2.WriteString(::GetCommandLine());
	   file2.WriteString("\r\n");
	   file2.Flush();
#endif

	   m_iExit = 7;
	   return m_iExit;
   }

   string str;
   while(m_file.ReadString(str))
   {
      str += "\r\n";
      m_strRet += str;
      if(str.Left(13) == "<<MAIL-DATA>>")
      {
         break;
      }
   }



 
// Write to the pipe that is the standard input for a child process. 
// Data is written to the pipe's buffers, so it is not necessary to wait
// until the child process is running before writing data.
 
   WriteToPipe(); 

   m_file.Close();

   ReadFromPipe();

   CStdioFile file;
   file.Open(strFile, 
      Ex1File::typeText | Ex1File::modeWrite);

   
   m_strRet.Replace("\r\n", "\n");
   file.WriteString(m_strRet);

   m_iExit = 7;
   return m_iExit;
}

BOOL xmsa_app::ExitInstance()
{
   return m_iExit;
}


Ex1FactoryImpl * xmsa_app::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}


 
 
void xmsa_app::CreateChildProcess()
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
   LPWSTR lpwstr = ::GetCommandLineW();
   string strCmdLine;
   gen::international::UnicodeToUtf8(strCmdLine, lpwstr);
   gen::property_set params;
   params._008Parse(strCmdLine);

   string szCmdline = gen::international::UnicodeToUtf8(m_argv[2]);
   PROCESS_INFORMATION piProcInfo; 
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
   siStartInfo.cb = sizeof(STARTUPINFO); 
   siStartInfo.hStdError = m_hChildStd_OUT_Wr;
   siStartInfo.hStdOutput = m_hChildStd_OUT_Wr;
   siStartInfo.hStdInput = m_hChildStd_IN_Rd;
   siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
 
// Create the child process. 
    
   bSuccess = CreateProcess(NULL, 
      (LPSTR)(LPCTSTR) szCmdline,     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      0,             // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &siStartInfo,  // STARTUPINFO pointer 
      &piProcInfo);  // receives PROCESS_INFORMATION 
   
   // If an error occurs, exit the application. 
   if ( ! bSuccess ) 
      ErrorExit(TEXT("CreateProcess"));
   else 
   {
      // Close handles to the child process and its primary thread.
      // Some applications might keep these handles to monitor the status
      // of the child process, for example. 

      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
   }
}
 
void xmsa_app::WriteToPipe(void) 
// Read from a file and write its contents to the pipe for the child's STDIN.
// Stop when there is no more data. 
{ 
   DWORD dwRead, dwWritten; 
   CHAR chBuf[BUFSIZE];
   BOOL bSuccess = FALSE;
 
   string str;
   while(m_file.ReadString(str))
   { 
      str += "\r\n";
      bSuccess = WriteFile(m_hChildStd_IN_Wr, (LPCTSTR) str, str.GetLength(), &dwWritten, NULL);
      if ( ! bSuccess ) break; 
   } 
 
// Close the pipe handle so the child process stops reading. 
 
   if ( ! CloseHandle(m_hChildStd_IN_Wr) ) 
      ErrorExit(TEXT("StdInWr CloseHandle")); 
} 
 
void xmsa_app::ReadFromPipe(void) 
// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 
{ 
   DWORD dwRead, dwWritten; 
   CHAR chBuf[BUFSIZE]; 
   BOOL bSuccess = FALSE;
//   HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Close the write end of the pipe before reading from the 
// read end of the pipe, to control child process execution.
// The pipe is assumed to have enough buffer space to hold the
// data the child process has already written to it.
 
   if (!CloseHandle(m_hChildStd_OUT_Wr)) 
      ErrorExit(TEXT("StdOutWr CloseHandle")); 
#ifdef XMSA_LOG
   CStdioFile file2;
   file2.Open("C:\\SA\\xmsa_msg.txt", CFile::typeText | CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);

   file2.SeekToEnd();
#endif

   for (;;) 
   { 
      memset(chBuf, 0, BUFSIZE);
      bSuccess = ReadFile( m_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
      if( ! bSuccess || dwRead == 0 ) break; 
      m_strRet += chBuf;
#ifdef XMSA_LOG
      file2.WriteString(chBuf);
#endif
   } 
#ifdef XMSA_LOG
   file2.Flush();
#endif
} 
 
void xmsa_app::ErrorExit(PTSTR lpszFunction) 
// Format a readable error message, display a message box, 
// and exit from the application.
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
#ifdef XMSA_LOG
   CStdioFile file2;
   file2.Open("C:\\SA\\xmsa_loge.txt", CFile::typeText | CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);

   file2.SeekToEnd();
   string strError;
   strError = (LPTSTR) lpDisplayBuf;
   strError += "\r\n";
   file2.WriteString(strError);
   file2.Flush();
#endif

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}