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
      uint64_t _size;
      uint32_t _crc;
      bool _wasFinished;

      ::primitive::memory_size read(void *data, ::primitive::memory_size size);
      void SetStream(::ca::reader *stream) { _stream = stream;  }
      void Init()
      {
         _size = 0;
         _wasFinished = false;
         _crc = CRC_INIT_VAL;
      }
      void ReleaseStream() { ca::release(_stream.m_p); }
      uint32_t GetCRC() const { return CRC_GET_DIGEST(_crc); }
      uint64_t GetSize() const { return _size; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace libcompress
