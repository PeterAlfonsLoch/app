// InStreamWithCRC.h
// from 7-zip on dawn of 13/01/2001 - Thursday

namespace libcompress
{

   class input_stream_with_crc:
      public ::ca::byte_input_stream
   {
   public:

      sp(::ca::byte_input_stream)  _stream;
      uint64         _size;
      uint32         _crc;

      memory_size_t read(void *data, memory_size_t size);
      file_position seek(file_offset offset, ::ca::e_seek seekOrigin);
      void SetStream(::ca::byte_input_stream *stream) { _stream = stream;  }
      void Init()
      {
         _size = 0;
         // _wasFinished = false;
         _crc = CRC_INIT_VAL;
      }
      void ReleaseStream() { ::ca::release(_stream.m_p); }
      uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
      uint64 GetSize() const { return _size; }
      // bool WasFinished() const { return _wasFinished; }
   };

} // namespace libcompress
