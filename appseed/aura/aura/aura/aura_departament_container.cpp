#include "framework.h"


departament_container_base::departament_container_base()
{

}


departament_container_base::~departament_container_base()
{

}


::aura::application * departament_container_base::get_departament_app()
{

   ::aura::application * papp = dynamic_cast < ::aura::application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
