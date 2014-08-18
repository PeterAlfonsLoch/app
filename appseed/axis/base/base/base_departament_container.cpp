#include "framework.h"


departament_container_base::departament_container_base()
{

}


departament_container_base::~departament_container_base()
{

}


::base::application * departament_container_base::get_departament_app()
{

   ::base::application * papp = dynamic_cast < ::base::application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
