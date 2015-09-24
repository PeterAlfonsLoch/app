// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


/*#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"
#include "../IStream.h"*/


namespace file
{

   class limited_reader:
      public reader
   {
      reader * _stream;
      file_size _size;
      file_size _pos;
      bool _wasFinished;
   public:
      void SetStream(reader *stream) { _stream = stream; }
      void ReleaseStream() 
      {
         //_stream.Release(); 
      }
      void Init(file_size streamSize)
      {
         _size = streamSize;
         _pos = 0;
         _wasFinished = false;
      }

      memory_size_t read(void *data, memory_size_t size);
      file_size GetSize() const { return _pos; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace file
