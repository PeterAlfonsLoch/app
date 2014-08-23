#include "framework.h"


namespace file
{


   buffered_buffer::buffered_buffer(sp(::aura::application) papp, ::file::binary_buffer_sp pfile, ::primitive::memory_size iBufferSize) :
      element(papp)
   {
      m_storage.allocate(iBufferSize);
      m_pfile              = pfile;
      m_uiBufferSize        = iBufferSize;
      m_uiPosition          = 0;
      m_uiBufLPos           = 0;
      m_uiBufUPos           = 0xffffffff;
      m_uiWriteLPos         = 0xffffffff;
      m_uiWriteUPos         = 0xffffffff;
      m_bDirty = false;
   }

   buffered_buffer::~buffered_buffer()
   {
      flush();
   }

   uint64_t buffered_buffer::GetBufferSize()
   {
      return m_uiBufferSize;
   }

   bool buffered_buffer::IsValid() const
   {
      return m_pfile.is_set();
   }

   /*int32_t buffered_buffer::remove_begin(void * lpBuf, UINT uiCount)
   {
      ASSERT(IsValid());
      if(uiCount > get_length())
         uiCount = m_storage.get_size();
      memcpy(lpBuf, ((LPBYTE)get_data()), uiCount);
      if(uiCount < this->get_size())
      {
         memmove(
            m_storage.get_data(),
            &((LPBYTE)m_storage.get_data())[uiCount],
            m_storage.get_size() - uiCount);
      }

      if(m_dwPosition <= uiCount)
         m_uiPosition = 0;
      else
         m_uiPosition -= uiCount;


      m_storage.allocate(m_uiPosition);

      return uiCount;
   }*/

   /*void buffered_buffer::load_string(string & str)
   {
   }*/

   file_position buffered_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      uint64_t uiBegBufPosition = m_uiBufLPos;
      uint64_t uiEndBufPosition = m_uiBufUPos;
      uint64_t uiNewPos;
      if(nFrom == ::file::seek_begin)
      {
         uiNewPos = lOff;
      }
      else if(nFrom == ::file::seek_end)
      {
         uiNewPos = m_pfile->get_length() + lOff;
      }
      else if(nFrom == ::file::seek_current)
      {
         uiNewPos = m_uiPosition + lOff;
      }
      else
      {
         throw invalid_argument_exception(get_app(), "::file::buffered_buffer::seek invalid seek option");
      }

      if(uiNewPos >= uiBegBufPosition
         && uiNewPos <= uiEndBufPosition)
      {
         m_uiPosition = uiNewPos;
      }
      else
      {
         m_uiPosition = m_pfile->seek(uiNewPos, ::file::seek_begin);
         if(m_bDirty)
            flush();
         m_uiBufLPos     = 0;
         m_uiBufUPos     = 0xffffffff;
         m_uiWriteLPos   = 0xffffffff;
         m_uiWriteUPos   = 0xffffffff;
      }
      return m_uiPosition;
   }

   file_position buffered_buffer::get_position() const
   {
      return m_uiPosition;
   }

   file_size buffered_buffer::get_length() const
   {
      return m_pfile->get_length();
   }

   /*void buffered_buffer::Truncate(int32_t iPosition)
   {
      m_pfile->Truncate();
   }

   void buffered_buffer::clear()
   {
      m_pfile->clear();
   }*/

   ::primitive::memory_size buffered_buffer:: read(void *lpBufParam, ::primitive::memory_size nCount)
   {
      if(nCount == 0)
         return 0;
      ::primitive::memory_size uiRead = 0;
      ::primitive::memory_size uiReadNow = 0;
      while(uiRead < nCount)
      {
         if(m_uiPosition >= m_uiBufLPos && m_uiPosition <= m_uiBufUPos && m_uiBufUPos != 0xFFFFFFFF)
         {
            uiReadNow = MIN(nCount - uiRead, (::primitive::memory_size) (m_uiBufUPos - m_uiPosition + 1));
            if(nCount == 1)
            {
               ((LPBYTE)lpBufParam)[uiRead] = m_storage.get_data()[m_uiPosition - m_uiBufLPos];
            }
            else
            {
               memcpy(&((LPBYTE)lpBufParam)[uiRead], &m_storage.get_data()[m_uiPosition - m_uiBufLPos], (size_t) uiReadNow);
            }
            m_uiPosition += uiReadNow;
            uiRead += uiReadNow;
         }
         if(uiRead < nCount)
         {
            if(!buffer())
               break;
         }
      }
      return uiRead;
   }

   bool buffered_buffer::buffer(::primitive::memory_size uiGrow)
   {
      if(m_bDirty)
      {
         flush();
      }
      //if(uiGrow == 0 && m_uiPosition > m_pfile->get_length())
        // return false;
      m_pfile->seek((file_offset) m_uiPosition, seek_begin);
      ::primitive::memory_size uiCopy;
      if(uiGrow > 0)
         uiCopy = MIN(m_uiBufferSize, uiGrow);
      else
         uiCopy = m_uiBufferSize;
      ::primitive::memory_size uiRead    = m_pfile->read(m_storage.get_data(), uiCopy);
      m_uiBufLPos     = m_uiPosition;
      m_uiBufUPos     = m_uiPosition + uiRead - 1;
      m_uiWriteLPos   = 0xffffffff;
      m_uiWriteUPos   = 0xffffffff;
      return uiRead > 0;
   }


   void buffered_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      ::primitive::memory_size uiWrite = 0;
      ::primitive::memory_size uiWriteNow = 0;
      while(uiWrite < nCount)
      {
         if(m_uiPosition >= m_uiBufLPos && m_uiPosition < (m_uiBufLPos + m_uiBufferSize))
         {
            m_bDirty = true;
            uiWriteNow = MIN(nCount - uiWrite, (::primitive::memory_size) ((m_uiBufLPos + m_uiBufferSize) - m_uiPosition + 1));
            if(m_uiWriteLPos == 0xffffffff || m_uiWriteLPos > m_uiPosition)
               m_uiWriteLPos = m_uiPosition;
            if(m_uiWriteUPos == 0xffffffff || m_uiWriteUPos < (m_uiPosition + uiWriteNow - 1))
               m_uiWriteUPos = (m_uiPosition + uiWriteNow - 1);
            memcpy(&m_storage.get_data()[m_uiPosition - m_uiBufLPos], &((LPBYTE)lpBuf)[uiWrite], (size_t) uiWriteNow);
            m_uiPosition += uiWriteNow;
            uiWrite += uiWriteNow;
         }
         if(uiWrite < nCount)
         {
            buffer(nCount - uiWrite);
         }
      }
   }

   void buffered_buffer::flush()
   {
      if(m_bDirty)
      {
         m_pfile->seek((file_offset) m_uiWriteLPos, seek_begin);
         m_pfile->write(&m_storage.get_data()[m_uiWriteLPos - m_uiBufLPos], (::primitive::memory_size) (m_uiWriteUPos - m_uiWriteLPos + 1));
         m_bDirty = false;
         m_uiWriteLPos = 0xffffffff;
         m_uiWriteUPos = 0xffffffff;
      }
   }


   void buffered_buffer::set_length(file_size dwNewLen)
   {
      m_pfile->set_length(dwNewLen);
   }


} // namespace file



