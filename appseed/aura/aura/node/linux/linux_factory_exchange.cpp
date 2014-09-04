#include "framework.h"


namespace linux
{

   namespace aura
   {


      factory_exchange::factory_exchange(sp(::aura::application) papp) :
         element(papp)
      {

         System.factory().cloneable_large <stdio_file             >  (System. type_info < ::file::text_buffer      > ());
         System.factory().cloneable_large < file                  >  (System. type_info < ::file::binary_buffer    > (), true);
         System.factory().cloneable < application                 >  (System. type_info < ::aura::application       > (), 1);
         System.factory().creatable_large < thread                >  (System. type_info < ::thread_impl                 > ());
         System.factory().creatable < os                          >  (System. type_info < ::aura::os               > (), 1);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace aura


} // namespace win


void __node_aura_factory_exchange(sp(::aura::application) papp)
{

   ::linux::aura::factory_exchange factoryexchange(papp);

}




