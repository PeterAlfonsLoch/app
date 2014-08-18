#include "framework.h"


/*void sprint_hex(char * sz, int32_t iValue)
{
int32_t i = 8;
sz[i] = '\0';
i--;
for(; i >= 0; i--)
{
sz[i] = hex::from((iValue >> (4 * (7 - i))) &  0xf);
}
}
*/


bool file_put_contents_dup(const char * path,const ::primitive::memory_base & memory)
{

   return file_put_contents_dup(path,(const char *)memory.get_data(),memory.get_size()) != false;

}









string file_title_dup(const char * path)
{
   string str(path);
   size_t iPos;
   size_t iPos1 = str.reverse_find('\\');
   size_t iPos2 = str.reverse_find('/');
   if(iPos1 != -1 && iPos2 != -1)
   {
      if(iPos1 > iPos2)
      {
         iPos = iPos1 + 1;
      }
      else
      {
         iPos = iPos2 + 1;
      }
   }
   else if(iPos1 != -1)
   {
      iPos = iPos1 + 1;
   }
   else if(iPos2 != -1)
   {
      iPos = iPos2 + 1;
   }
   else
   {
      iPos = 0;
   }
   return str.substr(iPos);
}


string file_name_dup(const char * path)
{
   string str = file_title_dup(path);
   size_t iPos = str.find('.');
   if(iPos != -1)
   {
      return str.substr(0,iPos);
   }
   else
   {
      return str;
   }
}



