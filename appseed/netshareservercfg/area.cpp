#include "StdAfx.h"


namespace netshareservercfg
{

   area::area()
   {
      m_dcSource.CreateDC("DISPLAY", 0, 0, 0);
   }

} // namespace netshareservercfg