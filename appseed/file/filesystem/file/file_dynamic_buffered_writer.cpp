#include "framework.h"


namespace file
{


   byte *dynamic_buffered_writer::GetBufPtrForWriting(size_t addSize)
   {

      addSize += _size;

      if (addSize < _size)
         return NULL;

      _buffer.EnsureCapacity(addSize);

      return (byte *)_buffer + _size;

   }


   void dynamic_buffered_writer::CopyToBuffer(byte_buffer &dest) const
   {

      dest.SetCapacity(_size);

      memcpy(dest, _buffer, _size);

   }


   void dynamic_buffered_writer::write(const void *data, uint_ptr size, uint_ptr *processedSize)
   {
      if (processedSize)
         *processedSize = 0;
      if (size == 0)
         return;
      byte *buf = GetBufPtrForWriting(size);
      if (!buf)
         throw memory_exception(get_app());
      memcpy(buf, data, size);
      UpdateSize(size);
      if (processedSize)
         *processedSize = size;
   }


} // namespace core



