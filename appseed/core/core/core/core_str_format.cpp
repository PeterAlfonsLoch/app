#include "framework.h"



#ifndef NO_VARIADIC_TEMPLATE



  namespace str

{

      void format(string_format * pformat, calculator::value const & cval)
      {

         pformat->append(cval.to_string());

      }




   } // namespace str



#endif
