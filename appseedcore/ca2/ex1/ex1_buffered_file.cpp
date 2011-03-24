#include "StdAfx.h"

namespace ex1
{

   buffered_file::buffered_file(::ca::application * papp, ex1::filesp pfile, DWORD_PTR iBufferSize) :
      ca(papp)
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

   buffered_file::~buffered_file()
   {

   }

   DWORD_PTR buffered_file::GetBufferSize()
   {
      return m_uiBufferSize;
   }

   bool buffered_file::IsValid() const
   {
      return m_pfile.is_set();
   }

   /*int buffered_file::RemoveBegin(void * lpBuf, UINT uiCount)
   {
      ASSERT(IsValid());
      if(uiCount > get_length())
         uiCount = m_storage.get_size();
      memcpy(lpBuf, ((LPBYTE)GetAllocation()), uiCount);
      if(uiCount < get_size())
      {
         memmove(
            m_storage.GetAllocation(), 
            &((LPBYTE)m_storage.GetAllocation())[uiCount],
            m_storage.get_size() - uiCount);
      }
      
      if(m_dwPosition <= uiCount)
         m_uiPosition = 0;
      else
         m_uiPosition -= uiCount;


      m_storage.allocate(m_uiPosition);

      return uiCount;
   }*/

   /*void buffered_file::load_string(string & str)
   {
   }*/

   INT_PTR buffered_file::seek(INT_PTR lOff, UINT nFrom)
   {
      int iBegBufPosition = m_uiBufLPos;
      int iEndBufPosition = m_uiBufUPos;
      int iNewPos;
      if(nFrom == ::ex1::seek_begin)
      {
         iNewPos = lOff;
      }
      else if(nFrom == ::ex1::seek_end)
      {
         iNewPos = m_pfile->get_length() + lOff;
      }
      else if(nFrom == ::ex1::seek_current)
      {
         iNewPos = m_uiPosition + lOff;
      }
      else
      {
         ASSERT(FALSE);
      }

      if(iNewPos >= iBegBufPosition
         && iNewPos <= iEndBufPosition)
      {
         m_uiPosition = iNewPos;
      }
      else
      {
         m_uiPosition = m_pfile->seek(lOff, nFrom);
         if(m_bDirty)
            Flush();
         m_uiBufLPos     = 0;
         m_uiBufUPos     = 0xffffffff;
         m_uiWriteLPos   = 0xffffffff;
         m_uiWriteUPos   = 0xffffffff;
      }
      return m_uiPosition;
   }

   DWORD_PTR buffered_file::GetPosition() const
   {
      return m_uiPosition;
   }

   DWORD_PTR buffered_file::get_length() const
   {
      return m_pfile->get_length();
   }

   /*void buffered_file::Truncate(int iPosition)
   {
      m_pfile->Truncate();
   }

   void buffered_file::clear()
   {
      m_pfile->clear();
   }*/

   DWORD_PTR buffered_file:: read(void *lpBufParam, DWORD_PTR nCount)
   {
      if(nCount == 0)
         return 0;
      DWORD_PTR uiRead = 0;
      DWORD_PTR uiReadNow = 0;
      while(uiRead < nCount)
      {
         if(m_uiPosition >= m_uiBufLPos && m_uiPosition <= m_uiBufUPos && m_uiBufUPos != 0xFFFFFFFF)
         {
            uiReadNow = min(nCount - uiRead, m_uiBufUPos - m_uiPosition + 1);
            if(nCount == 1)
            {
               ((LPBYTE)lpBufParam)[uiRead] = m_storage.GetAllocation()[m_uiPosition - m_uiBufLPos];
            }
            else
            {
               memcpy(&((LPBYTE)lpBufParam)[uiRead], &m_storage.GetAllocation()[m_uiPosition - m_uiBufLPos], uiReadNow);
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

   bool buffered_file::buffer(DWORD_PTR uiGrow)
   {
      if(m_bDirty)
      {
         Flush();
      }
      //if(uiGrow == 0 && m_uiPosition > m_pfile->get_length())
        // return false;
      m_pfile->seek(m_uiPosition, seek_begin);
      UINT uiCopy;
      if(uiGrow > 0)
         uiCopy = min(m_uiBufferSize, uiGrow);
      else
         uiCopy = m_uiBufferSize;
      UINT uiRead    = m_pfile->read(m_storage.GetAllocation(), uiCopy);
      m_uiBufLPos     = m_uiPosition;
      m_uiBufUPos     = m_uiPosition + uiRead - 1;
      m_uiWriteLPos   = 0xffffffff;
      m_uiWriteUPos   = 0xffffffff;
      return uiRead > 0;
   }


   void buffered_file::write(const void * lpBuf, DWORD_PTR nCount)
   {
      UINT uiWrite = 0;
      UINT uiWriteNow = 0;
      while(uiWrite < nCount)
      {
         if(m_uiPosition >= m_uiBufLPos && m_uiPosition <= m_uiBufUPos)
         {
            m_bDirty = true;
            uiWriteNow = min(nCount - uiWrite, m_uiBufUPos - m_uiPosition + 1);
            if(m_uiWriteLPos == 0xffffffff || m_uiWriteLPos > m_uiPosition)
               m_uiWriteLPos = m_uiPosition;
            if(m_uiWriteUPos == 0xffffffff || m_uiWriteUPos < (m_uiPosition + uiWriteNow - 1))
               m_uiWriteUPos = (m_uiPosition + uiWriteNow - 1);
            memcpy(&m_storage.GetAllocation()[m_uiPosition - m_uiBufLPos], &((LPBYTE)lpBuf)[uiWrite], uiWriteNow);
            m_uiPosition += uiWriteNow;
            uiWrite += uiWriteNow;
         }
         if(uiWrite < nCount)
         {
            if(!buffer(nCount - uiWrite))
               break;
         }
      }
   }

   void buffered_file::Flush()
   {
      if(m_bDirty)
      {
         m_pfile->seek(m_uiWriteLPos, seek_begin);
         m_pfile->write(&m_storage.GetAllocation()[m_uiWriteLPos - m_uiBufLPos], m_uiWriteUPos - m_uiWriteLPos);
         m_bDirty = false;
         m_uiWriteLPos = 0xffffffff;
         m_uiWriteUPos = 0xffffffff;
      }
   }


   void buffered_file::SetLength(DWORD_PTR dwNewLen)
   {
      m_pfile->SetLength(dwNewLen);
   }

} // namespace ex1