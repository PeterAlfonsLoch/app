// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"

/*#include "LimitedStreams.h"
#include "../../Common/Defs.h"*/

namespace file
{

   ::primitive::memory_size limited_reader::read(void *data, ::primitive::memory_size size)
   {
     primitive::memory_size realProcessedSize = 0;
     uint32_t sizeToRead = (uint32_t)MIN((_size - _pos), (uint64_t)size);
//     HRESULT result = S_OK;
     if (sizeToRead > 0)
     {
       realProcessedSize = _stream->read(data, sizeToRead);
       _pos += realProcessedSize;
       if (realProcessedSize == 0)
         _wasFinished = true;
     }
     return realProcessedSize;
   }


} // namespace file