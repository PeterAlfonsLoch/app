#include "framework.h"
#include "macos.h"


namespace macos
{


   namespace base
   {


      factory_exchange::factory_exchange(::aura::application * papp) :
         ::object(papp)
      {
          
          System.factory().creatable < window_draw                 >   (System.type_info < ::user::window_draw        > (), 1);
          System.factory().creatable_large < interaction_impl      >   (System.type_info < ::user::interaction_impl   > ());


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



