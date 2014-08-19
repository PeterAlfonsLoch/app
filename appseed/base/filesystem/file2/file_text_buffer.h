#pragma once


namespace file
{


   class CLASS_DECL_BASE text_buffer :
      virtual public ::file::stream_buffer
   {
   public:


      text_buffer();
      virtual ~text_buffer();


      virtual void write_string(const char * lpsz);
      virtual bool read_string(string & str);
      virtual UINT read_full_string(string & str);

      inline text_buffer & operator << (const char * lpsz)
      {
         write_string(lpsz);
         return *this;
      }


   };


   typedef smart_pointer < text_buffer > text_buffer_sp;


} // namespace file




