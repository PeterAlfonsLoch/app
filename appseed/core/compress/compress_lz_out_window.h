// LzOutWindow.h
// from 7-zip on 2012-12-23, dawn
#pragma once
/*#define __LZ_OUT_WINDOW_H

#include "../IStream.h"

#include "../Common/OutBuffer.h"*/


namespace libcompress
{

   typedef ::file::out_buffer_exception lz_out_window_exception;

   class lz_out_window :
      public ::file::out_buffer
   {
   public:
      void Init(bool solid = false);

      // distance >= 0, len > 0,
      bool CopyBlock(file_size_t distance, file_size_t len)
      {
         file_size_t pos = _pos - distance - 1;
         if (distance >= _pos)
         {
            if (!_overDict || distance >= m_memory.get_size())
               return false;
            pos += m_memory.get_size();
         }
         if (_limitPos - _pos > len && m_memory.get_size() - pos > len)
         {
            const byte *src = m_memory.get_data() + memory_position_t(pos);
            byte *dest = m_memory.get_data() + memory_position_t(_pos);
            _pos += len;
            do
            *dest++ = *src++;
            while(--len != 0);
         }
         else do
         {
            if (pos == m_memory.get_size())
               pos = 0;
            m_memory.get_data()[_pos++] = m_memory.get_data()[pos++];
            if (_pos == _limitPos)
               FlushWithCheck();
         }
         while(--len != 0);
         return true;
      }

      void PutByte(byte b)
      {
         m_memory.get_data()[_pos++] = b;
         if (_pos == _limitPos)
            FlushWithCheck();
      }

      byte GetByte(file_size_t distance) const
      {
         file_size_t pos = _pos - distance - 1;
         if (pos >= m_memory.get_size())
            pos += m_memory.get_size();
         return m_memory.get_data()[(index)pos];
      }
   };

} // namespace libcompress
