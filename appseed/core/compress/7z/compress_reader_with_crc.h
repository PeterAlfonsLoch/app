// InStreamWithCRC.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace libcompress
{

   class reader_with_crc:
      public ::ca::reader
   {
   public:
      sp(::ca::reader) _stream;
      uint64 _size;
      uint32 _crc;
      bool _wasFinished;

      memory_size_t read(void *data, memory_size_t size);
      void SetStream(::ca::reader *stream) { _stream = stream;  }
      void Init()
      {
         _size = 0;
         _wasFinished = false;
         _crc = CRC_INIT_VAL;
      }
      void ReleaseStream() { ::ca::release(_stream.m_p); }
      uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
      uint64 GetSize() const { return _size; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace libcompress
