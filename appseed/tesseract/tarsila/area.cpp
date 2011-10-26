#include "StdAfx.h"


namespace tarsila
{

   area::area()
   {
      m_dcSource.CreateDC("DISPLAY", 0, 0, 0);
   }

} // namespace tarsila