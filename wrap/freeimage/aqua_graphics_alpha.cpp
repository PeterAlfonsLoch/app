#include "framework.h"

CLASS_DECL_AQUA void pre_multiply_alpha(unsigned int * pui,int cx,int cy,int stride)
{

   int s =  stride / 4 * cy;

   for(int i = 0; i < s; i++)
   {
      pui[i] = ((pui[i] & 0xff000000) >> 24) << 24
         | (((((pui[i] & 0xff0000) >> 16) * ((pui[i] & 0xff000000) >> 24)) << 8) & 0xff0000)
         | ((((pui[i] & 0xff00) >> 8) * ((pui[i] & 0xff000000) >> 24)) & 0xff00)
         | (((pui[i] & 0xff) * ((pui[i] & 0xff000000) >> 24)) >> 8);
      //pui++;
   }

}