#include "StdAfx.h"

namespace sockets
{

   ::sockets::address * address::GetCopy()
   {
      return dynamic_cast < sockets::address * > (System.clone(this));
   }

} // namespace sockets