#include "framework.h" // from ""axis/user/user.h"
#include "linux.h"


namespace linux
{


   namespace base
   {


      factory_exchange::factory_exchange(sp(::aura::application) papp) :
         ::object(papp)
      {

//         System.factory().creatable < window_draw                 >  (System. type_info < ::user::window_draw      > (), 1);
//         System.factory().creatable_large < interaction_impl      >  (System. type_info < ::user::interaction_impl > ());
         System.factory().creatable_small < copydesk              >  (System. type_info < ::user::copydesk         > (), 1);
//         System.factory().creatable_small < message_queue         >  (System. type_info < ::user::message_queue    > (), 1);

         System.factory().creatable < window_draw                 >  (System. type_info < ::user::window_draw      > (), 1);
         System.factory().creatable_large < interaction_impl      >  (System. type_info < ::user::interaction_impl > ());


      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace base


} // namespace win


void __node_base_factory_exchange(::aura::application * papp)
{

   linux::base::factory_exchange factoryexchange(papp);

}




