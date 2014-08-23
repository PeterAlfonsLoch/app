#include "framework.h"


namespace android
{


   factory_exchange::factory_exchange(sp(::aura::application) papp) :
      element(papp)
   {

      System.factory().cloneable_large < stdio_file            >  (System. type_info < ::file::text_buffer         > ());
      System.factory().cloneable_large < file                  >  (System. type_info < ::file::binary_buffer              > ());
      System.factory().creatable_large < file_set              >  (System. type_info < ::file::set          > ());
      System.factory().creatable < file_system                 >(System. type_info < ::file::system       >(),1);
      System.factory().creatable < application                 >(System. type_info < ::axis::application  >(),1);
      System.factory().creatable < dir                         >(System. type_info < ::file::dir::system        >(),1);
      System.factory().creatable < window_draw                 >  (System. type_info < ::user::window_draw        > (), 1);
      System.factory().creatable_large < thread                >  (System. type_info < ::thread             > ());
      System.factory().creatable_large < interaction_impl      >  (System. type_info < ::user::interaction_impl             > ());
      System.factory().creatable < os                          >  (System. type_info < ::base::os                 > (), 1);
      //System.factory().creatable < port_forward              >  (System. type_info < ::ca2::port_forward      > (), 1);
      System.factory().creatable_small < copydesk              >  (System. type_info < ::base::copydesk          > (), 1);
      System.factory().creatable_small < crypto                >  (System. type_info < ::crypto::crypto             > (), 1);
      System.factory().creatable_small < ip_enum               >  (System. type_info < ::net::ip_enum           > ());

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace android


extern "C"
void ca2_factory_exchange(sp(::aura::application) papp)
{
   ::android::factory_exchange factoryexchange(papp);
}


