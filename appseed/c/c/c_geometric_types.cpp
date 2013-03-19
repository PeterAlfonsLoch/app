#include "framework.h"


bool polygon_contains(LPPOINT lppt, LPPOINT lpptPolygon, int iCount)
{

   int i, j = iCount - 1;
   int x = lppt->x;
   int y = lppt->y;
   bool oddNodes = false;

   for (i=0; i < iCount; i++)
   {
      if(((lpptPolygon[i].y < y && lpptPolygon[j].y >= y) ||  (lpptPolygon[j].y < y && lpptPolygon[i].y >= y)) && (lpptPolygon[i].x <= x || lpptPolygon[j].x <= x))
      {
         oddNodes ^= (lpptPolygon[i].x + (y - lpptPolygon[i].y) / (lpptPolygon[j].y - lpptPolygon[i].y) * (lpptPolygon[j].x - lpptPolygon[i].x) < x);
      }
      j = i;
   }

   return oddNodes;

}
