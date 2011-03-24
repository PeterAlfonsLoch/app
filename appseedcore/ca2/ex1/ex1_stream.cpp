#include "StdAfx.h"


namespace ex1
{

   DWORD_PTR reader::read(void *lpBuf, DWORD_PTR nCount)
   {
      UNREFERENCED_PARAMETER(lpBuf);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }


   void reader::write(output_stream & ostream)
   {
      UINT uiRead;
      UINT uiBufSize = 1024 * 1024;
      UINT uiSize = 0;

      char * buf = (char *) malloc(uiBufSize);
      if(buf == NULL)
         throw "no primitive::memory";
      try
      {
         while(true)
         {
            uiRead = read(buf, uiBufSize);
            ostream.write(buf, uiRead);
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

   void reader::read(input_stream & ostream)
   {
      UNREFERENCED_PARAMETER(ostream);
      throw not_implemented_exception();
   }


// FindSignature.cpp
// from 7-zip on 2012-12-23, lunch time
//#include "StdAfx.h"

/*#include "Common/Buffer.h"

#include "FindSignature.h"

#include "../../Common/StreamUtils.h"*/

   uint64 reader::find(const void * pFind, unsigned size, const uint64 * limit)
   {
      byte * signature = (byte *) pFind;
      unsigned signatureSize = size;
     uint64 resPos = 0;
     byte_buffer byteBuffer2;
     byteBuffer2.SetCapacity(signatureSize);
     if(FAILED(ReadStream_FALSE(this, byteBuffer2, signatureSize)))
        throw simple_exception();

     if (memcmp(byteBuffer2, signature, signatureSize) == 0)
       return resPos;

     const uint32 kBufferSize = (1 << 16);
     byte_buffer byteBuffer;
     byteBuffer.SetCapacity(kBufferSize);
     Byte *buffer = byteBuffer;
     uint32 numPrevBytes = signatureSize - 1;
     memcpy(buffer, (const Byte *)byteBuffer2 + 1, numPrevBytes);
     resPos = 1;
     for (;;)
     {
       if (limit != NULL)
         if (resPos > *limit)
           throw simple_exception();
       do
       {
         uint32 numReadBytes = kBufferSize - numPrevBytes;
         uint32 processedSize;
         processedSize = read(buffer + numPrevBytes, numReadBytes);
         numPrevBytes += processedSize;
         if (processedSize == 0)
           throw simple_exception();
       }
       while (numPrevBytes < signatureSize);
       uint32 numTests = numPrevBytes - signatureSize + 1;
       for (uint32 pos = 0; pos < numTests; pos++)
       {
         Byte b = signature[0];
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


   input_stream::input_stream()
   {
      m_preader = NULL;
   }

   input_stream::input_stream(reader * preader)
   {
      m_preader = preader;
   }

   input_stream::~input_stream()
   {

   }

   DWORD_PTR input_stream::read(void *lpBuf, DWORD_PTR nCount)
   {
      if(m_preader == this)
         throw new interface_only_exception();
      return m_preader->read(lpBuf, nCount);
   }

   DWORD_PTR input_stream::seek(INT_PTR offset, e_seek eseek)
   {
      throw new interface_only_exception();
   }

   input_stream & input_stream::operator >> (char & ch)
   {
      read(&ch, sizeof(ch));
      return *this;
   }

   input_stream & input_stream::operator >> (unsigned char & uch)
   {
      read(&uch, sizeof(uch));
      return *this;
   }

   input_stream & input_stream::operator >> (short & sh)
   {
      read(&sh, sizeof(sh));
      return *this;
   }

   input_stream & input_stream::operator >> (unsigned short & ush)
   {
      read(&ush, sizeof(ush));
      return *this;
   }

   input_stream & input_stream::operator >> (wchar_t & wch)
   {
      read(&wch, sizeof(wch));
      return *this;
   }

   input_stream & input_stream::operator >> (bool & b)
   {
      read(&b, sizeof(b));
      return *this;
   }

   input_stream & input_stream::operator >> (int & i)
   {
      UINT uiRead = read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         throw "failed to read int";
      return *this;
   }

   input_stream & input_stream::operator >> (unsigned int & ui)
   {
      UINT uiRead = read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         throw "failed to read unsigned int";
      return *this;
   }

   input_stream & input_stream::operator >> (long & l)
   {
      UINT uiRead = read(&l, sizeof(l));
      if(uiRead != sizeof(l))
         throw "failed to read long";
      return *this;
   }

   input_stream & input_stream::operator >> (unsigned long & ul)
   {
      read(&ul, sizeof(ul));
      return *this;
   }

   input_stream & input_stream::operator >> (__int64 & i)
   {
      read(&i, sizeof(i));
      return *this;
   }

   input_stream & input_stream::operator >> (unsigned __int64 & ui)
   {
      read(&ui, sizeof(ui));
      return *this;
   }

   input_stream & input_stream::operator >> (float & f)
   {
      read(&f, sizeof(f));
      return *this;
   }

   input_stream & input_stream::operator >> (double & d)
   {
      read(&d, sizeof(d));
      return *this;
   }

   input_stream & input_stream::operator >> (LPRECT lprect)
   {
      read(&lprect->left,     sizeof(lprect->left));
      read(&lprect->top,      sizeof(lprect->top));
      read(&lprect->right,    sizeof(lprect->right));
      read(&lprect->bottom,   sizeof(lprect->bottom));
      return *this;
   }

   input_stream & input_stream::operator >> (SIZE & size)
   {
      read(&size.cx,     sizeof(size.cx));
      read(&size.cy,      sizeof(size.cy));
      return *this;
   }

   input_stream & input_stream::operator >> (::ca::type_info & info)
   {
      int iLen;
      read(&iLen, sizeof(iLen));
      char * psz = (char *) malloc(iLen + 1);
      read(psz, iLen);
      psz[iLen] = '\0';
      info.raw_name(psz);
      free((void *) psz);
      return *this;
   }


   input_stream & input_stream::operator >> (serializable & serializable)
   {
      serializable.read(*this);
      return *this;
   }


   string input_stream::get_location() const
   {
      return "<unknown input_stream location>";
   }

   void input_stream::seek_to_begin()
   {
      throw "seek_to_begin not supported in raw input_stream";
   }










   void writer::write(const void *lpBuf, DWORD_PTR nCount)
   {
      DWORD_PTR dwWritten;
      while (nCount > 0)
      {
         dwWritten = 0;
         write(lpBuf, nCount, &dwWritten);
         if(dwWritten <= 0)
            throw "written 0 bytes";
         lpBuf = (const void *)((const byte *)lpBuf + dwWritten);
         nCount -= dwWritten;
      }
      if(nCount < 0)
         throw "written more than requested count of bytes";
   }

   void writer::write(const void *lpBuf, DWORD_PTR nCount, DWORD_PTR * dwWritten)
   {
      // default implementation
      write(lpBuf, nCount);
      *dwWritten = nCount;
   }



   void writer::write(output_stream & ostream)
   {
      UNREFERENCED_PARAMETER(ostream);
      throw not_implemented_exception();
   }

   void writer::read(input_stream & istream)
   {
      UINT uiRead;
      UINT uiBufSize = 1024 * 1024;
      UINT uiSize = 0;

      char * buf = (char *) malloc(uiBufSize);
      if(buf == NULL)
         throw "no primitive::memory";
      try
      {
         while(true)
         {
            uiRead = istream.read(buf, uiBufSize);
            write(buf, uiRead);
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

   output_stream::output_stream()
   {
      m_pwriter = NULL;
   }

   output_stream::output_stream(writer * pwriter)
   {
      m_pwriter = pwriter;
   }

   output_stream::~output_stream()
   {

   }

   void output_stream::write(const void * lpBuf, DWORD_PTR nCount)
   {
      m_pwriter->write(lpBuf, nCount);
   }

   DWORD_PTR output_stream::seek(INT_PTR offset, e_seek eseek)
   {
      throw new interface_only_exception();
   }

   output_stream & output_stream::operator << (char ch)
   {
      write(&ch, sizeof(ch));
      return *this;
   }

   output_stream & output_stream::operator << (unsigned char uch)
   {
      write(&uch, sizeof(uch));
      return *this;
   }

   output_stream & output_stream::operator << (short sh)
   {
      write(&sh, sizeof(sh));
      return *this;
   }

   output_stream & output_stream::operator << (unsigned short ush)
   {
      write(&ush, sizeof(ush));
      return *this;
   }

   output_stream & output_stream::operator << (wchar_t wch)
   {
      write(&wch, sizeof(wch));
      return *this;
   }

   output_stream & output_stream::operator << (bool b)
   {
      write(&b, sizeof(b));
      return *this;
   }

   output_stream & output_stream::operator << (int i)
   {
      write(&i, sizeof(i));
      return *this;
   }

   output_stream & output_stream::operator << (unsigned int ui)
   {
      write(&ui, sizeof(ui));
      return *this;
   }

   output_stream & output_stream::operator << (long l)
   {
      write(&l, sizeof(l));
      return *this;
   }

   output_stream & output_stream::operator << (__int64 i)
   {
      write(&i, sizeof(i));
      return *this;
   }

   output_stream & output_stream::operator << (unsigned long ul)
   {
      write(&ul, sizeof(ul));
      return *this;
   }

   output_stream & output_stream::operator << (unsigned __int64 ui)
   {
      write(&ui, sizeof(ui));
      return *this;
   }

   output_stream & output_stream::operator << (float f)
   {
      write(&f, sizeof(f));
      return *this;
   }

   output_stream & output_stream::operator << (double d)
   {
      write(&d, sizeof(d));
      return *this;
   }

   output_stream & output_stream::operator << (LPCRECT lpcrect)
   {
      write(&lpcrect->left,     sizeof(lpcrect->left));
      write(&lpcrect->top,      sizeof(lpcrect->top));
      write(&lpcrect->right,    sizeof(lpcrect->right));
      write(&lpcrect->bottom,   sizeof(lpcrect->bottom));
      return *this;
   }

   output_stream & output_stream::operator << (SIZE & size)
   {
      write(&size.cx,     sizeof(size.cx));
      write(&size.cy,     sizeof(size.cy));
      return *this;
   }

   output_stream & output_stream::operator << (::ca::type_info & info)
   {
      int iLen = strlen(info.raw_name());
      write(&iLen, sizeof(iLen));
      write(info.raw_name(), iLen);
      return *this;
   }

   output_stream & output_stream::operator << (serializable & serializable)
   {
      serializable.write(*this);
      return *this;
   }

   output_stream & output_stream::operator << (const char * psz)
   {
      write(psz, strlen(psz));
      return *this;
   }

   string output_stream::get_location() const
   {
      return "<unknown output_stream location>";
   }


   io_stream::io_stream()
   {
   }

   io_stream::io_stream(reader * preader, writer * pwriter) :
   input_stream(preader),
      output_stream(pwriter)
   {
   }

   io_stream::~io_stream()
   {
   }

   void io_stream::write(output_stream & ostream)
   {
      input_stream::write(ostream);
   }

   void io_stream::read(input_stream & istream)
   {
      output_stream::read(istream);
   }

   DWORD_PTR io_stream::seek(INT_PTR offset, e_seek eseek)
   {
      input_stream::seek(offset, eseek);
      return output_stream::seek(offset, eseek);
   }

   string io_stream::get_location() const
   {
      return "<unknown io_stream location>";
   }

   static const uint32 kBlockSize = ((uint32)1 << 31);

   HRESULT ReadStream(reader * stream, void * data, size_t * processedSize)
   {
      size_t size = *processedSize;
      *processedSize = 0;
      while (size != 0)
      {
         uint32 curSize = (size < kBlockSize) ? (uint32)size : kBlockSize;
         uint32 processedSizeLoc;
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

   HRESULT ReadStream_FALSE(reader * stream, void *data, size_t size)
   {
      size_t processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : S_FALSE;
   }

   HRESULT ReadStream_FAIL(reader * stream, void * data, size_t size)
   {
      size_t processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : E_FAIL;
   }

   HRESULT WriteStream(writer * stream, const void *data, size_t size)
   {
      HRESULT res = S_OK;
      try
      {
         stream->write(data, size);
      }
      catch(...)
      {
         res = E_FAIL;
      }
      RINOK(res);
      return res;
   }


} // namespace ex1
