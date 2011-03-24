#include "StdAfx.h"

namespace ex1
{

   void size_count_writer::write(const void *data, DWORD_PTR size, DWORD_PTR * processedSize)
   {
      DWORD_PTR realProcessedSize;
      _stream->write(data, size, &realProcessedSize);
      _size += realProcessedSize;
      if (processedSize)
         *processedSize = realProcessedSize;
   }

} // namespace ex1