#include "StdAfx.h"

point_array::~point_array(void)
{
}

void point_array::offset(int x, int y)
{
   for(int i = 0; i < get_size(); i++)
   {
      element_at(i).x += x;
      element_at(i).y += y;
   }
}



point64_array::~point64_array(void)
{
}

void point64_array::offset(__int64 x, __int64 y)
{
   for(int i = 0; i < get_size(); i++)
   {
      element_at(i).x += x;
      element_at(i).y += y;
   }
}
