#include "framework.h"


namespace ca2
{

   section_container_base::section_container_base()
   {
   }

   section_container_base::~section_container_base()
   {
   }

   ::ca2::application * section_container_base::get_section_app()
   {
      
      ::ca2::application * papp = dynamic_cast < ::ca2::application * > (this);
      
      if(papp != NULL)
         return papp;

      return get_app();

   }

} // namespace ca2
