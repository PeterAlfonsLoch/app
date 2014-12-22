#include "framework.h"


namespace http
{

   output_stream::output_stream()
   {
   
   }

   output_stream::output_stream(::file::stream_buffer * pbuffer) :
      ::file::plain_text_output_stream(pbuffer)
   {
   
   
   }

   output_stream::~output_stream()
   {
      close();
   }


   /*void output_stream::write(const char * lpcsz)
   {

      write(lpcsz, strlen(lpcsz));

      return *this;

   }*/

   void output_stream::write (const string & str)
   {

      write((const char *) str, str.get_length());

   }


   ::file::output_stream & output_stream::operator << (::file::memory_buffer & memfile)
   {

      write(memfile.get_data(), (::primitive::memory_size) memfile.get_length());

      return *this;

   }





   /*bool output_stream::read_string(string & str)
   {
      uint_ptr nRead;
      char ch;
      bool bR = false;
      str.Empty();
      while((nRead = read(&ch, sizeof(ch))) > 0)
      {
         str += ch;
         if(bR)
         {
            if(ch == '\n')
            {
               break;
            }
            else
            {
               seek(-1, ::file::seek_current);
            }
         }
         else if(ch == '\r')
         {
            bR = true;
         }
         else if(ch == '\n')
         {
            break;
         }
      }
      return str.has_char();
   }*/

   ::file::output_stream & output_stream::operator << (::file::buffer_sp spbuf)
   {
      uint_ptr nRead;
      primitive::memory mem;
      if(!mem.allocate(1024 * 1024))
      {
         throw memory_exception(get_app());
      }
      while((nRead = spbuf->read(mem.get_data(), mem.get_size())) > 0)
      {
         write(mem.get_data(), nRead);
      }
      return *this;
   }


/*    void output_stream::to_string(string & str);
      {

         read(str.GetBufferSetLength((int32_t)get_length()), (int32_t)(get_length()));

         str.ReleaseBuffer();

      }*/

} // namespace http
