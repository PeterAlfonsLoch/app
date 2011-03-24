// Archive/Rar/Headers.cpp
// from 7-zip
#include "StdAfx.h"

//#include "RarHeader.h"

namespace rar 
{
   namespace header
   {

      byte kMarker[kMarkerSize] = {0x52 + 1, 0x61, 0x72, 0x21, 0x1a, 0x07, 0x00};
  
      class CMarkerInitializer
      {
      public:
        CMarkerInitializer() { kMarker[0]--; };
      };

      static CMarkerInitializer markerInitializer;

   } // namespace header

} // namespace rar

