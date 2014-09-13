#include "framework.h"
#include "macos.h"

namespace macos
{
namespace axis
{

   
   factory_exchange::factory_exchange(::aura::application * papp) :
      element(papp)
   {
      
      System.factory().creatable < window_draw                >   (System.type_info < ::user::window_draw     > (), 1);
      System.factory().creatable_large < interaction_impl     >   (System.type_info < ::user::interaction_impl > ());
      System.factory().creatable < copydesk                   >   (System.type_info < ::axis::copydesk        > (), 1);
      System.factory().creatable < printer            >   (System.type_info < ::user::printer        > (), 1);
      
   }

    
   factory_exchange::~factory_exchange()
   {
       
   }

    
} // namespace axis
}//   namespace macos


void __node_axis_factory_exchange(sp(::aura::application) papp)
{
   
   ::macos::axis::factory_exchange factoryexchange(papp);
   
   
}



