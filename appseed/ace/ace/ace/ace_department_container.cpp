//#include "framework.h"


department_container_base::department_container_base()
{

}


department_container_base::~department_container_base()
{

}


::ace::application * department_container_base::get_department_app()
{

   ::ace::application * papp = dynamic_cast < ::ace::application * > (this);

   if(papp != NULL)
      return papp;

   return get_app();

}
