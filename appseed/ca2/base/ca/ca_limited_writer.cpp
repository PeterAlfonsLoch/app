// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace ca
{


   void limited_writer::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize)
   {
      if (processedSize != ::null())
         *processedSize = 0;
      if (size > _size)
      {
         if (_size == 0)
         {
            _overflow = true;
            if (!_overflowIsAllowed)
               throw system_exception(get_app(), E_FAIL);
            if (processedSize != ::null())
               *processedSize = size;
            return;
         }
         size = (uint32_t)_size;
      }
      if (_stream)
         _stream->write(data, size, &size);
      _size -= size;
      if (processedSize != ::null())
         *processedSize = size;
      return;
   }

} // namespace ca