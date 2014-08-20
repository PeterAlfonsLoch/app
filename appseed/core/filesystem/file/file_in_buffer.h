// InBuffer.h
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"*/


namespace file
{


   class CLASS_DECL_CORE in_buffer_exception :
      virtual public system_exception
   {
   public:
      in_buffer_exception(sp(::axis::application) papp, HRESULT errorCode) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::simple_exception(papp),
         system_exception(papp, errorCode)
      {
      }
   };

   class CLASS_DECL_CORE in_buffer :
      virtual public ::object
   {
     byte *_buffer;
     byte *_bufferLimit;
     byte *_bufferBase;
     reader * _stream;
     uint64_t _processedSize;
     uint32_t _bufferSize;
     bool _wasFinished;

     bool ReadBlock();
     byte ReadBlock2();

   public:
     HRESULT ErrorCode;

     in_buffer();
     ~in_buffer() { Free(); }

     bool Create(uint32_t bufferSize);
     void Free();

     void SetStream(reader *stream);
     void Init();
     void ReleaseStream()
     {
     //   _stream.Release();
     }

     bool ReadByte(byte &b)
     {
       if (_buffer >= _bufferLimit)
         if (!ReadBlock())
           return false;
       b = *_buffer++;
       return true;
     }
     byte ReadByte()
     {
       if (_buffer >= _bufferLimit)
         return ReadBlock2();
       return *_buffer++;
     }
     uint32_t ReadBytes(byte *buf, uint32_t size)
     {
       if ((uint32_t)(_bufferLimit - _buffer) >= size)
       {
         for (uint32_t i = 0; i < size; i++)
           buf[i] = _buffer[i];
         _buffer += size;
         return size;
       }
       for (uint32_t i = 0; i < size; i++)
       {
         if (_buffer >= _bufferLimit)
           if (!ReadBlock())
             return i;
         buf[i] = *_buffer++;
       }
       return size;
     }
     uint64_t GetProcessedSize() const { return _processedSize + (_buffer - _bufferBase); }
     bool WasFinished() const { return _wasFinished; }
   };


} // namespace file




