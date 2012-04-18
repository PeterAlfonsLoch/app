#include "StdAfx.h"

namespace gen
{

   process::process() :
      m_pipe(true)
   {
      m_bPiped = false;
      memset(&m_pi, 0, sizeof(PROCESS_INFORMATION));
      memset(&m_si, 0, sizeof(STARTUPINFO));
   }

   process::~process()
   {
      if(m_pi.hProcess != INVALID_HANDLE_VALUE && m_pi.hProcess != NULL)
      {
         CloseHandle(m_pi.hProcess);
      }
      if(m_pi.hThread != INVALID_HANDLE_VALUE && m_pi.hThread != NULL)
      {
         CloseHandle(m_pi.hThread);
      }
   }


   bool process::create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir)
   {
      string szCmdline = pszCmdLine;
 
      
      BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
      

      if(bPiped)
      {
         if(!m_pipe.create())
            return false;
         DWORD dwMode = PIPE_NOWAIT;
         VERIFY(SetNamedPipeHandleState(m_pipe.m_pipeIn.m_hRead   , &dwMode, NULL, NULL));
         VERIFY(SetNamedPipeHandleState(m_pipe.m_pipeIn.m_hWrite  , &dwMode, NULL, NULL));
         VERIFY(SetNamedPipeHandleState(m_pipe.m_pipeOut.m_hRead  , &dwMode, NULL, NULL));
         VERIFY(SetNamedPipeHandleState(m_pipe.m_pipeOut.m_hWrite , &dwMode, NULL, NULL));
      }

      m_bPiped = bPiped;
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
      
      m_si.cb = sizeof(STARTUPINFO); 
      if(bPiped)
      {
         m_si.hStdError = m_pipe.m_pipeOut.m_hWrite;
         m_si.hStdOutput = m_pipe.m_pipeOut.m_hWrite;
         m_si.hStdInput = m_pipe.m_pipeIn.m_hRead;
         m_si.dwFlags |= STARTF_USESTDHANDLES;
         
      }
        /* STARTUPINFO si;
         PROCESS_INFORMATION pi; 
         memset(&si, 0, sizeof(si));
         memset(&pi, 0, sizeof(pi));
         si.cb = sizeof(si);
         si.dwFlags = STARTF_USESHOWWINDOW;
         si.wShowWindow = SW_HIDE; */
//         if(!::CreateProcess(NULL, (LPTSTR) (const char *) System.dir().appdata("production\\build.bat"), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
      m_si.dwFlags |= STARTF_USESHOWWINDOW;
      m_si.wShowWindow = SW_HIDE;
      
 
// create the child process. 
    
      bSuccess = CreateProcess(NULL, 
         (char *)(const char *) szCmdline,     // command line 
         NULL,          // process security attributes 
         NULL,          // primary thread security attributes 
         TRUE,          // handles are inherited 
         CREATE_NEW_CONSOLE,             // creation flags 
         NULL,          // use parent's environment 
         pszDir,
         &m_si,  // STARTUPINFO pointer 
         &m_pi);  // receives PROCESS_INFORMATION 
   
      // If an error occurs, exit the application. 
      if ( ! bSuccess ) 
         return false;
      else 
      {
         // close handles to the child process and its primary thread.
         // Some applications might keep these handles to monitor the status
         // of the child process, for example. 

         //CloseHandle(m_pi.hProcess);
         //CloseHandle(m_pi.hThread);
      }
      return true;
   }
 
   bool process::write(const char * psz)
   {
      return m_pipe.m_pipeIn.write(psz);
   }
      
   string process::read(bool bUntilExit)
   {
      UNREFERENCED_PARAMETER(bUntilExit);
      return m_pipe.m_pipeOut.read();
   }

   DWORD process::wait_until_exit(int iWaitMax)
   {
      DWORD dwExitCode = 0;
      DWORD dwStartTime = ::GetTickCount();
      int i = 1;
      while(true)
      {
         if(has_exited(&dwExitCode))
            break;
         if(iWaitMax >= 0 && GetTickCount() > dwStartTime + iWaitMax)
            break;
         Sleep(100);
         i++;
      }
      return dwExitCode;
   }

   bool process::has_exited(DWORD * pdwExitCode)
   {
      DWORD dwExitCode;
      if(pdwExitCode == NULL)
         pdwExitCode = &dwExitCode;
      if(!GetExitCodeProcess(m_pi.hProcess, pdwExitCode))
         return true;
      if(*pdwExitCode == STILL_ACTIVE)
         return false;
      return true;
   }


} // namespace gen