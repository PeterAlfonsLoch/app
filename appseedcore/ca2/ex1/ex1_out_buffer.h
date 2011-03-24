// OutBuffer.h
// from 7-zip on 2012-12-23, dawn
#pragma once


/*#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"*/

namespace ex1
{

   class CLASS_DECL_ca out_buffer_exception: 
      virtual public system_exception
   {
   public:
      out_buffer_exception(::ca::application * papp, HRESULT errorCode) : 
         ca(papp),
         system_exception(papp, errorCode)
      {
      }
   };

   class CLASS_DECL_ca out_buffer :
      virtual public ::radix::object
   {
   protected:
      byte *_buffer;
      uint32 _pos;
      uint32 _limitPos;
      uint32 _streamPos;
      uint32 _bufferSize;
      writer * _stream;
      uint64 _processedSize;
      byte  *_buffer2;
      bool _overDict;

      HRESULT FlushPart();
   public:
      HRESULT ErrorCode;

      out_buffer(): _buffer(0), _pos(0), _stream(0), _buffer2(0) {}
      ~out_buffer() { Free(); }

      bool Create(uint32 bufferSize);
      void Free();

      void SetMemStream(byte *buffer) { _buffer2 = buffer; }
      void SetStream(writer *stream);
      void Init();
      HRESULT Flush();
      void FlushWithCheck();
      void ReleaseStream()
      { 
         // _stream.Release(); 
      }

      void WriteByte(byte b)
      {
         _buffer[_pos++] = b;
         if(_pos == _limitPos)
            FlushWithCheck();
      }
      void WriteBytes(const void *data, size_t size)
      {
         for (size_t i = 0; i < size; i++)
            WriteByte(((const byte *)data)[i]);
      }

      uint64 GetProcessedSize() const;
   };

} // namespace ex1