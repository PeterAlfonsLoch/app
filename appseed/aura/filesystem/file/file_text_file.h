#pragma once


namespace file
{


   class CLASS_DECL_AURA text_file :
      virtual public ::file::file
   {
   public:


      text_file();
      virtual ~text_file();


      virtual void write_string(const char * lpsz);
      virtual bool read_string(string & str);
      virtual UINT read_full_string(string & str);

      inline text_file & operator << (const char * lpsz)
      {
         write_string(lpsz);
         return *this;
      }


   };


   typedef smart_pointer < text_file > text_buffer_sp;


} // namespace file




