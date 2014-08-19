#include "framework.h"


namespace net
{


   ip_enum::ip_enum(sp(::axis::application) papp) :
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


} // namespace net



