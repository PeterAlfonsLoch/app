// LzOutWindow.cpp
// from 7-zip on 2012-12-23, dawn
#include "framework.h"

//#include "LzOutWindow.h"

namespace compress
{

   void lz_out_window::Init(bool solid)
   {
     if (!solid)
       out_buffer::Init();
     ErrorCode = S_OK;
   }

} // namespace compress