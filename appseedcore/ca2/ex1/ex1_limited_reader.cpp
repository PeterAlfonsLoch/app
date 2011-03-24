// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "StdAfx.h"

/*#include "LimitedStreams.h"
#include "../../Common/Defs.h"*/

namespace ex1
{

   DWORD_PTR limited_reader::read(void *data, DWORD_PTR size)
   {
     uint32 realProcessedSize = 0;
     uint32 sizeToRead = (uint32)min((_size - _pos), (uint64)size);
     HRESULT result = S_OK;
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