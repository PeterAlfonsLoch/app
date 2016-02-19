//#include "framework.h"


department_container_base::department_container_base()
{

}


department_container_base::~department_container_base()
{

}


::aura::application * department_container_base::get_department_app()
{

   ::aura::application * papp = dynamic_cast < ::aura::application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
