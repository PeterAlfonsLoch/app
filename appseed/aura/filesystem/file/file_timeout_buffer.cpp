#include "framework.h"


namespace file
{

   // uiExpectedSize = (uint64_t) -1 - initially unknown size
   // uiExpectedSize = (uint64_t) -2 - permanent or until end unknown size
   timeout_buffer::timeout_buffer(sp(::aura::application) papp, ::file::buffer_sp  pfile, uint64_t uiExpectedSize) :
      element(papp)
   {
      UNREFERENCED_PARAMETER(uiExpectedSize);
      m_pfile = pfile;
      //if(uiExpectedSize == (uint64_t) -1)
      {
         m_uiExpectedSize = uiExpectedSize;
      }
      //else
      {
         //  m_uiExpectedSize  = uiExpectedSize;
      }
      m_dwTimeOut = 120 * 1000;
      m_dwSleep = 584;
   }

   timeout_buffer::~timeout_buffer()
   {
   }

   bool timeout_buffer::IsValid() const
   {
      single_lock sl((const_cast < timeout_buffer * > (this))->m_spmutex, TRUE);
      return m_pfile != NULL;
   }

   file_position timeout_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      single_lock sl(m_spmutex, TRUE);
      uint64_t dwFuture;
      switch (nFrom)
      {
      case ::file::seek_begin:
         dwFuture = lOff;
         break;
      case ::file::seek_current:
      {
                                  uint64_t dwCurrent = m_pfile->get_position();
                                  dwFuture = dwCurrent + lOff;
      }
         break;
      case ::file::seek_end:
      {
                              uint64_t dwCurrent = get_length(&sl);
                              if (dwCurrent == ((uint64_t)-1))
                                 dwFuture = 0;
                              else
                              {
                                 dwFuture = dwCurrent + lOff;
                                 if (lOff < 0 && dwFuture > dwCurrent)
                                    dwFuture = 0;
                              }
      }
         break;
      default:
         return ::numeric_info < file_size >::allset();
      }
      m_dwLastCall = ::get_tick_count();
      while (true)
      {
         if (dwFuture == m_pfile->get_position())
            break;
         m_pfile->seek(dwFuture, ::file::seek_begin);
         if (dwFuture == m_pfile->get_position())
            break;
         Sleep(MAX(11, m_dwSleep));
      }
      return m_pfile->get_position();
   }

   file_position timeout_buffer::get_position() const
   {
      single_lock sl((const_cast < timeout_buffer * > (this))->m_spmutex, TRUE);
      return m_pfile->get_position();
   }

   file_size timeout_buffer::get_length() const
   {
      if (m_uiExpectedSize == (uint64_t)-2)
         return (uint64_t)-2;
      if (m_uiExpectedSize == (uint64_t)-1)
      {
         (const_cast < timeout_buffer * > (this))->m_dwLastCall = ::get_tick_count();
         while (m_uiExpectedSize == (uint64_t)-1)
         {
            if (::get_tick_count() - m_dwLastCall > m_dwTimeOut)
               break;
            Sleep(MAX(11, m_dwSleep));
         }
         TRACE("timeout_buffer::m_uiExpectedSize = %d", m_uiExpectedSize);
      }
      if (m_uiExpectedSize == (uint64_t)-1)
         return 0;
      else
         return m_uiExpectedSize;
   }


   file_size timeout_buffer::get_length(single_lock * psl) const
   {
      bool bAcquired = psl->IsLocked();
      if (bAcquired)
         psl->unlock();

      if (m_uiExpectedSize == (uint64_t)-2)
         return (uint64_t)-2;
      if (m_uiExpectedSize == (uint64_t)-1)
      {
         (const_cast < timeout_buffer * > (this))->m_dwLastCall = ::get_tick_count();
         while (m_uiExpectedSize == (uint64_t)-1)
         {
            if (::get_tick_count() - m_dwLastCall > m_dwTimeOut)
               break;
            Sleep(MAX(11, m_dwSleep));
         }
         TRACE("timeout_buffer::m_uiExpectedSize = %d", m_uiExpectedSize);
      }
      if (bAcquired)
         psl->lock();
      if (m_uiExpectedSize == (uint64_t)-1)
         return 0;
      else
         return m_uiExpectedSize;
   }

   ::primitive::memory_size timeout_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      single_lock sl(m_spmutex);
      if (m_pfile == NULL)
         return 0;
      ::primitive::memory_size uiRead = 0;
      ::primitive::memory_size uiReadNow = 0;
      m_dwLastCall = ::get_tick_count();
      while (nCount > 0)
      {
         sl.lock();
         uiReadNow = m_pfile->read(&((byte *)lpBuf)[uiRead], nCount);
         sl.unlock();
         if (uiReadNow > 0)
         {
            m_dwLastCall = ::get_tick_count();
         }
         uiRead += uiReadNow;
         nCount -= uiReadNow;
         if (nCount <= 0 || (::get_tick_count() - m_dwLastCall > m_dwTimeOut) ||
            (m_pfile->get_position() >= m_uiExpectedSize &&
            m_uiExpectedSize != ((uint64_t)-1)
            && m_uiExpectedSize != ((uint64_t)-2)))
            break;
         Sleep(MAX(11, m_dwSleep));
      }
      return uiRead;
   }

   void timeout_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      single_lock sl(m_spmutex, TRUE);
      m_pfile->write(lpBuf, nCount);
      //     m_uiExpectedSize = m_pfile->get_length();
   }

   void timeout_buffer::flush()
   {
      single_lock sl(m_spmutex, TRUE);
      m_pfile->flush();
   }

   void timeout_buffer::set_length(file_size dwNewLen)
   {
      single_lock sl(m_spmutex, TRUE);
      m_uiExpectedSize = dwNewLen;
   }


} // namespace file



