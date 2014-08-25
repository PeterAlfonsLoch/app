#include "framework.h"


namespace windows
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

      if(!CreatePipe(&m_hRead,&m_hWrite,&m_sa,0))
         return false;

      if(!bBlock)
      {

         DWORD dwMode = PIPE_NOWAIT;
         VERIFY(SetNamedPipeHandleState(m_hRead,&dwMode,NULL,NULL));
         VERIFY(SetNamedPipeHandleState(m_hWrite,&dwMode,NULL,NULL));

      }

      return true;

   }


   bool pipe::not_inherit_read()
   {

      if(!SetHandleInformation(m_hRead,HANDLE_FLAG_INHERIT,0))
         return false;

      return true;

   }


   bool pipe::not_inherit_write()
   {

      if(!SetHandleInformation(m_hWrite,HANDLE_FLAG_INHERIT,0))
         return false;

      return true;

   }


   bool pipe::write(const char * psz)
   {

      uint32_t dwLen = (uint32_t)strlen(psz);

      bool bSuccess = false;

      DWORD dwWritten;

      bSuccess = WriteFile(m_hWrite,(const char *)psz,dwLen,&dwWritten,NULL) != FALSE;

      return bSuccess != FALSE && dwWritten == dwLen;

   }


   string pipe::read()
   {

      string str;

      const int32_t BUFSIZE = 1024 * 8;

      DWORD dwRead;

      bool bSuccess = false; 

      char chBuf[BUFSIZE];

      for(;;)
      {

         memset(chBuf,0,BUFSIZE);

         try
         {

            bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,NULL) != FALSE;

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

      DWORD dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      memset(chBuf,0,BUFSIZE);

      try
      {

         bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,NULL) != FALSE;



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


} // namespace core



















