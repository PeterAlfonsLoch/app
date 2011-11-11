#include "StdAfx.h"


namespace cube8
{

            
   CLASS_DECL_ca class system * create_system()
   {
      return new class system;
   }
      
   CLASS_DECL_ca void destroy_system(system * & psystem)
   {
      delete psystem;
      psystem = NULL;
   }


} // namespace cube8

