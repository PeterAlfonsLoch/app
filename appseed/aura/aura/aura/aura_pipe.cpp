#include "framework.h"


namespace aura
{


   pipe::pipe(bool bInherit)
   {

      m_bInherit = false;

      m_pchBuf = NULL;



   }

   pipe::~pipe()
   {

      if(m_pchBuf != NULL)
      {
         free(m_pchBuf);
      }

   }


   bool pipe::create(bool bBlock, bool bInherit)
   {

      m_bBlock = bBlock;

      m_bInherit = bInherit;

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

      return true;

   }


   string pipe::read()
   {

      return "";

   }


   string pipe::one_pass_read()
   {

      return "";

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
      int32_t iLimit = min(dwNumberOfBytesTransfered,1024);
      plap->m_ppipe->m_pchBuf[iLimit] = '\0';
      plap->m_ppipe->m_strRead += plap->m_ppipe->m_pchBuf;
   }


#endif


   cross_pipe::cross_pipe(bool bInherit):
   {


   }


   cross_pipe::cross_pipe(sp(::aura::application) papp) :
      element(papp)
      m_sppipeIn(bInherit),
      m_sppipeOut(bInherit)
   {

   }


   bool cross_pipe::create(bool bBlock, bool bInherit)
   {

      if(!m_sppipeIn->create(bBlock, bInherit))
         return false;

      if(!m_sppipeIn->not_inherit_write())
         return false;

      if(!m_sppipeOut->create(bBlock,bInherit))
         return false;

      if(!m_sppipeOut->not_inherit_read())
         return false;

      return true;

   }


} // namespace core





































