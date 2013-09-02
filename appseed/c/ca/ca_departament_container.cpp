#include "framework.h"


namespace ca2
{

   departament_container_base::departament_container_base()
   {
   }

   departament_container_base::~departament_container_base()
   {
   }

   ::application * departament_container_base::get_departament_app()
   {
      
      ::application * papp = dynamic_cast < ::application * > (this);
      
      if(papp != NULL)
         return papp;

      return get_app();

   }

} // namespace ca2
