#include "framework.h"

#if defined(LINUX)
#define _GNU_SOURCE
#include <unistd.h>
#endif

namespace gen
{


   pipe::pipe(bool bInherit)
   {
      m_pchBuf = NULL;
      m_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_sa.bInheritHandle = bInherit ? TRUE : FALSE;
      m_sa.lpSecurityDescriptor = NULL;
      m_hRead = NULL;
      m_hWrite = NULL;
   }

   pipe::~pipe()
   {
      if(m_pchBuf != NULL)
      {
         free(m_pchBuf);
      }
      ::CloseHandle(m_hRead);
      ::CloseHandle(m_hWrite);
   }


   bool pipe::create(bool bBlock)
   {

#ifdef WINDOWS

      if(!CreatePipe(&m_hRead, &m_hWrite, &m_sa, 0))
         return false;

      if(!bBlock)
      {

         DWORD dwMode = PIPE_NOWAIT;
         VERIFY(SetNamedPipeHandleState(m_hRead   , &dwMode, NULL, NULL));
         VERIFY(SetNamedPipeHandleState(m_hWrite  , &dwMode, NULL, NULL));

      }

#else

      int iFlags = bBlock ? 0 : O_NONBLOCK;

      if(pipe2(m_fd, iFlags))
      {
         // errno
         return false;
      }

#endif

      return true;

   }

   bool pipe::not_inherit_read()
   {
      if(!SetHandleInformation(m_hRead, HANDLE_FLAG_INHERIT, 0))
         return false;
      return true;
   }

   bool pipe::not_inherit_write()
   {
      if(!SetHandleInformation(m_hWrite, HANDLE_FLAG_INHERIT, 0))
         return false;
      return true;
   }


   bool pipe::write(const char * psz)
   {
      DWORD dwWritten;
      BOOL bSuccess = FALSE;
      bSuccess = WriteFile(m_hWrite, (const char *) psz, (DWORD) strlen(psz), &dwWritten, NULL);
      return bSuccess != FALSE;
   }

   string pipe::read()
   {
      string str;
      const int BUFSIZE = 1024 * 8;
      DWORD dwRead;
      BOOL bSuccess;
      char chBuf[BUFSIZE];
      for (;;)
      {
         memset(chBuf, 0, BUFSIZE);

         try
         {
            bSuccess = ReadFile( m_hRead, chBuf, BUFSIZE, &dwRead, NULL);
         }
         catch(...)
         {
            bSuccess = FALSE;
         }
         if(!bSuccess || dwRead == 0 )
            break;
         str += chBuf;
         if(dwRead < BUFSIZE)
            break;
      }
      return str;
   }

   string pipe::one_pass_read()
   {
      string str;
      const int BUFSIZE = 1024 * 8;
      DWORD dwRead;
      BOOL bSuccess;
      char chBuf[BUFSIZE];
      memset(chBuf, 0, BUFSIZE);

      try
      {
         bSuccess = ReadFile( m_hRead, chBuf, BUFSIZE, &dwRead, NULL);
      }
      catch(...)
      {
         bSuccess = FALSE;
      }
      if(!bSuccess || dwRead == 0 )
         return str;
      str += chBuf;
      return str;
   }

   void pipe::readex()
   {
      if(m_pchBuf == NULL)
      {
         m_pchBuf = (char *) malloc(1025);
         if(m_pchBuf == NULL)
            throw memory_exception();
      }
      memset(&m_overlapped, 0, sizeof(m_overlapped));
      m_overlapped.m_ppipe = this;
      ReadFileEx(m_hRead, m_pchBuf, 1024, &m_overlapped.m_overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE) &pipe::read_complete);
   }

   void WINAPI pipe::read_complete(
         DWORD dwErrorCode,
         DWORD dwNumberOfBytesTransfered,
         LPOVERLAPPED lpOverlapped
         )
   {
      UNREFERENCED_PARAMETER(dwErrorCode);
      overlapped * plap = NULL;
      plap = plap->from(lpOverlapped);
      int iLimit = min(dwNumberOfBytesTransfered, 1024);
      plap->m_ppipe->m_pchBuf[iLimit] = '\0';
      plap->m_ppipe->m_strRead += plap->m_ppipe->m_pchBuf;
   }





   cross_pipe::cross_pipe(bool bInherit) :
      m_pipeIn(bInherit),
      m_pipeOut(bInherit)
   {
   }

   bool cross_pipe::create(bool bBlock)
   {
      if(!m_pipeIn.create(bBlock))
         return false;
      if(!m_pipeIn.not_inherit_write())
         return false;
      if(!m_pipeOut.create(bBlock))
         return false;
      if(!m_pipeOut.not_inherit_read())
         return false;
      return true;
   }

} // namespace gen
