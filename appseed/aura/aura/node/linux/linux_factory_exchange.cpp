#include "framework.h"


namespace linux
{


   factory_exchange::factory_exchange(sp(::aura::application) papp) :
      element(papp)
   {

      System.factory().cloneable_large <stdio_file             >  (System. type_info < ::file::text_buffer      > ());
      System.factory().cloneable_large < file                  >  (System. type_info < ::file::binary_buffer    > (), true);
      System.factory().cloneable < application                 >  (System. type_info < ::aura::application       > (), 1);
      System.factory().creatable_large < thread                >  (System. type_info < ::thread_impl                 > ());
      System.factory().creatable_large < interaction_impl                >  (System. type_info < ::user::interaction_impl           > ());
      System.factory().creatable < os                          >  (System. type_info < ::aura::os               > (), 1);
      System.factory().creatable_small < copydesk              >  (System. type_info < ::aura::copydesk         > (), 1);

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace win


void __node_axis_factory_exchange(sp(::aura::application) papp)
{

   linux::factory_exchange factoryexchange(papp);

}




