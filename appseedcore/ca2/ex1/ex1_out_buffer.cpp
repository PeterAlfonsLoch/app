// OutBuffer.cpp
// from 7-zip on 2012-12-23, dawn
#include "StdAfx.h"

/*#include "../../../C/Alloc.h"

#include "OutBuffer.h"*/

namespace ex1
{

   bool out_buffer::Create(uint32 bufferSize)
   {
      const uint32 kMinBlockSize = 1;
      if (bufferSize < kMinBlockSize)
         bufferSize = kMinBlockSize;
      if (_buffer != 0 && _bufferSize == bufferSize)
         return true;
      Free();
      _bufferSize = bufferSize;
      _buffer = (byte *)::MidAlloc(bufferSize);
      return (_buffer != 0);
   }

   void out_buffer::Free()
   {
      ::MidFree(_buffer);
      _buffer = 0;
   }

   void out_buffer::SetStream(writer *stream)
   {
      _stream = stream;
   }

   void out_buffer::Init()
   {
      _streamPos = 0;
      _limitPos = _bufferSize;
      _pos = 0;
      _processedSize = 0;
      _overDict = false;
#ifdef _NO_EXCEPTIONS
      ErrorCode = S_OK;
#endif
   }

   uint64 out_buffer::GetProcessedSize() const
   {
      uint64 res = _processedSize + _pos - _streamPos;
      if (_streamPos > _pos)
         res += _bufferSize;
      return res;
   }


   HRESULT out_buffer::FlushPart()
   {
      // _streamPos < _bufferSize
      DWORD_PTR size = (_streamPos >= _pos) ? (_bufferSize - _streamPos) : (_pos - _streamPos);
      HRESULT result = S_OK;
      if (_buffer2 != 0)
      {
         memmove(_buffer2, _buffer + _streamPos, size);
         _buffer2 += size;
      }

      if (_stream != 0)
      {
         DWORD_PTR processedSize = 0;
         _stream->write(_buffer + _streamPos, size, &processedSize);
         size = processedSize;
      }
      _streamPos += size;
      if (_streamPos == _bufferSize)
         _streamPos = 0;
      if (_pos == _bufferSize)
      {
         _overDict = true;
         _pos = 0;
      }
      _limitPos = (_streamPos > _pos) ? _streamPos : _bufferSize;
      _processedSize += size;
      return result;
   }

   HRESULT out_buffer::Flush()
   {
      while(_streamPos != _pos)
      {
         HRESULT result = FlushPart();
         if (result != S_OK)
            return result;
      }
      return S_OK;
   }

   void out_buffer::FlushWithCheck()
   {
      HRESULT result = Flush();
      if (result != S_OK)
         throw out_buffer_exception(get_app(), result);
   }


} // namespace ex1 