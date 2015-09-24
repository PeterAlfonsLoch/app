// 7zSpecStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace libcompress
{

   class size_count_reader2:
      public ::file::reader,
      public ::libcompress::get_sub_stream_size_interface
   {
   public:

      smart_pointer < ::file::reader > _stream;
      smart_pointer < ::libcompress::get_sub_stream_size_interface > _getSubStreamSize;
      uint64_t _size;

      void Init(::file::reader *stream)
      {
         _stream = stream;
         _getSubStreamSize = dynamic_cast < ::libcompress::get_sub_stream_size_interface * > (_stream.m_p);
         _size = 0;
      }
      uint64_t GetSize() const { return _size; }

   //   MY_UNKNOWN_IMP1(::libcompress::get_sub_stream_size_interface)

      memory_size_t read(void *data, memory_size_t size);

      HRes GetSubStreamSize(uint64_t subStream, uint64_t *value);
   };

} // namespace libcompress
