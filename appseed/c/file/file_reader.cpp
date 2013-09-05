#include "framework.h"


namespace file
{


   reader::reader()
   {
   }

   reader::~reader()
   {
   }


   ::primitive::memory_size reader::read(void * lpBuf, ::primitive::memory_size nCount)
   {
      
      throw interface_only_exception(get_app());
      
      return 0;

   }

   file_position reader::find(const void * pFind, ::primitive::memory_size size, const file_position * limit)
   {
      byte * signature = (byte *) pFind;
      primitive::memory_size signatureSize = size;
      uint64_t resPos = 0;
      byte_buffer byteBuffer2;
      byteBuffer2.SetCapacity(signatureSize);
      if(FAILED(read_reader_false(this, byteBuffer2, signatureSize)))
         throw simple_exception(get_app());

      if (memcmp(byteBuffer2, signature, signatureSize) == 0)
         return resPos;

      const uint32_t kBufferSize = (1 << 16);
      byte_buffer byteBuffer;
      byteBuffer.SetCapacity(kBufferSize);
      byte *buffer = byteBuffer;
      primitive::memory_size numPrevBytes = signatureSize - 1;
      memcpy(buffer, (const byte *)byteBuffer2 + 1, numPrevBytes);
      resPos = 1;
      for (;;)
      {
         if (limit != NULL)
            if (resPos > *limit)
               throw simple_exception(get_app());
         do
         {
            ::primitive::memory_size numReadBytes = kBufferSize - numPrevBytes;
            ::primitive::memory_size processedSize;
            processedSize = read(buffer + numPrevBytes, numReadBytes);
            numPrevBytes += processedSize;
            if (processedSize == 0)
               throw simple_exception(get_app());
         }
         while (numPrevBytes < signatureSize);
         uint32_t numTests = (uint32_t) (numPrevBytes - signatureSize + 1);
         for (uint32_t pos = 0; pos < numTests; pos++)
         {
            byte b = signature[0];
            for (; buffer[pos] != b && pos < numTests; pos++);
            if (pos == numTests)
               break;
            if (memcmp(buffer + pos, signature, signatureSize) == 0)
            {
               resPos += pos;
               return resPos;
            }
         }
         resPos += numTests;
         numPrevBytes -= numTests;
         memmove(buffer, buffer + numTests, numPrevBytes);
      }

   }

   void reader::write_to(writer & writer)
   {
      ::primitive::memory_size uiRead;
      ::primitive::memory_size uiBufSize = 1024 * 1024;
      ::primitive::memory_size uiSize = 0;

      char * buf = (char *) malloc((::primitive::memory_size)uiBufSize);
      if(buf == NULL)
         throw "no primitive::memory";
      try
      {
         while(true)
         {
            uiRead = read(buf, uiBufSize);
            writer.write(buf, uiRead);
            if(uiRead < uiBufSize)
            {
               break;
            }
            uiSize += uiBufSize;
         }
      }
      catch(...)
      {
      }
      free(buf);
   }

   void reader::close()
   {
   }

   file_position reader::get_position()
   {
      throw interface_only_exception(get_app());
      return 0;
   }

   static const ::primitive::memory_size kBlockSize = ((uint32_t)1 << 31);

   HRESULT read_reader(::file::reader * stream, void * data, ::primitive::memory_size * processedSize)
   {
      ::primitive::memory_size size = *processedSize;
      *processedSize = 0;
      while (size != 0)
      {
         ::primitive::memory_size curSize = min(size, kBlockSize);
         ::primitive::memory_size processedSizeLoc;
         HRESULT res = S_OK;
         try
         {
            processedSizeLoc = stream->read(data, curSize);
         }
         catch(...)
         {
            res = E_FAIL;
         }
         *processedSize += processedSizeLoc;
         data = (void *)((byte *)data + processedSizeLoc);
         size -= processedSizeLoc;
         RINOK(res);
         if (processedSizeLoc == 0)
            return S_OK;
      }
      return S_OK;
   }

   HRESULT read_reader_false(reader * stream, void * data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processedSize = size;
      RINOK(read_reader(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : S_FALSE;
   }

   HRESULT read_reader_fail(reader * stream, void * data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processedSize = size;
      RINOK(read_reader(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : E_FAIL;
   }


   


} // namespace file




