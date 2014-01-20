#include "framework.h"

namespace file
{

   void size_count_writer::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize)
   {
      ::primitive::memory_size realProcessedSize;
      _stream->write(data, size, &realProcessedSize);
      _size += realProcessedSize;
      if (processedSize)
         *processedSize = realProcessedSize;
   }

} // namespace file
