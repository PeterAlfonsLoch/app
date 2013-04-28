#include "framework.h"


namespace ca
{

   section_container_base::section_container_base()
   {
   }

   section_container_base::~section_container_base()
   {
   }

   ::ca::application * section_container_base::get_section_app()
   {
      
      ::ca::application * papp = dynamic_cast < ::ca::application * > (this);
      
      if(papp != NULL)
         return papp;

      return get_app();

   }

} // namespace ca