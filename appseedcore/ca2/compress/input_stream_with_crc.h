// InStreamWithCRC.h
// from 7-zip on dawn of 13/01/2001 - Thursday

namespace compress
{

   class input_stream_with_crc:
      public ::ex1::byte_input_stream
   {
   public:

      sp(::ex1::byte_input_stream)  _stream;
      uint64         _size;
      uint32         _crc;

      ::primitive::memory_size read(void *data, ::primitive::memory_size size);
      file_position seek(file_offset offset, ::ex1::e_seek seekOrigin);
      void SetStream(::ex1::byte_input_stream *stream) { _stream = stream;  }
      void Init()
      {
         _size = 0;
         // _wasFinished = false;
         _crc = CRC_INIT_VAL;
      }
      void ReleaseStream() { gen::release(_stream.m_p); }
      uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
      uint64 GetSize() const { return _size; }
      // bool WasFinished() const { return _wasFinished; }
   };

} // namespace compress