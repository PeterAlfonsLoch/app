#include "StdAfx.h"


namespace netshareclient
{

   area::area(::ca::application * papp) :
      //ca(papp),
         m_dib1(papp),
         m_dib2(papp),
         m_dcSource(papp)
   {
      m_dcSource->CreateDC("DISPLAY", 0, 0, 0);
   }

} // namespace netshareclient