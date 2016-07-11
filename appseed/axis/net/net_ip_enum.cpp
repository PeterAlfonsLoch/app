#include "framework.h"


namespace net
{


   ip_enum::ip_enum(::aura::application * papp) :
      ::object(papp)
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(array < ::net::address > & ipa)
   {

      UNREFERENCED_PARAMETER(ipa);

      ::exception::throw_interface_only(get_app());

      return 0;

   }


} // namespace net



