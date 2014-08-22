#include "framework.h"


namespace linux
{


   factory_exchange::factory_exchange(sp(::axis::application) papp) :
      element(papp)
   {

      System.factory().creatable_large < file_set              >  (System. type_info < ::file::set              > ());
      System.factory().cloneable < file_system                 >  (System. type_info < ::file::system           > (), 1);
      System.factory().cloneable < dir                         >  (System. type_info < ::file::dir::system      > (), 1);
      System.factory().creatable < port_forward                >  (System. type_info < ::net::port_forward      > (), 1);
      System.factory().creatable_small < crypto                >  (System. type_info < ::crypto::crypto         > (), 1);
      System.factory().creatable_small < ip_enum               >  (System. type_info < ::net::ip_enum           > ());

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace win


void __node_base_factory_exchange(sp(::axis::application) papp)
{

   linux::factory_exchange factoryexchange(papp);

}




