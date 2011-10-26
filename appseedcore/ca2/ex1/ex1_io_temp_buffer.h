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
      ex1::filesp                      _tempFile;
      ex1::filesp                      _outFile;
      string                           _tempFileName;
      bool                             _tempFileCreated;
      uint32                           _crc;
      ::primitive::memory              m_memory;
      ::primitive::memory_position     _bufPos;
      ::primitive::memory_size         _size;


      temp_io_buffer();
      virtual ~temp_io_buffer();

      bool write_to_file(const void * data, ::primitive::memory_size size);
      using ::ex1::request_interface::create;
      void create();

      void InitWriting();
      bool write(const void *data, ::primitive::memory_size size);

      HRESULT write_to_stream(writer *stream);
      ::primitive::memory_size GetDataSize() const 
      { 
         return _size; 
      }
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
      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize);
   };

} // namespace ex1
