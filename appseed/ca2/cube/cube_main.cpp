#include "StdAfx.h"


namespace cube
{

            
   CLASS_DECL_ca2 class cube * create_cube()
   {
      return new class cube;
   }
      
   CLASS_DECL_ca2 void destroy_cube(cube * & pcube)
   {
      delete pcube;
      pcube = NULL;
   }


} // namespace cube

