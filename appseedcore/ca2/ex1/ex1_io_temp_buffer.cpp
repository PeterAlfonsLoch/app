// InOutTempBuffer.cpp
// at sector8J on afternoon of 13/01/2011 - Thursday
#include "StdAfx.h"

/*#include "../../../C/7zCrc.h"

#include "InOutTempBuffer.h"
#include "StreamUtils.h"

using namespace NWindows;
using namespace NFile;
using namespace NDirectory;*/

namespace ex1
{

   static const uint32 kTempBufSize = (1 << 20);

   static LPCTSTR kTempFilePrefixString = TEXT("7zt");

   temp_io_buffer::temp_io_buffer(): _buf(NULL) { }

   void temp_io_buffer::Create()
   {
      if (!_buf)
         _buf = new Byte[kTempBufSize];
   }

   temp_io_buffer::~temp_io_buffer()
   {
      delete []_buf;
   }

   void temp_io_buffer::InitWriting()
   {
      _bufPos = 0;
      _tempFileCreated = false;
      _size = 0;
      _crc = CRC_INIT_VAL;
   }

   bool temp_io_buffer::WriteToFile(const void *data, uint32 size)
   {
      if (size == 0)
         return true;
      if (!_tempFileCreated)
      {
         _tempFileName = System.file().time_square(kTempFilePrefixString);
         _tempFile = System.file().get(_tempFileName);
         _tempFileCreated = _tempFile.is_set();
      }
      uint32 processed = size;
      _outFile->write(data, size);
      _crc = crc_update(_crc, data, processed);
      _size += processed;
      return (processed == size);
   }

   bool temp_io_buffer::Write(const void *data, uint32 size)
   {
      if (_bufPos < kTempBufSize)
      {
         uint32 cur = MyMin(kTempBufSize - _bufPos, size);
         memcpy(_buf + _bufPos, data, cur);
         _crc = crc_update(_crc, data, cur);
         _bufPos += cur;
         size -= cur;
         data = ((const Byte *)data) + cur;
         _size += cur;
      }
      return WriteToFile(data, size);
   }

   HRESULT temp_io_buffer::WriteToStream(writer *stream)
   {
      _outFile->close();

      uint64 size = 0;
      uint32 crc = CRC_INIT_VAL;

      if (_bufPos > 0)
      {
         RINOK(WriteStream(stream, _buf, _bufPos));
         crc = crc_update(crc, _buf, _bufPos);
         size += _bufPos;
      }
      if (_tempFileCreated)
      {
         ::ex1::filesp inFile(get_app());
         if (!inFile->open(_tempFileName, ex1::file::mode_read | ex1::file::type_binary))
            return E_FAIL;
         while (size < _size)
         {
            uint32 processed;
            throw "should implement below ReadPart from InFile";
            /*if (!inFile.ReadPart(_buf, kTempBufSize, processed))
               return E_FAIL;*/
            if (processed == 0)
               break;
            RINOK(WriteStream(stream, _buf, processed));
            crc = crc_update(crc, _buf, processed);
            size += processed;
         }
      }
      return (_crc == crc && size == _size) ? S_OK : E_FAIL;
   }

   void temp_io_writer::write(const void *data, DWORD_PTR size, DWORD_PTR * processed)
   {
      if (!_buf->Write(data, size))
      {
         if (processed != NULL)
            *processed = 0;
         throw E_FAIL;
      }
      if (processed != NULL)
         *processed = size;
   }

} // namespace ex1