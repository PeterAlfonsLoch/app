#include "framework.h"

namespace axis
{
namespace macos
{

   
   factory_exchange::factory_exchange(::aura::application * papp) :
      element(papp)
   {
      
      System.factory().creatable < window_draw                >   (System.type_info < ::user::window_draw     > (), 1);
      System.factory().creatable_large < interaction_impl     >   (System.type_info < ::user::interaction_impl > ());
      System.factory().creatable < copydesk                   >   (System.type_info < ::aura::copydesk        > (), 1);
      System.factory().creatable < ::mac2::printer            >   (System.type_info < ::user::printer        > (), 1);
      
   }

    
   factory_exchange::~factory_exchange()
   {
       
   }

    
} // namespace macos
}//   namespace axis


void __node_axis_factory_exchange(sp(::aura::application) papp)
{
   
   ::axis::mac::factory_exchange factoryexchange(papp);
   
   
}



