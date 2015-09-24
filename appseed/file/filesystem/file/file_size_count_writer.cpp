#include "framework.h"

namespace file
{

   void size_count_writer::write(const void *data, memory_size_t size, memory_size_t * processedSize)
   {
      memory_size_t realProcessedSize;
      _stream->write(data, size, &realProcessedSize);
      _size += realProcessedSize;
      if (processedSize)
         *processedSize = realProcessedSize;
   }

} // namespace file
