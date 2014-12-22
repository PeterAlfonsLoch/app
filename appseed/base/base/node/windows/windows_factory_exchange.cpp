#include "framework.h" // from "base/user/user.h"
#include "windows.h"


namespace base
{


   namespace windows
   {


      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {

         System.factory().creatable          < ::windows::window_draw        >(System.type_info < ::user::window_draw         >(),1);
         System.factory().creatable_large    < ::windows::interaction_impl   >(System.type_info < ::user::interaction_impl    >());
         System.factory().creatable_small    < ::windows::copydesk           >(System.type_info < ::base::copydesk            >(),1);
         System.factory().creatable_large    < ::windows::print_job          >(System.type_info < ::user::print_job           >());
         System.factory().creatable          < ::windows::message_queue      >(System.type_info < ::aura::message_queue       >(), 32);


      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace windows


} // namespace base


void __node_base_factory_exchange(::aura::application * papp)
{

   ::base::windows::factory_exchange factoryexchange(papp);

}




