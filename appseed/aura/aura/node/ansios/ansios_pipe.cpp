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


} // namespace core

















