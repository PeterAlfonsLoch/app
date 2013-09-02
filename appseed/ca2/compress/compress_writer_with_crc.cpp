// OutStreamWithCRC.cpp
#include "framework.h"

//#include "OutStreamWithCRC.h"

namespace libcompress
{

   void writer_with_crc::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize)
   {
     if (_stream)
       _stream->write(data, size, &size);
     if (_calculate)
       _crc = crc_update(_crc, data, size);
     _size += size;
     if (processedSize != NULL)
       *processedSize = size;
   }


} // namespace libcompress
