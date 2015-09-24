// OutStreamWithCRC.h
// from 7-zip at night after the Churrasco Setorial on 2010-12-21
#pragma once

/*#include "../../../../C/7zCrc.h"

#include "../../../Common/MyCom.h"

#include "../../IStream.h"
*/

namespace libcompress
{

   class writer_with_crc:
      public ::ca::writer
   {
   public:


      ::ca::writer *   _stream;
      uint64            _size;
      uint32            _crc;
      bool              _calculate;


      void write(const void *data, memory_size_t size, memory_size_t *processedSize);
      void SetStream(writer *stream) { _stream = stream; }
      void ReleaseStream()  {}
      //{ _stream.Release(); }
      void Init(bool calculate = true)
      {
         _size = 0;
         _calculate = calculate;
         _crc = CRC_INIT_VAL;
      }
      void InitCRC() { _crc = CRC_INIT_VAL; }
      uint64 GetSize() const { return _size; }
      uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
   };

} // namespace libcompress
