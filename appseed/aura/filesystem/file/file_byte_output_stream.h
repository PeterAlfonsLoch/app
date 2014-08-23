#pragma once




namespace file
{


   class exception;         // file exception
   class file;
   typedef sp(binary_buffer) binary_buffer_sp;

   class byte_output_stream;
   class input_stream;
   class serializable;



   class CLASS_DECL_AXIS byte_output_stream :
      virtual public output_stream
   {
   public:


      bool        m_b64bit;


      byte_output_stream();
      byte_output_stream(stream_buffer * pwriter);
      byte_output_stream(const output_stream & ostream);
      virtual ~byte_output_stream();


      void write_arbitrary(int32_t i);
      void write_arbitrary(uint32_t ui);
      void write_arbitrary(int64_t i);
      void write_arbitrary(uint64_t ui);
      void write_arbitrary(uint64_t ui, int signal);

      using output_stream::write;
      virtual void write (char ch);
      virtual void write (uchar uch);
      virtual void write (int16_t sh);
      virtual void write (uint16_t uint16_t);
      virtual void write (wchar_t wch);
      virtual void write (bool b);
      virtual void write (int32_t i);
      virtual void write (uint32_t ui);
      virtual void write (int64_t i);
      virtual void write (uint64_t ui);
      virtual void write (float f);
      virtual void write (double d);
      virtual void write (const RECT & rect);
      virtual void write (LPCRECT lpcrect);
      virtual void write (SIZE & size);
      virtual void write (sp(type) info);
      virtual void write (serializable & serializable);
      virtual void write (const char * psz);
      virtual void write (const id & id);
      virtual void write (const var & var);
      virtual void write (const string & str);

      virtual string get_location() const;

      output_stream & operator = (const output_stream & ostream);

      virtual void write_from_hex(const char * psz);


   };



} // namespace file




