#include "framework.h"

namespace ca2
{

   string xml::special_chars(const char * psz)
   {
      string str(psz);
      str.replace("&"      , "&amp;");
      str.replace("\""     , "&quot;"); // quando ENT_NOQUOTES n縊 est・definida.
      str.replace("'"      , "&#039;"); // apenas quando ENT_QUOTES est・definida.
      str.replace("<"      , "&lt;");
      str.replace(">"      , "&gt;");
      return str;
   }

} // namespace ca2