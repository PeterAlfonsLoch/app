// InOutTempBuffer.h
// at sector8J on afternoon of 13/01/2011 - Thursday

#pragma once


/*#include "../../Common/MyCom.h"
#include "../../Windows/FileDir.h"
#include "../../Windows/FileIO.h"

#include "../IStream.h"*/

namespace ex1
{

   class temp_io_buffer : 
      virtual public ::radix::object

   {
   public:
      //NWindows::NFile::NDirectory::CTempFile _tempFile;
      //NWindows::NFile::NIO::COutFile _outFile;
      ex1::filesp       _tempFile;
      ex1::filesp       _outFile;
      byte *            _buf;
      uint32            _bufPos;
      string            _tempFileName;
      bool              _tempFileCreated;
      uint64            _size;
      uint32            _crc;


      temp_io_buffer();
      virtual ~temp_io_buffer();

      bool WriteToFile(const void *data, uint32 size);
      void Create();

      void InitWriting();
      bool Write(const void *data, uint32 size);

      HRESULT WriteToStream(writer *stream);
      uint64 GetDataSize() const { return _size; }
   };

   class temp_io_writer :
      virtual public writer
   {
      temp_io_buffer *_buf;
   public:
      void Init(temp_io_buffer *buffer) 
      {
         _buf = buffer; 
      }
      void write(const void *data, DWORD_PTR size, DWORD_PTR * processedSize);
   };

} // namespace ex1
