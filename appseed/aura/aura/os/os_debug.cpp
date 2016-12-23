#include "framework.h"


char os_trace_level_char(e_level elevel)
{

   switch (elevel)
   {
   case level_error:
      return 'E';
   case level_warning:
      return 'W';
   case level_info:
      return 'I';
   default:
      return 'D';
   }

}

void os_trace(e_level elevel, const char * pszTag, const char * psz)
{

   string strMessage;

   string strTag;

   strTag = strTag.Left(23);

   strTag = string(' ', MAX(0, 23 - strTag.get_length()));

   strMessage.Format("-%c- %s %s\n", os_trace_level_char(elevel), strTag, psz);

   output_debug_string(strMessage);

}


void simple_debug_print(const char * psz)
{

   os_trace(level_debug, "simple_debug_string", psz);

}