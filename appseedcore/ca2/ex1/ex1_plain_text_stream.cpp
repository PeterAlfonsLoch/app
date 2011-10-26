#include "StdAfx.h"


namespace ex1
{


   plain_text_stream_base::plain_text_stream_base()
   {
      m_fmtflags = nofmtflags;
   }

   plain_text_stream_base::~plain_text_stream_base()
   {
   }

   plain_text_stream_base::fmtflags plain_text_stream_base::setf(fmtflags flagsAdd)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) ((uint) m_fmtflags | (uint) flagsAdd);

      return fmtflagsOld;

   }

   plain_text_stream_base::fmtflags plain_text_stream_base::setf(fmtflags flagsAdd, fmtflags flagsRemove)
   {
      
      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) (((uint) m_fmtflags | (uint) flagsAdd) & (~(uint)flagsRemove));

      return fmtflagsOld;

   }


   iostate plain_text_stream_base::rdstate() const
   {
      return m_iostate;
   }

   void plain_text_stream_base::setstate(iostate state)
   {
      clear(rdstate() | state);
   }

   void plain_text_stream_base::clear(iostate state)
   {
      m_iostate = state;
   }

   bool plain_text_stream_base::bad() const
   {
      return (m_iostate & badbit) != 0;
   }

   bool plain_text_stream_base::fail() const
   {
      return (m_iostate & badbit) || ( m_iostate & failbit);
   }

   bool plain_text_stream_base::eof() const
   {
      return m_iostate & eofbit;
   }

   bool plain_text_stream_base::good() const
   {
      return m_iostate == goodbit;
   }


   plain_text_input_stream::plain_text_input_stream()
   {
   }

   plain_text_input_stream::plain_text_input_stream(reader * preader) :
      reader(preader)
   {
      
   }

   plain_text_input_stream::plain_text_input_stream(const plain_text_input_stream & istream) :
      reader(istream)
   {
      
   }

   plain_text_input_stream::~plain_text_input_stream()
   {

   }

   plain_text_input_stream & plain_text_input_stream::operator >> (char & ch)
   {
      read(&ch, sizeof(ch));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (unsigned char & uch)
   {
      read(&uch, sizeof(uch));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (short & sh)
   {
      read(&sh, sizeof(sh));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (unsigned short & ush)
   {
      read(&ush, sizeof(ush));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (wchar_t & wch)
   {
      read(&wch, sizeof(wch));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (bool & b)
   {
      read(&b, sizeof(b));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (int & i)
   {
      uint64_t uiRead = read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         throw "failed to read int";
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (unsigned int & ui)
   {
      uint64_t uiRead = read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         throw "failed to read unsigned int";
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (long & l)
   {
      uint64_t uiRead = read(&l, sizeof(l));
      if(uiRead != sizeof(l))
         throw "failed to read long";
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (unsigned long & ul)
   {
      read(&ul, sizeof(ul));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (__int64 & i)
   {
      read(&i, sizeof(i));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (uint64_t & ui)
   {
      read(&ui, sizeof(ui));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (float & f)
   {
      read(&f, sizeof(f));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (double & d)
   {
      read(&d, sizeof(d));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (LPRECT lprect)
   {
      read(&lprect->left,     sizeof(lprect->left));
      read(&lprect->top,      sizeof(lprect->top));
      read(&lprect->right,    sizeof(lprect->right));
      read(&lprect->bottom,   sizeof(lprect->bottom));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (SIZE & size)
   {
      read(&size.cx,     sizeof(size.cx));
      read(&size.cy,      sizeof(size.cy));
      return *this;
   }

   plain_text_input_stream & plain_text_input_stream::operator >> (::ca::type_info & info)
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


   plain_text_input_stream & plain_text_input_stream::operator >> (plain_text_serializable & serializable)
   {
      serializable.read(*this);
      return *this;
   }


   string plain_text_input_stream::get_location() const
   {
      return "<unknown plain_text_input_stream location>";
   }

   plain_text_input_stream & plain_text_input_stream::operator = (const plain_text_input_stream & istream)
   {
      reader::operator = (istream);
      return *this;
   }







   plain_text_output_stream::plain_text_output_stream()
   {
   }

   plain_text_output_stream::plain_text_output_stream(writer * pwriter) :
      writer(pwriter)
   {
   }

   plain_text_output_stream::plain_text_output_stream(const plain_text_output_stream & ostream) :
      writer(ostream)
   {
   }

   plain_text_output_stream::~plain_text_output_stream()
   {

   }

   plain_text_output_stream & plain_text_output_stream::operator << (char ch)
   {
      write(&ch, sizeof(ch));
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (unsigned char uch)
   {
      return operator << ((unsigned int) uch);
   }

   plain_text_output_stream & plain_text_output_stream::operator << (short sh)
   {
      return operator << ((int) sh);
   }

   plain_text_output_stream & plain_text_output_stream::operator << (unsigned short ush)
   {
      return operator << ((unsigned int) ush);
   }

   plain_text_output_stream & plain_text_output_stream::operator << (wchar_t wch)
   {
      return raw_print(gen::str::uni_to_utf8(wch));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (bool b)
   {
      if(b)
         return raw_print("true");
      else
         return raw_print("false");
   }

   plain_text_output_stream & plain_text_output_stream::operator << (int i)
   {
      return raw_print(gen::str::itoa(i));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (unsigned int ui)
   {
      return raw_print(gen::str::itoa(ui));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (long l)
   {
      return raw_print(gen::str::itoa(l));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (__int64 i)
   {
      return raw_print(gen::str::i64toa(i));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (unsigned long ul)
   {
      return raw_print(gen::str::itoa(ul));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (uint64_t ui)
   {
      return raw_print(gen::str::i64toa(ui));
   }

   plain_text_output_stream & plain_text_output_stream::operator << (float f)
   {
      string str;
      str.Format("%f", f);
      raw_print(str);
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (double d)
   {
      string str;
      str.Format("%f", d);
      raw_print(str);
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (LPCRECT lpcrect)
   {
      operator << (lpcrect->left);
      operator << (lpcrect->top);
      operator << (lpcrect->right);
      operator << (lpcrect->bottom);
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (SIZE & size)
   {
      operator << (size.cx);
      operator << (size.cy);
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (::ca::type_info & info)
   {
      return raw_print(info.raw_name());
   }

   plain_text_output_stream & plain_text_output_stream::operator << (plain_text_serializable & serializable)
   {
      serializable.write(*this);
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator << (const char * psz)
   {
      write(psz, strlen(psz));
      return *this;
   }

   string plain_text_output_stream::get_location() const
   {
      return "<unknown plain_text_output_stream location>";
   }

   plain_text_output_stream & plain_text_output_stream::raw_print(const string & str)
   {
      write(str.c_str(), str.size());
      return *this;
   }

   plain_text_output_stream & plain_text_output_stream::operator = (const plain_text_output_stream & ostream)
   {
      writer::operator = (ostream);
      return *this;
   }


















   plain_text_stream::plain_text_stream()
   {
   }

   plain_text_stream::plain_text_stream(const filesp & filesp) :
      stream(*filesp.m_p)
   {
   }

   plain_text_stream::plain_text_stream(reader * preader, writer * pwriter) :
      stream(preader, pwriter),
      plain_text_input_stream(preader),
      plain_text_output_stream(pwriter)
   {
   }

   plain_text_stream::plain_text_stream(const plain_text_stream & stream) :
      stream(stream),
      plain_text_input_stream(stream),
      plain_text_output_stream(stream)
   {
   }

   plain_text_stream::~plain_text_stream()
   {
   }

   plain_text_stream & plain_text_stream::operator = (const plain_text_stream & stream)
   {
      if(this != &stream)
      {
         m_spreader = stream.m_spreader;
         m_spwriter = stream.m_spwriter;
      }
      return *this;
   }


   string plain_text_stream::get_location() const
   {
      return "<unknown plain_text_io_stream location>";
   }

   /*static const uint32 kBlockSize = ((uint32)1 << 31);

   HRESULT ReadStream(reader * stream, void * data, uint64_t * processedSize)
   {
      uint64_t size = *processedSize;
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

   HRESULT ReadStream_FALSE(reader * stream, void *data, uint64_t size)
   {
      uint64_t processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : S_FALSE;
   }

   HRESULT ReadStream_FAIL(reader * stream, void * data, uint64_t size)
   {
      uint64_t processedSize = size;
      RINOK(ReadStream(stream, data, &processedSize));
      return (size == processedSize) ? S_OK : E_FAIL;
   }

   HRESULT WriteStream(writer * stream, const void *data, uint64_t size)
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

   */
} // namespace ex1

