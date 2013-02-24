#include "framework.h"


namespace gen
{


   reader::reader()
   {
   }

   reader::reader(reader * preader) :
      m_spreader(preader)
   {
   }

   reader::reader(const reader & reader)
   {
      operator = (reader);
   }

   reader::~reader()
   {
   }


   ::primitive::memory_size reader::read(void * lpBuf, ::primitive::memory_size nCount)
   {
      // if stack overflows or function crashes here, probably this member should be overridden
      return m_spreader->read(lpBuf, nCount);
   }

   file_position reader::find(const void * pFind, ::primitive::memory_size size, const file_position * limit)
   {
      byte * signature = (byte *) pFind;
      primitive::memory_size signatureSize = size;
      uint64_t resPos = 0;
      byte_buffer byteBuffer2;
      byteBuffer2.SetCapacity(signatureSize);
      if(FAILED(ReadStream_FALSE(this, byteBuffer2, signatureSize)))
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

   void reader::write(writer & writer)
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

   reader & reader::operator = (const reader & reader)
   {
      if(this != &reader)
      {
         m_spreader = reader.m_spreader;
      }
      return *this;
   }

   bool reader::is_reader_null()
   {
      return m_spreader.is_null();
   }

   bool reader::is_reader_set()
   {
      return m_spreader.is_set();
   }

   void reader::close()
   {
      if(m_spreader.is_set())
      {
         m_spreader->close();
         gen::release(m_spreader.m_p);
      }
   }

   void reader::to_hex(string & str, ::primitive::memory_position dwStart, ::primitive::memory_position dwEnd)
   {
      primitive::memory memory(get_app());
      seek((file_offset) dwStart, seek_begin);
      ::primitive::memory_position uiPos = 0;
      ::primitive::memory_size uiRead;
      memory.allocate(1024);
      strsize nCount = dwEnd - dwStart;
      int32_t iTry = 0;
      while((uiRead = read(&memory.get_data()[uiPos], min(memory.get_size() - uiPos, (::primitive::memory_size) nCount))) > 0)
      {
         uiPos += uiRead;
         nCount -= uiRead;
         iTry++;
         if(iTry == 2)
         {
            memory.allocate_add_up(1024 * 1024);
         }
      }
      memory.allocate((::primitive::memory_size) uiPos);
      memory.to_hex(str);
   }



} // namespace gen




