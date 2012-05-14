#include "framework.h"


rgb_quad_array::rgb_quad_array()
{
}

rgb_quad_array::~rgb_quad_array()
{
}

void rgb_quad_array::create_web_palette()
{
   // Do nothing
   const DWORD STANDARD_PALETTE[] = {00,51,102,153,204,255};
   const INT STANDARD_COLOR_SIZE = 6;
//   const INT STANDARD_PALETTE_VAL_DIF = 51;
   set_size(216);
//   DWORD dwColorMapTable[216] = {0};
   int nColorMapIdx = 0;
   for(int nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
   {
      for(int nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
      {
         for(int nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
         {
            this->element_at(nColorMapIdx).rgbRed      = (BYTE) STANDARD_PALETTE[nRedIdx];
            this->element_at(nColorMapIdx).rgbGreen    = (BYTE) STANDARD_PALETTE[nGreenIdx];
            this->element_at(nColorMapIdx).rgbBlue     = (BYTE) STANDARD_PALETTE[nBlueIdx];
            this->element_at(nColorMapIdx).rgbReserved = 0;
            ++nColorMapIdx;
         }
      }
   }
}
