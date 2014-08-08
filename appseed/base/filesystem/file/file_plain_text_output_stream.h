#pragma once


namespace file
{


   class CLASS_DECL_BASE plain_text_output_stream :
      virtual public output_stream,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_output_stream();
      plain_text_output_stream(stream_buffer * pwriter);
      plain_text_output_stream(const output_stream & ostream);
      virtual ~plain_text_output_stream();

      using output_stream::write;
      virtual void write (bool b);
      virtual void write (char ch);
      virtual void write (uchar uch);
      virtual void write (wchar_t wch);
      virtual void write (int16_t sh);
      virtual void write (uint16_t uint16_t);
      virtual void write (int32_t i);
      virtual void write (uint32_t ui);
      virtual void write (int64_t i);
      virtual void write (uint64_t ui);
      virtual void write (float f);
      virtual void write (double d);
      virtual void write (const RECT & rect);
      virtual void write (SIZE & size);
      virtual void write (sp(type) info);
      virtual void write (serializable & serializable);
      virtual void write (const char * psz);

      virtual void raw_print(const string & str);

      virtual ::string get_location() const;

      output_stream & operator = (const output_stream & ostream);

      operator void * ()
      {
         return this;
      }

      

   };


} // namespace file


