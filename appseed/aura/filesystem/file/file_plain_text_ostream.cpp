//#include "framework.h"


namespace file
{


   plain_text_ostream::plain_text_ostream()
   {
	   m_spbuffer = canew(string_buffer);
   }

   plain_text_ostream::plain_text_ostream(stream_buffer * pwriter)
   {
	   m_spbuffer = pwriter;
   }

   plain_text_ostream::plain_text_ostream(const ostream & ostream)
   {
	   m_spbuffer = ostream.m_spbuffer;
   }

   plain_text_ostream::~plain_text_ostream()
   {

   }

   void plain_text_ostream:: write (bool b)
   {
      if(b)
         raw_print("true");
      else
         raw_print("false");
   }

   void plain_text_ostream:: write (char ch)
   {
      m_spbuffer->write(&ch, sizeof(ch)); // treat as char - character
      
   }

   void plain_text_ostream:: write (uchar uch)
   {
      write ((uint32_t) uch);
   }

   void plain_text_ostream:: write (int16_t i)
   {
      write ((int32_t) i);
   }

   void plain_text_ostream:: write (uint16_t ui)
   {
      write ((uint32_t) ui);
   }

   void plain_text_ostream:: write (char16_t wch)
   {
      raw_print(::str::uni_to_utf8(wch));
   }


   void plain_text_ostream:: write (int32_t i)
   {
      raw_print(::str::from(i));
   }

   void plain_text_ostream:: write (uint32_t ui)
   {
      raw_print(::str::from(ui));
   }

   void plain_text_ostream:: write (int64_t i)
   {
      raw_print(::str::from(i));
   }

   void plain_text_ostream:: write (uint64_t ui)
   {
      raw_print(::str::from(ui));
   }

   void plain_text_ostream:: write (float f)
   {
      string str;
      str.Format("%f", f);
      raw_print(str);
      
   }

   void plain_text_ostream:: write (double d)
   {
      string str;
      str.Format("%f", d);
      raw_print(str);
      
   }

   void plain_text_ostream:: write (const RECT & rect)
   {
       write (rect.left);
       write (rect.top);
       write (rect.right);
       write (rect.bottom);
      
   }

   void plain_text_ostream:: write(LPCRECT lpcrect)
   {
      write(*lpcrect);
   }


   void plain_text_ostream:: write (const SIZE & size)
   {
       write (size.cx);
       write (size.cy);
      
   }

   void plain_text_ostream:: write (const sp(type) info)
   {

      raw_print(info->name());
      raw_print(info->friendly_name());

      
   }

   void plain_text_ostream:: write (serializable & serializable)
   {
      serializable.write(*this);
      
   }

   void plain_text_ostream:: write (const char * psz)
   {
      m_spbuffer->write(psz, strlen(psz));
      
   }

   string plain_text_ostream::get_location() const
   {
      return "<unknown plain_text_ostream location>";
   }

   void plain_text_ostream::raw_print(const string & str)
   {
      m_spbuffer->write(str.c_str(), str.size());
      
   }

   ostream & plain_text_ostream::operator = (const ostream & ostream)
   {

      return ostream::operator = (ostream);
      
   }


} // namespace core



