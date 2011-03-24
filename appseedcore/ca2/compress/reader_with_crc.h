// InStreamWithCRC.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace compress
{

   class reader_with_crc:
      public ::ex1::reader
   {
   public:
      sp(::ex1::reader) _stream;
      uint64 _size;
      uint32 _crc;
      bool _wasFinished;

      DWORD_PTR read(void *data, DWORD_PTR size);
      void SetStream(::ex1::reader *stream) { _stream = stream;  }
      void Init()
      {
         _size = 0;
         _wasFinished = false;
         _crc = CRC_INIT_VAL;
      }
      void ReleaseStream() { gen::release(_stream.m_p); }
      uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
      uint64 GetSize() const { return _size; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace compress