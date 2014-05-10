#include "framework.h"

namespace core
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

} // namespace core

