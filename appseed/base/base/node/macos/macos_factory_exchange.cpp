#include "framework.h"
#include "macos.h"


namespace macos
{


   namespace base
   {


      factory_exchange::factory_exchange(::aura::application * papp) :
         ::object(papp)
      {


      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} //   namespace macos


void __node_base_factory_exchange(::aura::application * papp)
{

   ::macos::base::factory_exchange factoryexchange(papp);


}



