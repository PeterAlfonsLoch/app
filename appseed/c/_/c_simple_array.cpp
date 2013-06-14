#include "framework.h"


double simple_double_array::average()
{
   if(this->get_count() == 0)
      return 0.0;
   double d = 0.0;
   for(index i = 0; i < this->get_count(); i++)
   {
      d += this->element_at(i) / ((double) this->get_count());
   }
   return d;
}
