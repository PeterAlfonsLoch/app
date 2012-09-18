#include "framework.h"


namespace ex1
{





// FindSignature.cpp
// from 7-zip on 2012-12-23, lunch time
//#include "framework.h"

/*#include "Common/Buffer.h"

#include "FindSignature.h"

#include "../../Common/StreamUtils.h"*/


   byte_input_stream::byte_input_stream()
   {
   }

   byte_input_stream::byte_input_stream(reader * preader) :
      reader(preader)
   {
   }

   byte_input_stream::byte_input_stream(const byte_input_stream & istream) :
      reader(istream)
   {
   }

   byte_input_stream::~byte_input_stream()
   {

   }

   byte_input_stream & byte_input_stream::operator >> (char & ch)
   {
      read(&ch, sizeof(ch));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (unsigned char & uch)
   {
      read(&uch, sizeof(uch));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (short & sh)
   {
      read(&sh, sizeof(sh));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (unsigned short & ush)
   {
      read(&ush, sizeof(ush));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (wchar_t & wch)
   {
      read(&wch, sizeof(wch));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (bool & b)
   {
      read(&b, sizeof(b));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (int & i)
   {
      uint64_t uiRead = read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         throw "failed to read int";
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (unsigned int & ui)
   {
      uint64_t uiRead = read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         throw "failed to read unsigned int";
      return *this;
   }

#if defined(WINDOWS)

   byte_input_stream & byte_input_stream::operator >> (long & l)
   {
      uint64_t uiRead = read(&l, sizeof(l));
      if(uiRead != sizeof(l))
         throw "failed to read long";
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (unsigned long & ul)
   {
      read(&ul, sizeof(ul));
      return *this;
   }

#endif

   byte_input_stream & byte_input_stream::operator >> (int64_t & i)
   {
      read(&i, sizeof(i));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (uint64_t & ui)
   {
      read(&ui, sizeof(ui));
      return *this;
   }


   void byte_input_stream::read_arbritary(void * p, count nMax)
   {

      byte b;
      int iRotate = 0;
      byte * pTarget =(byte *) p;
      while(nMax > 0)
      {
         read(&b, sizeof(b));
         switch(iRotate % 8)
         {
         case 0:
            *pTarget |= b & 0x7f;
            break;
         case 1:
            *pTarget |= (b & 0x01) << 7;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 1;
            break;
         case 2:
            *pTarget |= (b & 0x03) << 6;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 2;
            break;
         case 3:
            *pTarget |= (b & 0x07) << 5;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 3;
            break;
         case 4:
            *pTarget |= (b & 0x0f) << 4;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 4;
            break;
         case 5:
            *pTarget |= (b & 0x1f) << 3;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 5;
            break;
         case 6:
            *pTarget |= (b & 0x3f) << 2;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 6;
            break;
         case 7:
            *pTarget |= (b & 0x7f) << 1;
            pTarget++;
            *pTarget |= (b & 0x7f) >> 7;
            break;
         }
         iRotate++;
         if((b & 0x80) == 0)
            break;
      }
      if((b & 0x80) != 0)
         throw "byte count overflow";


   }

   byte_input_stream & byte_input_stream::operator >> (float & f)
   {
      read(&f, sizeof(f));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (double & d)
   {
      read(&d, sizeof(d));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (LPRECT lprect)
   {
      read(&lprect->left,     sizeof(lprect->left));
      read(&lprect->top,      sizeof(lprect->top));
      read(&lprect->right,    sizeof(lprect->right));
      read(&lprect->bottom,   sizeof(lprect->bottom));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (SIZE & size)
   {
      read(&size.cx,     sizeof(size.cx));
      read(&size.cy,      sizeof(size.cy));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (::ca::type_info & info)
   {
      int iLen;
      read(&iLen, sizeof(iLen));
      char * psz = (char *) malloc(iLen + 1);
      read(psz, iLen);
      psz[iLen] = '\0';
      info.name(psz);
      free((void *) psz);
      return *this;
   }


   byte_input_stream & byte_input_stream::operator >> (byte_serializable & serializable)
   {
      serializable.read(*this);
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (id & id)
   {

      operator >> (id.m_chType);

      if(id.m_chType == IDTYPE_TYPE_TEXT)
      {
         string str;
         *this >> str;
         id = str;
      }
      else if(id.m_chType == IDTYPE_TYPE_NUMBER)
      {
         operator >> (id.m_i);
      }

      return *this;

   }

   byte_input_stream & byte_input_stream::operator >> (var & var)
   {
      var.read(*this);
      return *this;
   }

   string byte_input_stream::get_location() const
   {
      return "<unknown byte_input_stream location>";
   }


   file_position byte_input_stream::seek(file_offset offset, e_seek seekOrigin)
   {
      return m_spreader->seek(offset, seekOrigin);
   }


   void byte_input_stream::full_load(string & str)
   {

      seek_to_end();

      ::file_position uiLength = get_position();

      seek_to_begin();

      ::file_position uiCount = uiLength;

      ::file_position uiPos = 0;
      LPSTR lpstr = str.GetBufferSetLength((strsize) (uiLength + 1));
      while(uiCount > 0)
      {
         ::primitive::memory_size uiRead =  read(&lpstr[uiPos], (::primitive::memory_size) uiCount);
         uiCount -= uiRead;
         uiPos+=uiRead;
         if(uiCount > 0)
            Sleep(84);
      }

      str.ReleaseBuffer((strsize) uiLength);

   }







   byte_output_stream::byte_output_stream()
   {
      m_b64bit = false;
   }

   byte_output_stream::byte_output_stream(writer * pwriter) :
      writer(pwriter)
   {
      m_b64bit = false;
   }

   byte_output_stream::byte_output_stream(const  byte_output_stream & ostream) :
      writer(ostream)
   {
      m_b64bit = false;
   }

   byte_output_stream::~byte_output_stream()
   {

   }

   byte_output_stream & byte_output_stream::operator << (char ch)
   {
      write(&ch, sizeof(ch));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (unsigned char uch)
   {
      write(&uch, sizeof(uch));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (short sh)
   {
      write(&sh, sizeof(sh));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (unsigned short ush)
   {
      write(&ush, sizeof(ush));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (wchar_t wch)
   {
      write(&wch, sizeof(wch));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (bool b)
   {
      write(&b, sizeof(b));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (int i)
   {
      write(&i, sizeof(i));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (unsigned int ui)
   {
      write(&ui, sizeof(ui));
      return *this;
   }

   void byte_output_stream::write_arbitrary(int32_t i)
   {

      write_arbitrary((int64_t) i);

   }

   void byte_output_stream::write_arbitrary(uint32_t ui)
   {

      write_arbitrary((uint64_t) ui);

   }

#if defined(WINDOWS)

   byte_output_stream & byte_output_stream::operator << (long l)
   {
      write(&l, sizeof(l));
      return *this;
   }

#endif

   byte_output_stream & byte_output_stream::operator << (int64_t i)
   {
      write(&i, sizeof(i));
      return *this;
   }

   void byte_output_stream::write_arbitrary(int64_t i)
   {

      if(i < 0)
      {
         byte b = (byte)i;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(i >> 28);
         write(&b, sizeof(byte));
         b = (byte)(i >> 35);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 42);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 49);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 56);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(i >> 63);
         write(&b, sizeof(byte));
      }
      else
      {
         
         write_arbitrary((uint64_t) i);

      }

   }

#if defined(WINDOWS)

   byte_output_stream & byte_output_stream::operator << (unsigned long ul)
   {
      write(&ul, sizeof(ul));
      return *this;
   }

#endif

   byte_output_stream & byte_output_stream::operator << (uint64_t ui)
   {
      write(&ui, sizeof(ui));
      return *this;
   }

   void byte_output_stream::write_arbitrary(uint64_t ui)
   {
      if(ui < (1u << 8))
      {
         byte b = (byte)ui;
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 15))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 22))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 29))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 36))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 28);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 43))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(ui >> 28);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 35);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 50))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(ui >> 28);
         write(&b, sizeof(byte));
         b = (byte)(ui >> 35);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 42);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 57))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(ui >> 28);
         write(&b, sizeof(byte));
         b = (byte)(ui >> 35);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 42);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 49);
         write(&b, sizeof(byte));
      }
      else if(ui < (1u << 57))
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(ui >> 28);
         write(&b, sizeof(byte));
         b = (byte)(ui >> 35);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 42);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 49);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 56);
         write(&b, sizeof(byte));
      }
      else
      {
         byte b = (byte)ui;
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 7);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 14);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 21);
         b |= 0x80;
         write(&b, sizeof(byte));
         b |= 0x80;
         b = (byte)(ui >> 28);
         write(&b, sizeof(byte));
         b = (byte)(ui >> 35);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 42);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 49);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 56);
         b |= 0x80;
         write(&b, sizeof(byte));
         b = (byte)(ui >> 63);
         write(&b, sizeof(byte));
      }
   }

   byte_output_stream & byte_output_stream::operator << (float f)
   {
      write(&f, sizeof(f));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (double d)
   {
      write(&d, sizeof(d));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (LPCRECT lpcrect)
   {
      write(&lpcrect->left,     sizeof(lpcrect->left));
      write(&lpcrect->top,      sizeof(lpcrect->top));
      write(&lpcrect->right,    sizeof(lpcrect->right));
      write(&lpcrect->bottom,   sizeof(lpcrect->bottom));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (SIZE & size)
   {
      write(&size.cx,     sizeof(size.cx));
      write(&size.cy,     sizeof(size.cy));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (::ca::type_info & info)
   {
      strsize iLen = strlen(info.name());
      write(&iLen, sizeof(iLen));
      write(info.name(), iLen);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (byte_serializable & serializable)
   {
      serializable.write(*this);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (const char * psz)
   {
      write(psz, strlen(psz));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (const id & id)
   {

      operator << (id.m_chType);

      if(id.m_chType == IDTYPE_TYPE_TEXT)
      {
         *this << *id.m_pstr;
      }
      else if(id.m_chType == IDTYPE_TYPE_NUMBER)
      {
         operator << (id.m_i);
      }

      return *this;

   }

   byte_output_stream & byte_output_stream::operator << (const var & var)
   {
      ((::var *)&var)->write(*this);
      return *this;
   }

   string byte_output_stream::get_location() const
   {
      return "<unknown byte_output_stream location>";
   }

   byte_output_stream & byte_output_stream::operator = (const byte_output_stream & ostream)
   {
      writer::operator = (ostream);
      return *this;
   }













   byte_stream::byte_stream()
   {
   }

   byte_stream::byte_stream(const filesp & filesp)
   {
      if(filesp.is_set())
      {
         m_spreader = filesp.m_p;
         m_spwriter = filesp.m_p;
      }
   }

   byte_stream::byte_stream(reader * preader, writer * pwriter) :
      stream(preader, pwriter),
      byte_input_stream(preader),
      byte_output_stream(pwriter)
   {
   }

   byte_stream::byte_stream(const byte_stream & stream) :
      ::ex1::stream(stream),
      byte_input_stream(stream),
      byte_output_stream(stream)
   {
   }

   byte_stream::~byte_stream()
   {
   }

   string byte_stream::get_location() const
   {
      return "<unknown byte_io_stream location>";
   }

   byte_stream & byte_stream::operator = (const byte_stream & stream)
   {
      if(this != &stream)
      {
         m_spreader = stream.m_spreader;
         m_spwriter = stream.m_spwriter;
      }
      return *this;
   }

   static const ::primitive::memory_size kBlockSize = ((uint32)1 << 31);

   HRESULT ReadStream(::ex1::reader * stream, void * data, ::primitive::memory_size * processedSize)
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

   HRESULT ReadStream_FALSE(reader * stream, void * data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : S_FALSE;
   }

   HRESULT ReadStream_FAIL(reader * stream, void * data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : E_FAIL;
   }

   HRESULT WriteStream(writer * stream, const void * data, ::primitive::memory_size size)
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
