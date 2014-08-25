#include "framework.h"


#if defined(LINUX) || defined(ANDROID)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ansios
{


   pipe::pipe(bool bInherit)
   {

      m_pchBuf = NULL;


      m_fd[0] = -1;
      m_fd[1] = -1;



   }


   pipe::~pipe()
   {

      if(m_pchBuf != NULL)
      {
         free(m_pchBuf);
      }

      if(m_fd[0] != -1)
      {
         ::close(m_fd[0]);
      }

      if(m_fd[1] != -1)
      {
         ::close(m_fd[1]);
      }

   }


   bool pipe::create(bool bBlock)
   {


      int32_t iFlags = bBlock ? 0 : O_NONBLOCK;

      if(::pipe(m_fd))
      {
         // errno
         return false;
      }

      if(fcntl(m_fd[0],F_SETFL,iFlags))
      {
         close(m_fd[0]);
         close(m_fd[1]);
         return false;
      }

      if(fcntl(m_fd[1],F_SETFL,iFlags))
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

      if(!SetHandleInformation(m_hRead,HANDLE_FLAG_INHERIT,0))
         return false;

#endif

      return true;

   }

   bool pipe::not_inherit_write()
   {

#ifdef WINDOWS

      if(!SetHandleInformation(m_hWrite,HANDLE_FLAG_INHERIT,0))
         return false;

#endif

      return true;

   }


   bool pipe::write(const char * psz)
   {
      uint32_t dwLen = (uint32_t)strlen(psz);
      bool bSuccess = FALSE;
#ifdef WINDOWS
      DWORD dwWritten;
      bSuccess = WriteFile(m_hWrite,(const char *)psz,dwLen,&dwWritten,NULL) != FALSE;
#else
      size_t dwWritten;
      dwWritten = ::write(m_fd[1],(const char *)psz,dwLen);
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
      for(;;)
      {
         memset(chBuf,0,BUFSIZE);

         try
         {
#ifdef WINDOWS
            bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,NULL) != FALSE;
#else
            dwRead =::read(m_fd[0],chBuf,BUFSIZE);
            bSuccess = TRUE;
#endif
         }
         catch(...)
         {
            bSuccess = FALSE;
         }
         if(!bSuccess || dwRead == 0)
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
      const int32_t BUFSIZE = 1024 * 8;
#ifdef WINDOWS
      DWORD dwRead;
#else
      size_t dwRead;
#endif
      bool bSuccess = FALSE;
      char chBuf[BUFSIZE];
      memset(chBuf,0,BUFSIZE);

      try
      {

#ifdef WINDOWS

         bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,NULL) != FALSE;

#else

         dwRead = ::read(m_fd[0],chBuf,BUFSIZE);

         bSuccess = true;

#endif

      }
      catch(...)
      {
         bSuccess = FALSE;
      }

      if(!bSuccess || dwRead == 0)
         return str;

      str += chBuf;
      return str;
   }

#ifdef WINDOWS

   void pipe::readex()
   {
      if(m_pchBuf == NULL)
      {
         m_pchBuf = (char *)malloc(1025);
         if(m_pchBuf == NULL)
            throw memory_exception(get_thread_app());
      }
      memset(&m_overlapped,0,sizeof(m_overlapped));
      m_overlapped.m_ppipe = this;
      ReadFileEx(m_hRead,m_pchBuf,1024,&m_overlapped.m_overlapped,(LPOVERLAPPED_COMPLETION_ROUTINE)&pipe::read_complete);
   }

   void WINAPI pipe::read_complete(
      uint32_t dwErrorCode,
      uint32_t dwNumberOfBytesTransfered,
      LPOVERLAPPED lpOverlapped
      )
   {
      UNREFERENCED_PARAMETER(dwErrorCode);
      overlapped * plap = NULL;
      plap = plap->from(lpOverlapped);
      int32_t iLimit = MIN(dwNumberOfBytesTransfered,1024);
      plap->m_ppipe->m_pchBuf[iLimit] = '\0';
      plap->m_ppipe->m_strRead += plap->m_ppipe->m_pchBuf;
   }


#endif


   cross_pipe::cross_pipe(bool bInherit):
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
   }

} // namespace core


#endi





