// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"

/*#include "LimitedStreams.h"
#include "../../Common/Defs.h"*/

namespace file
{

   memory_size_t limited_reader::read(void *data, memory_size_t size)
   {
     memory_size_t realProcessedSize = 0;
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