// 7zSpecStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"

namespace libcompress
{

   ::primitive::memory_size size_count_reader2::read(void *data, ::primitive::memory_size size)
   {
     ::primitive::memory_size realProcessedSize = realProcessedSize = _stream->read(data, size);
     _size += realProcessedSize;
     return realProcessedSize;
   }

   ::ca::HRes size_count_reader2::GetSubStreamSize(uint64_t subStream, uint64_t *value)
   {
     if (_getSubStreamSize == NULL)
       return E_NOTIMPL;
     return  _getSubStreamSize->GetSubStreamSize(subStream, value);
   }


}
