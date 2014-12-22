#include "framework.h"

thread_pointer < lconv > t_plconv;

extern "C"
{



   struct lconv *localeconv(void)
   {

      if(t_plconv == NULL)
      {

         t_plconv = new lconv;

         t_plconv->decimal_point = ".";

      }

      return t_plconv;

   }



} // extern "C"











