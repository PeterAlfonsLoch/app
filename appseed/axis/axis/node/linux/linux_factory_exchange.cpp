#include "framework.h"
#include "linux.h"


namespace linux
{

   namespace axis
   {

      factory_exchange::factory_exchange(sp(::aura::application) papp) :
         ::object(papp)
      {

         System.factory().creatable_large < file_set              >  (System. type_info < ::file::set              > ());
         System.factory().cloneable < file_system                 >  (System. type_info < ::file::system           > (), 1);
         System.factory().cloneable < dir                         >  (System. type_info < ::file::dir::system      > (), 1);
         System.factory().creatable < port_forward                >  (System. type_info < ::net::port_forward      > (), 1);
         System.factory().creatable_small < crypto                >  (System. type_info < ::crypto::crypto         > (), 1);
         System.factory().creatable_small < ip_enum               >  (System. type_info < ::net::ip_enum           > ());





         System.factory().creatable_small < copydesk              >  (System. type_info < ::user::copydesk         > (), 1);
         System.factory().creatable_small < message_queue         >  (System. type_info < ::aura::message_queue    > (), 1);


      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace win


void __node_axis_factory_exchange(::aura::application * papp)
{

   linux::axis::factory_exchange factoryexchange(papp);

}




