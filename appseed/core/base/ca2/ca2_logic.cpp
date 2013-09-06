#include "framework.h"

namespace ca2
{

   namespace logic
   {

      bool forward_conditional(bool p, bool q)
      {
         return !p || q;
      }

      bool reverse_conditional(bool p, bool q)
      {
         return  q || !p;
      }

   } // namespace logic

} // namespace ca2

