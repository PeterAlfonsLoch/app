#include "framework.h"


#ifndef METROWIN

#if defined(LINUX) || defined(ANDROID)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace core
{


   pipe::pipe(bool bInherit)
   {

      m_pchBuf = NULL;

#ifdef WINDOWS

      m_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_sa.bInheritHandle = bInherit ? TRUE : FALSE;
      m_sa.lpSecurityDescriptor = NULL;
      m_hRead = NULL;
      m_hWrite = NULL;

#else

      m_fd[0] = -1;
      m_fd[1] = -1;

#endif


   }

   pipe::~pipe()
   {

      if(m_pchBuf != NULL)
      {
         free(m_pchBuf);
      }

#ifdef WINDOWS

      ::CloseHandle(m_hRead);
      ::CloseHandle(m_hWrite);

#else

      if(m_fd[0] != -1)
      {
         ::close(m_fd[0]);
      }

      if(m_fd[1] != -1)
      {
         ::close(m_fd[1]);
      }

#endif

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

      int32_t iFlags = bBlock ? 0 : O_NONBLOCK;

      if(::pipe(m_fd))
      {
         // errno
         return false;
      }

      if(fcntl(m_fd[0], F_SETFL, iFlags))
      {
         close(m_fd[0]);
         close(m_fd[1]);
         return false;
      }

      if(fcntl(m_fd[1], F_SETFL, iFlags))
      {
         close(m_fd[0]);
         close(m_fd[1]);
         return false;
      }


#endif

      return true;

   }

   bool pipe::not_inherit_read()
   {

#ifdef WINDOWS

      if(!SetHandleInformation(m_hRead, HANDLE_FLAG_INHERIT, 0))
         return false;

#endif

      return true;

   }

   bool pipe::not_inherit_write()
   {

#ifdef WINDOWS

      if(!SetHandleInformation(m_hWrite, HANDLE_FLAG_INHERIT, 0))
         return false;

#endif

      return true;

   }


   bool pipe::write(const char * psz)
   {
      uint32_t dwLen = (uint32_t) strlen(psz);
      bool bSuccess = FALSE;
#ifdef WINDOWS
      DWORD dwWritten;
      bSuccess = WriteFile(m_hWrite, (const char *) psz, dwLen, &dwWritten, NULL) != FALSE;
#else
      size_t dwWritten;
      dwWritten = ::write(m_fd[1], (const char *) psz, dwLen);
#endif
      return bSuccess != FALSE && dwWritten == dwLen;
   }

   string pipe::read()
   {
      string str;
      const int32_t BUFSIZE = 1024 * 8;
#ifdef WINDOWS
      DWORD dwRead;
#else
      size_t dwRead;
#endif
      bool bSuccess;
      char chBuf[BUFSIZE];
      for (;;)
      {
         memset(chBuf, 0, BUFSIZE);

         try
         {
#ifdef WINDOWS
            bSuccess = ReadFile( m_hRead, chBuf, BUFSIZE, &dwRead, NULL) != FALSE;
#else
            dwRead =::read(m_fd[0], chBuf, BUFSIZE);
            bSuccess = TRUE;
#endif
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
