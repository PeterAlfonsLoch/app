#pragma once

namespace ca2
{

   class CLASS_DECL_ca2 text_file : 
      virtual public ::file::file
   {
   public:
      text_file();
      virtual ~text_file();

      virtual void write_string(const char * lpsz);
      virtual UINT read_string(string & str);
      virtual UINT read_full_string(string & str);

      inline text_file & operator << (const char * lpsz)
      {
         write_string(lpsz);
         return *this;
      }
   };

   typedef smart_pointer < text_file > text_file_sp;

} // namespace ca2
