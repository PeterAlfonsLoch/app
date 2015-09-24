// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace file
{


   void limited_writer::write(const void *data, memory_size_t size, memory_size_t * processedSize)
   {
      if (processedSize != NULL)
         *processedSize = 0;
      if (size > _size)
      {
         if (_size == 0)
         {
            _overflow = true;
            if (!_overflowIsAllowed)
               throw system_exception(get_app(), E_FAIL);
            if (processedSize != NULL)
               *processedSize = size;
            return;
         }
         size = (uint32_t)_size;
      }
      if (_stream)
         _stream->write(data, size, &size);
      _size -= size;
      if (processedSize != NULL)
         *processedSize = size;
      return;
   }

} // namespace file
