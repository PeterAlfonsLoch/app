#pragma once

namespace file
{

   class string_file;


   typedef sp(string_file) string_file_sp;



   class CLASS_DECL_AURA plain_text_ostream :
      virtual public ostream,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_ostream();
      plain_text_ostream(file * pwriter);
      plain_text_ostream(const ostream & ostream);
      virtual ~plain_text_ostream();

      using ostream::write;
      virtual void write (bool b);
      virtual void write (char ch);
      virtual void write (uchar uch);
#ifdef WINDOWS
      virtual void write (unichar wch);
#endif
      virtual void write (int16_t sh);
      virtual void write (uint16_t ui);
      virtual void write (int32_t i);
      virtual void write (uint32_t ui);
      virtual void write (int64_t i);
      virtual void write (uint64_t ui);
      virtual void write (float f);
      virtual void write (double d);
      virtual void write (const RECT & rect);
      virtual void write (LPCRECT lpcrect);
      virtual void write (const SIZE & size);
      virtual void write (const sp(type) info);
      virtual void write (const std_type_info & info);
      virtual void write (serializable & serializable);
      virtual void write (const char * psz);

      virtual void raw_print(const string & str);
      virtual void print_number(const string & str);

      virtual ::string get_location() const;

      ostream & operator = (const ostream & ostream);

      operator void * ()
      {
         return this;
      }

      

   };


} // namespace file


class CLASS_DECL_AURA plain_text_stream_log_line :
   virtual public ::file::plain_text_ostream
{
public:

   
   ::file::string_file_sp   m_pfile;
   e_level                    m_elevel;
   string                     m_strTag;
   string                     m_strFile;
   int                        m_iLine;


   plain_text_stream_log_line(e_level elevel, const char * pszTag, const char * pszFile = NULL, int iLine = -1);
   virtual ~plain_text_stream_log_line();

};





