#include "framework.h"
#include "metrowin.h"


namespace metrowin
{

   namespace axis
   {

      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {

         System.factory().creatable       < window_draw              >(System.template type_info < ::user::window_draw         >(),1);
         System.factory().creatable_large < interaction_impl         >(System.template type_info < ::user::interaction_impl    >());
         System.factory().creatable_small < copydesk                 >(System.template type_info < ::axis::copydesk            >(),1);
         //      System.factory().creatable       < printer               >  (System.template type_info < ::user::printer             > ()  , 1);

         System.factory().creatable          < ::windows::message_queue      >(System.type_info < ::aura::message_queue       >(),32);


      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace axis


} // namespace metrowin


void __node_axis_factory_exchange(::aura::application * papp)
{
   ::metrowin::axis::factory_exchange factoryexchange(papp);
}



