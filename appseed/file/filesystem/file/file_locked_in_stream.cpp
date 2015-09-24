// LockedStream.cpp

#include "framework.h"

namespace file
{

   memory_size_t locked_in_stream::read(file_position_t startPos, void *data, memory_size_t size)
   {
      cslock sl(&_criticalSection);
      _stream->seek((file_offset_t) startPos, ::file::seek_begin);
      return _stream->read(data, size);
   }

   memory_size_t locked_reader::read(void *data, memory_size_t size)
   {
      memory_size_t realProcessedSize = _lockedInStream->read((file_position_t) _pos, data, size);
      _pos += realProcessedSize;
      return realProcessedSize;
   }

} // namespace file
