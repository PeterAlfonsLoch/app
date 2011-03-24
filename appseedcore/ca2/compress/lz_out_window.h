// LzOutWindow.h
// from 7-zip on 2012-12-23, dawn
#pragma once
/*#define __LZ_OUT_WINDOW_H

#include "../IStream.h"

#include "../Common/OutBuffer.h"*/


namespace compress
{

   typedef ex1::out_buffer_exception lz_out_window_exception;

   class lz_out_window :
      public ::ex1::out_buffer
   {
   public:
      void Init(bool solid = false);

      // distance >= 0, len > 0,
      bool CopyBlock(uint32 distance, uint32 len)
      {
         uint32 pos = _pos - distance - 1;
         if (distance >= _pos)
         {
            if (!_overDict || distance >= _bufferSize)
               return false;
            pos += _bufferSize;
         }
         if (_limitPos - _pos > len && _bufferSize - pos > len)
         {
            const byte *src = _buffer + pos;
            byte *dest = _buffer + _pos;
            _pos += len;
            do
            *dest++ = *src++;
            while(--len != 0);
         }
         else do
         {
            if (pos == _bufferSize)
               pos = 0;
            _buffer[_pos++] = _buffer[pos++];
            if (_pos == _limitPos)
               FlushWithCheck();
         }
         while(--len != 0);
         return true;
      }

      void PutByte(byte b)
      {
         _buffer[_pos++] = b;
         if (_pos == _limitPos)
            FlushWithCheck();
      }

      byte GetByte(uint32 distance) const
      {
         uint32 pos = _pos - distance - 1;
         if (pos >= _bufferSize)
            pos += _bufferSize;
         return _buffer[pos];
      }
   };

} // namespace compress