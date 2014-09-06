#include "axis/user/user.h"


namespace linux
{

   namespace axis
   {


      factory_exchange::factory_exchange(sp(::aura::application) papp) :
         element(papp)
      {

         System.factory().creatable < window_draw                 >  (System. type_info < ::user::window_draw      > (), 1);
         System.factory().creatable_large < interaction_impl                >  (System. type_info < ::user::interaction_impl           > ());
         System.factory().creatable_small < copydesk              >  (System. type_info < ::axis::copydesk         > (), 1);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace win


void __node_axis_factory_exchange(sp(::aura::application) papp)
{

   linux::axis::factory_exchange factoryexchange(papp);

}




