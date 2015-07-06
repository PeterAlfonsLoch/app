#include "framework.h"
#include "macos.h"


namespace macos
{
   
   
   namespace axis
   {
      
      
      factory_exchange::factory_exchange(sp(::aura::application) papp) :
      ::object(papp)
      {
         
         System.factory().creatable_large < file_set             >   (System.type_info < ::file::set             > ());
         System.factory().cloneable < file_system                >   (System.type_info < ::file::system          > (), 1);
         System.factory().cloneable < dir                        >   (System.type_info < ::file::dir::system     > (), 1);
         System.factory().creatable < port_forward               >   (System.type_info < ::net::port_forward     > (), 1);
         System.factory().creatable < crypto                     >   (System.type_info < ::crypto::crypto           > (), 1);
         System.factory().creatable < ip_enum                     >   (System.type_info < ::net::ip_enum     > (), 1);
         
         System.factory().creatable < window_draw                 >   (System.type_info < ::user::window_draw        > (), 1);
         System.factory().creatable_large < interaction_impl      >   (System.type_info < ::user::interaction_impl   > ());
         System.factory().creatable < copydesk                    >   (System.type_info < ::user::copydesk           > (), 1);
//         System.factory().creatable < printer                     >   (System.type_info < ::user::printer            > (), 1);
         System.factory().creatable < message_queue               >   (System.type_info < ::user::message_queue      > (), 1);
         
      }
      
      
      factory_exchange::~factory_exchange()
      {
         
      }
      
      
   } // namespace axis
   
   
} // namespace macos


void __node_axis_factory_exchange(::aura::application * papp)
{
   
   ::macos::axis::factory_exchange factoryexchange(papp);
   
   
}



