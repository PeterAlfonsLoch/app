// OutStreamWithCRC.cpp
// from 7-zip at night after the Churrasco Setorial on 2010-12-21
#include "StdAfx.h"

//#include "OutStreamWithCRC.h"

namespace compress
{

   void writer_with_crc::write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize)
   {
     if (_stream)
       _stream->write(data, size, &size);
     if (_calculate)
       _crc = crc_update(_crc, data, size);
     _size += size;
     if (processedSize != NULL)
       *processedSize = size;
   }


} // namespace compress