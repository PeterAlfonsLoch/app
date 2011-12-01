#include "StdAfx.h"

namespace ex1
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

   void dynamic_buffered_writer::write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize)
   {
      if (processedSize)
         *processedSize = 0;
      if (size == 0)
         return;
      byte *buf = GetBufPtrForWriting(size);
      if (!buf)
         AfxThrowMemoryException();
      memcpy(buf, data, size);
      UpdateSize(size);
      if (processedSize)
         *processedSize = size;
   }

} // namespace ex1