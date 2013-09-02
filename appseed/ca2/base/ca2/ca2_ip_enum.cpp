#include "framework.h"


namespace ca2
{


   ip_enum::ip_enum(sp(::application) papp) :
      element(papp)
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


} // namespace ca2



