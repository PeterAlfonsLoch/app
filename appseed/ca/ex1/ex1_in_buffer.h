// InBuffer.h
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"*/

namespace ex1
{

   class CLASS_DECL_ca in_buffer_exception : 
      virtual public system_exception
   {
   public:
      in_buffer_exception(::ca::application * papp, HRESULT errorCode) :
         ca(papp),
         system_exception(papp, errorCode)
      {
      }
   };

   class CLASS_DECL_ca in_buffer :
      virtual public ::radix::object
   {
     byte *_buffer;
     byte *_bufferLimit;
     byte *_bufferBase;
     reader * _stream;
     uint64 _processedSize;
     uint32 _bufferSize;
     bool _wasFinished;

     bool ReadBlock();
     byte ReadBlock2();

   public:
     HRESULT ErrorCode;

     in_buffer();
     ~in_buffer() { Free(); }

     bool Create(uint32 bufferSize);
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
     uint32 ReadBytes(byte *buf, uint32 size)
     {
       if ((uint32)(_bufferLimit - _buffer) >= size)
       {
         for (uint32 i = 0; i < size; i++)
           buf[i] = _buffer[i];
         _buffer += size;
         return size;
       }
       for (uint32 i = 0; i < size; i++)
       {
         if (_buffer >= _bufferLimit)
           if (!ReadBlock())
             return i;
         buf[i] = *_buffer++;
       }
       return size;
     }
     uint64 GetProcessedSize() const { return _processedSize + (_buffer - _bufferBase); }
     bool WasFinished() const { return _wasFinished; }
   };

} // namespace ex1
