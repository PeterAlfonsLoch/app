#include "framework.h"


namespace ca
{


   ip_enum::ip_enum(::ca::applicationsp papp) :
      ca(papp)
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


} // namespace ca



