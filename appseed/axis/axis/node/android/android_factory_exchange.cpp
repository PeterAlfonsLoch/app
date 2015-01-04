//#include "framework.h"
//#include "android.h"


namespace android
{


   namespace axis
   {


      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {

         System.factory().creatable_large < file_set              >(System. type_info < ::file::set            >());
         System.factory().creatable < file_system                 >(System. type_info < ::file::system         >(),1);
         System.factory().creatable < dir                         >(System. type_info < ::file::dir::system    >(),1);
         System.factory().creatable_small < crypto                >(System. type_info < ::crypto::crypto       >(),1);
         System.factory().creatable_small < ip_enum               >(System. type_info < ::net::ip_enum         >());

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace android


void __node_axis_factory_exchange(::aura::application * papp)
{

   ::android::axis::factory_exchange factoryexchange(papp);

}


