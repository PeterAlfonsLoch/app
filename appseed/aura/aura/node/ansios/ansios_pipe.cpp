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

      return true;

   }


   bool pipe::not_inherit_read()
   {

      return true;

   }

   bool pipe::not_inherit_write()
   {


      return true;

   }


   bool pipe::write(const char * psz)
   {

      uint32_t dwLen = (uint32_t)strlen(psz);

      bool bSuccess = false;

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
      bool bSuccess = false;
      char chBuf[BUFSIZE];
      for(;;)
      {
         memset(chBuf,0,BUFSIZE);

         try
         {

            dwRead =::read(m_fd[0],chBuf,BUFSIZE);

            bSuccess = true;

         }
         catch(...)
         {

            bSuccess = false;

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

      size_t dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      memset(chBuf,0,BUFSIZE);

      try
      {

         dwRead = ::read(m_fd[0],chBuf,BUFSIZE);

         bSuccess = true;

      }
      catch(...)
      {

         bSuccess = false;

      }

      if(!bSuccess || dwRead == 0)
         return str;

      str += chBuf;

      return str;

   }


} // namespace core

















