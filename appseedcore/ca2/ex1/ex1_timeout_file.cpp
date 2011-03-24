#include "StdAfx.h"

namespace ex1
{

   timeout_file::timeout_file(::ca::application * papp, ex1::file * pfile, DWORD_PTR uiExpectedSize) :
      ca(papp)
   {
      UNREFERENCED_PARAMETER(uiExpectedSize);
      m_pfile           = pfile;
      //if(uiExpectedSize == (DWORD_PTR) -1)
      {
         m_uiExpectedSize = 0;
      }
      //else
      {
       //  m_uiExpectedSize  = uiExpectedSize;
      }
      m_dwTimeOut       = 120 * 1000;
      m_dwSleep         = 584;
   }
   
   timeout_file::~timeout_file()
   {
   }

   bool timeout_file::IsValid() const
   {
      return m_pfile != NULL;
   }

   INT_PTR timeout_file::seek(INT_PTR lOff, UINT nFrom)
   {
      DWORD_PTR dwFuture;
      switch(nFrom)
      {
      case ::ex1::seek_begin:
         dwFuture = lOff;
         break;
      case ::ex1::seek_current:
         {
            DWORD_PTR dwCurrent = m_pfile->GetPosition();
            dwFuture = dwCurrent + lOff;
         }
         break;
      case ::ex1::seek_end:
         {
            DWORD_PTR dwCurrent = get_length();
            if(dwCurrent == ((DWORD_PTR)-1))
               dwFuture = 0;
            else
            {
               dwFuture = dwCurrent + lOff;
               if(lOff < 0 && dwFuture > dwCurrent)
                  dwFuture = 0;
            }
         }
         break;
      default:
         return INT_PTR(-1);
      }
      m_dwLastCall = ::GetTickCount();
      while(true)
      {
         if(dwFuture == m_pfile->GetPosition())
            break;
         m_pfile->seek(dwFuture, ::ex1::seek_begin);
         if(dwFuture == m_pfile->GetPosition())
            break;
         Sleep(max(11, m_dwSleep));
      }
      return m_pfile->GetPosition();
   }

   DWORD_PTR timeout_file::GetPosition() const
   {
      return m_pfile->GetPosition();
   }

   DWORD_PTR timeout_file::get_length() const
   {
      return m_uiExpectedSize;
   }

   DWORD_PTR timeout_file::read(void *lpBuf, DWORD_PTR nCount)
   {
      if(m_pfile == NULL)
         return 0;
      UINT uiRead = 0;
      UINT uiReadNow = 0;
      m_dwLastCall = ::GetTickCount();
      while(nCount > 0)
      {
         uiReadNow = m_pfile->read(&((byte *)lpBuf)[uiRead], nCount);
         if(uiReadNow > 0)
         {
            m_dwLastCall = ::GetTickCount();
         }
         uiRead += uiReadNow;
         nCount -= uiReadNow;
         if(nCount <= 0 || (::GetTickCount() - m_dwLastCall > m_dwTimeOut) || (m_pfile->GetPosition() >= m_uiExpectedSize && m_uiExpectedSize > 0 && m_uiExpectedSize != ((DWORD_PTR) -1)))
            break;
         Sleep(max(11, m_dwSleep));
      }
      return uiRead;
   }

   void timeout_file::write(const void * lpBuf, DWORD_PTR nCount)
   {
      m_pfile->write(lpBuf, nCount);
   }
   void timeout_file::Flush()
   {
      m_pfile->Flush();
   }

   void timeout_file::SetLength(DWORD_PTR dwNewLen)
   {
      m_uiExpectedSize = dwNewLen;
   }

} // namespace ex1