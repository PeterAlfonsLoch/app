#include "framework.h"




namespace file
{


   int get_arbitrary_length(uint64_t ui);




   // string serialization code
   // string format:
   //      UNICODE strings are always prefixed by 0xff, 0xfffe
   //      if < 0xff chars: len:BYTE, char chars
   //      if >= 0xff characters: 0xff, len:WORD, char chars
   //      if >= 0xfffe characters: 0xff, 0xffff, len:uint32_t, TCHARs

   void byte_output_stream:: write (const string & string)
   {
      if (string.get_length() < 255)
      {
         *this << (byte)         string.get_length();
      }
      else if (string.get_length() < 0xfffe)
      {
         *this << (byte)         0xff;
         *this << (uint16_t)     string.get_length();
      }
      else
      {
         *this << (byte)         0xff;
         *this << (uint16_t)     0xffff;
         *this << (uint32_t)     string.get_length();
      }

      m_spbuffer->write((const char *) string, string.get_length());

   }





   byte_output_stream::byte_output_stream()
   {
      m_b64bit = false;
   }

   byte_output_stream::byte_output_stream(stream_buffer * pwriter) :
      output_stream(pwriter)
   {
      m_b64bit = false;
   }

   byte_output_stream::byte_output_stream(const  output_stream & ostream) :
      output_stream(ostream)
   {
      m_b64bit = false;
   }

   byte_output_stream::~byte_output_stream()
   {

   }

   void byte_output_stream:: write (bool b)
   {
      
      m_spbuffer->write(&b, sizeof(b));

   }

   void byte_output_stream:: write (char ch)
   {
      
      m_spbuffer->write(&ch, sizeof(ch));

   }

   void byte_output_stream:: write (uchar uch)
   {
      
      m_spbuffer->write(&uch, sizeof(uch));

   }

   void byte_output_stream:: write (int16_t i)
   {
      write_arbitrary(i);

   }

   void byte_output_stream:: write (uint16_t ui)
   {
      write_arbitrary(ui);

   }

   void byte_output_stream:: write (wchar_t wch)
   {
      write_arbitrary(wch);

   }

   void byte_output_stream:: write (int32_t i)
   {
      write_arbitrary(i);

   }

   void byte_output_stream:: write (uint32_t ui)
   {
      write_arbitrary(ui);

   }

   void byte_output_stream:: write (int64_t i)
   {
      write_arbitrary(i);

   }

   void byte_output_stream:: write (uint64_t ui)
   {
      write_arbitrary(ui);

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

      m_spbuffer->write(&b, sizeof(b));

      m_spbuffer->write(&ui, len);

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

   void byte_output_stream:: write (float f)
   {
      m_spbuffer->write(&f, sizeof(f));

   }

   void byte_output_stream:: write (double d)
   {
      m_spbuffer->write(&d, sizeof(d));

   }

   void byte_output_stream:: write (const RECT & rect)
   {
      m_spbuffer->write(&rect.left,     sizeof(rect.left));
      m_spbuffer->write(&rect.top,      sizeof(rect.top));
      m_spbuffer->write(&rect.right,    sizeof(rect.right));
      m_spbuffer->write(&rect.bottom,   sizeof(rect.bottom));

   }

   void byte_output_stream:: write(LPCRECT lpcrect)
   {

      write(*lpcrect);

   }

   void byte_output_stream:: write (SIZE & size)
   {
      m_spbuffer->write(&size.cx,     sizeof(size.cx));
      m_spbuffer->write(&size.cy,     sizeof(size.cy));

   }

   void byte_output_stream:: write (sp(type) info)
   {
      strsize iLen = strlen(info->name());
      m_spbuffer->write(&iLen, sizeof(iLen));
      m_spbuffer->write(info->name(), iLen);
      iLen = strlen(info->friendly_name());
      m_spbuffer->write(&iLen, sizeof(iLen));
      m_spbuffer->write(info->friendly_name(), iLen);

   }

   void byte_output_stream:: write (serializable & serializable)
   {
      serializable.write(*this);

   }

   void byte_output_stream:: write (const char * psz)
   {
      
      m_spbuffer->write(psz, strlen(psz));

   }

   void byte_output_stream:: write (const id & id)
   {


      bool bNull = id.is_null();

      operator << (bNull);

      if(!bNull)
      {
         *this << *id.m_pstr;
      }



   }

   void byte_output_stream:: write (const var & var)
   {
      ((::var *)&var)->write(*this);

   }

   string byte_output_stream::get_location() const
   {

      return "<unknown byte_output_stream location>";

   }

   
   output_stream & byte_output_stream::operator = (const output_stream & ostream)
   {

      return ::file::output_stream::operator = (ostream);

   }
   


   void byte_output_stream::write_from_hex(const char * psz)
   {

      primitive::memory memory(get_app());

      memory.from_hex(psz);

      write(memory.get_data(), memory.get_size());

   }













} // namespace file




