#include "framework.h"

namespace http
{

   bool file::read_string(string & str)
   {
      dword_ptr nRead;
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
               seek(-1, ::ex1::seek_current);
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
   }

   inline file & file::operator << (ex1::file & file)
      {
         dword_ptr nRead;
         primitive::memory mem;
         if(!mem.allocate(1024 * 1024))
         {
            throw memory_exception(get_app());
         }
         while((nRead = file.read(mem.get_data(), mem.get_size())) > 0)
         {
            write(mem.get_data(), nRead);
         }
         return *this;
      }

} // namespace http
