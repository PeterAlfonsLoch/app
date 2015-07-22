//#include "framework.h"




namespace file
{


   int get_arbitrary_length(uint64_t ui);




   // string serialization code
   // string format:
   //      UNICODE strings are always prefixed by 0xff, 0xfffe
   //      if < 0xff chars: len:BYTE, char chars
   //      if >= 0xff characters: 0xff, len:WORD, char chars
   //      if >= 0xfffe characters: 0xff, 0xffff, len:uint32_t, TCHARs

   void byte_ostream:: write (const string & string)
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





   byte_ostream::byte_ostream()
   {
      m_b64bit = false;
   }

   byte_ostream::byte_ostream(stream_buffer * pwriter) :
      ostream(pwriter)
   {
      m_b64bit = false;
   }

   byte_ostream::byte_ostream(const  ostream & os) :
      ostream(os)
   {
      m_b64bit = false;
   }

   byte_ostream::~byte_ostream()
   {

   }

   void byte_ostream:: write (bool b)
   {

      m_spbuffer->write(&b, sizeof(b));

   }

   void byte_ostream:: write (char ch)
   {

      m_spbuffer->write(&ch, sizeof(ch));

   }

   void byte_ostream:: write (uchar uch)
   {

      m_spbuffer->write(&uch, sizeof(uch));

   }

   void byte_ostream:: write (int16_t i)
   {
      write_arbitrary(i);

   }

   void byte_ostream:: write (uint16_t ui)
   {
      write_arbitrary(ui);

   }
#ifdef WINDOWS
   void byte_ostream:: write (unichar wch)
   {
      write_arbitrary(wch);

   }
#endif
   void byte_ostream:: write (int32_t i)
   {
      write_arbitrary(i);

   }

   void byte_ostream:: write (uint32_t ui)
   {
      write_arbitrary(ui);

   }

   void byte_ostream:: write (int64_t i)
   {
      write_arbitrary(i);

   }

   void byte_ostream:: write (uint64_t ui)
   {
      write_arbitrary(ui);

   }



   void byte_ostream::write_arbitrary(int32_t i)
   {

      write_arbitrary((int64_t) i);

   }

   void byte_ostream::write_arbitrary(uint32_t ui)
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

   void byte_ostream::write_arbitrary(uint64_t ui, int signal)
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

   void byte_ostream::write_arbitrary(int64_t i)
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

   void byte_ostream::write_arbitrary(uint64_t ui)
   {

      write_arbitrary(ui, 0);

   }

   void byte_ostream:: write (float f)
   {
      m_spbuffer->write(&f, sizeof(f));

   }

   void byte_ostream:: write (double d)
   {
      m_spbuffer->write(&d, sizeof(d));

   }

   void byte_ostream:: write (const RECT & rect)
   {
      m_spbuffer->write(&rect.left,     sizeof(rect.left));
      m_spbuffer->write(&rect.top,      sizeof(rect.top));
      m_spbuffer->write(&rect.right,    sizeof(rect.right));
      m_spbuffer->write(&rect.bottom,   sizeof(rect.bottom));

   }

   void byte_ostream:: write(LPCRECT lpcrect)
   {

      write(*lpcrect);

   }

   void byte_ostream:: write (const SIZE & size)
   {
      m_spbuffer->write(&size.cx,     sizeof(size.cx));
      m_spbuffer->write(&size.cy,     sizeof(size.cy));

   }

   void byte_ostream:: write (const sp(type) info)
   {
      strsize iLen = strlen(info->name());
      m_spbuffer->write(&iLen, sizeof(iLen));
      m_spbuffer->write(info->name(), iLen);
      iLen = strlen(info->friendly_name());
      m_spbuffer->write(&iLen, sizeof(iLen));
      m_spbuffer->write(info->friendly_name(), iLen);

   }

   void byte_ostream:: write (serializable & serializable)
   {
      serializable.write(*this);

   }

   void byte_ostream:: write (const char * psz)
   {

      m_spbuffer->write(psz, strlen(psz));

   }

   void byte_ostream:: write (const id & id)
   {


      bool bNull = id.is_null();

      operator << (bNull);

      if(!bNull)
      {
         string str = id.m_psz;
         *this << str;
      }



   }


   void byte_ostream:: write (const var & var)
   {

      ((::var *)&var)->write(*this);

   }

   void byte_ostream:: write(const property & property)
   {

      ((::property *)&property)->write(*this);

   }


   string byte_ostream::get_location() const
   {

      return "<unknown byte_ostream location>";

   }


   ostream & byte_ostream::operator = (const ostream & ostream)
   {

      return ::file::ostream::operator = (ostream);

   }



   void byte_ostream::write_from_hex(const char * psz, strsize iLen)
   {

      //primitive::memory memory(get_app());

      //memory.from_hex(psz);

      //write(memory.get_data(), memory.get_size());

      ::file::ostream::write_from_hex(psz,iLen < 0 ? strlen(psz) + iLen + 1 : iLen);

   }


   void byte_ostream::write_from_hex(const string & str)
   {

      ::file::ostream::write_from_hex(str,str.get_length());

   }











} // namespace file




