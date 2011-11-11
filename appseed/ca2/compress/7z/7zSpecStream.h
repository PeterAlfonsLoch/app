// 7zSpecStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace compress
{

   class size_count_reader2:
      public ::ex1::reader,
      public ::compress::get_sub_stream_size_interface
   {
   public:

      ::ca::smart_pointer < ::ex1::reader > _stream;
      ::ca::smart_pointer < ::compress::get_sub_stream_size_interface > _getSubStreamSize;
      uint64 _size;

      void Init(::ex1::reader *stream)
      {
         _stream = stream;
         _getSubStreamSize = dynamic_cast < ::compress::get_sub_stream_size_interface * > (_stream.m_p);
         _size = 0;
      }
      uint64 GetSize() const { return _size; }

   //   MY_UNKNOWN_IMP1(::compress::get_sub_stream_size_interface)

      ::primitive::memory_size read(void *data, ::primitive::memory_size size);

      ex1::HRes GetSubStreamSize(uint64 subStream, uint64 *value);
   };

} // namespace compress
