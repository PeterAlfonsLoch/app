#include "framework.h"
#include "metrowin.h"


namespace metrowin
{

   namespace base
   {

      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {

         System.factory().creatable_small < file_set              >(System.template type_info < ::file::set                 >());
         System.factory().cloneable       < file_system           >(System.template type_info < ::file::system              >(),1);
         System.factory().cloneable       < dir                   >(System.template type_info < ::file::dir::system         >(),1);
         System.factory().cloneable_small < folder_watch          >(System.template type_info < ::file::folder_watch        >());
         System.factory().creatable       < port_forward          >(System.template type_info < ::net::port_forward         >(),1);
         System.factory().creatable_small < crypto                >(System.template type_info < ::crypto::crypto            >(),1);
         System.factory().creatable_small < ip_enum               >(System.template type_info < ::net::ip_enum              >());

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace base


} // namespace metrowin



void __node_base_factory_exchange(::aura::application * papp)
{

   ::metrowin::base::factory_exchange factoryexchange(papp);

}



