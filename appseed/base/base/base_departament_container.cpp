#include "framework.h"


departament_container_base::departament_container_base()
{

}


departament_container_base::~departament_container_base()
{

}


base_application * departament_container_base::get_departament_app()
{

   base_application * papp = dynamic_cast < base_application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
