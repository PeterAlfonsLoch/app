// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"

/*#include "LimitedStreams.h"
#include "../../Common/Defs.h"*/

namespace ex1
{

   ::primitive::memory_size limited_reader::read(void *data, ::primitive::memory_size size)
   {
     primitive::memory_size realProcessedSize = 0;
     uint32 sizeToRead = (uint32)min((_size - _pos), (uint64)size);
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


} // namespace exit