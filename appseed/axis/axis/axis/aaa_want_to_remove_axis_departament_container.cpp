#include "framework.h"


departament_container_base::departament_container_base()
{

}


departament_container_base::~departament_container_base()
{

}


::axis::application * departament_container_base::get_departament_app()
{

   ::axis::application * papp = dynamic_cast < ::axis::application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
