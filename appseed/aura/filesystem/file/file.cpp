#include "framework.h"


string file_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.reverse_find('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}
