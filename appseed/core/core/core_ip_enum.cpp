#include "framework.h"


namespace core
{


   ip_enum::ip_enum(sp(base_application) papp) :
      base_element(papp)
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);

      throw interface_only_exception(get_app());

      return 0;

   }


} // namespace core



