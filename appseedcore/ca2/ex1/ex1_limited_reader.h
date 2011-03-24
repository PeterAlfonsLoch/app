// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


/*#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"
#include "../IStream.h"*/


namespace ex1
{

   class limited_reader:
      public reader
   {
      reader * _stream;
      uint64 _size;
      uint64 _pos;
      bool _wasFinished;
   public:
      void SetStream(reader *stream) { _stream = stream; }
      void ReleaseStream() 
      {
         //_stream.Release(); 
      }
      void Init(uint64 streamSize)
      {
         _size = streamSize;
         _pos = 0;
         _wasFinished = false;
      }

      DWORD_PTR read(void *data, DWORD_PTR size);
      uint64 GetSize() const { return _pos; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace ex1