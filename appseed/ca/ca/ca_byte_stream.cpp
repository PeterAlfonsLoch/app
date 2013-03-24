#include "framework.h"




namespace ca
{


   int get_arbitrary_length(uint64_t ui);



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

   byte_input_stream & byte_input_stream::operator >> (uchar & uch)
   {
      read(&uch, sizeof(uch));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (int16_t & i)
   {

      read_arbitrary(&i, sizeof(i));

      return *this;

   }

   byte_input_stream & byte_input_stream::operator >> (uint16_t & ui)
   {
      read_arbitrary(&ui, sizeof(ui));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (wchar_t & wch)
   {
      read_arbitrary(&wch, sizeof(wch));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (bool & b)
   {
      read(&b, sizeof(b));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (int32_t & i)
   {
      read_arbitrary(&i, sizeof(i));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (uint32_t & ui)
   {
      read_arbitrary(&ui, sizeof(ui));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (int64_t & i)
   {
      read_arbitrary(&i, sizeof(i));
      return *this;
   }

   byte_input_stream & byte_input_stream::operator >> (uint64_t & ui)
   {
      read_arbitrary(&ui, sizeof(ui));
      return *this;
   }

   void byte_input_stream::read_arbitrary(int32_t & i)
   {

      read_arbitrary(&i, sizeof(i));

   }

   void byte_input_stream::read_arbitrary(uint32_t & ui)
   {

      read_arbitrary(&ui, sizeof(ui));

   }

   void byte_input_stream::read_arbitrary(int64_t & i)
   {

      read_arbitrary(&i, sizeof(i));

   }

   void byte_input_stream::read_arbitrary(uint64_t & ui)
   {

      read_arbitrary(&ui, sizeof(ui));

   }

   void byte_input_stream::read_arbitrary(void * p, count nMax)
   {

      byte b;

      if(read(&b, sizeof(b)) < sizeof(b))
         throw io_exception(get_app(), "ca::byte_input_stream::read_arbitrary : unexpected end of stream, cannot read header byte");

      if(b == 0)
      {
         memset(p, 0, nMax);
         return;
      }

      uint64_t uiRead = 0;

      int len = b & 0x3f;

      if(len > sizeof(uiRead) || len > nMax)
         throw io_exception(get_app(), "ca::byte_input_stream::read_arbitrary : overflow");

      if(read(&uiRead, len) != len)
         throw io_exception(get_app(), "ca::byte_input_stream::read_arbitrary : unexpected end of stream, cannot read number body");

      if(b & 0x40)
      {
         int64_t i = - ((int64_t) uiRead);
         memcpy(p, &i, nMax);
      }
      else
      {
         memcpy(p, &uiRead, nMax);
      }

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
      {
         int32_t iLen;
         read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         read(psz, iLen);
         psz[iLen] = '\0';
         info.m_id = psz;
         free((void *) psz);
      }
      {
         int32_t iLen;
         read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         read(psz, iLen);
         psz[iLen] = '\0';
         info.m_idFriendly = psz;
         free((void *) psz);
      }
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

   byte_output_stream & byte_output_stream::operator << (bool b)
   {
      write(&b, sizeof(b));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (char ch)
   {
      write(&ch, sizeof(ch));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (uchar uch)
   {
      write(&uch, sizeof(uch));
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (int16_t i)
   {
      write_arbitrary(i);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (uint16_t ui)
   {
      write_arbitrary(ui);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (wchar_t wch)
   {
      write_arbitrary(wch);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (int32_t i)
   {
      write_arbitrary(i);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (uint32_t ui)
   {
      write_arbitrary(ui);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (int64_t i)
   {
      write_arbitrary(i);
      return *this;
   }

   byte_output_stream & byte_output_stream::operator << (uint64_t ui)
   {
      write_arbitrary(ui);
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

   int get_arbitrary_length(uint64_t ui)
   {

      if(ui == 0)
      {
         return 0;
      }
      else if(ui < (1UL << 8))
      {
         return 1;
      }
      else if(ui < (1UL << 16))
      {
         return 2;
      }
      else if(ui < (1UL << 24))
      {
         return 3;
      }
      else if(ui < (1ULL << 32))
      {
         return 4;
      }
      else if(ui < (1ULL << 40))
      {
         return 5;
      }
      else if(ui < (1ULL << 48))
      {
         return 6;
      }
      else if(ui < (1ULL << 56))
      {
         return 7;
      }
      else
      {
         return 8;
      }

   }

   void byte_output_stream::write_arbitrary(uint64_t ui, int signal)
   {

      // 0 bit is 0 for 0 version

      // 0 version first byte reserved
      // 1 bit is signal
      // 2-7 bit length in bytes of the arbitrary always positive integer signal by signal bit above

      if(signal != 0)
         signal = 1;

      int len = get_arbitrary_length(ui);

      byte b = (signal << 6) | (len & 0x3f);

      write(&b, sizeof(b));

      write(&ui, len);

   }

   void byte_output_stream::write_arbitrary(int64_t i)
   {

      if(i < 0)
      {
         write_arbitrary(-i, 1);
      }
      else
      {
         write_arbitrary(i, 0);
      }

   }

   void byte_output_stream::write_arbitrary(uint64_t ui)
   {

      write_arbitrary(ui, 0);

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
      iLen = strlen(info.friendly_name());
      write(&iLen, sizeof(iLen));
      write(info.friendly_name(), iLen);
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
      ::ca::stream(stream),
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

   static const ::primitive::memory_size kBlockSize = ((uint32_t)1 << 31);

   HRESULT ReadStream(::ca::reader * stream, void * data, ::primitive::memory_size * processedSize)
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





} // namespace ca
