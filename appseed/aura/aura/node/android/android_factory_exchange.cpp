#include "framework.h"
#include "android.h"


namespace android
{

   namespace aura
   {

      factory_exchange::factory_exchange(sp(::aura::application) papp):
         element(papp)
      {

         System.factory().cloneable_large < stdio_file            >(System. type_info < ::file::text_buffer       >());
         System.factory().cloneable_large < file                  >(System. type_info < ::file::binary_buffer     >());
         System.factory().creatable_large < file_set              >(System. type_info < ::file::set               >());
         System.factory().creatable < application                 >(System. type_info < ::aura::application       >(),1);
         System.factory().creatable_large < thread                >(System. type_info < ::thread                  >());
         System.factory().creatable < os                          >(System. type_info < ::aura::os                >(),1);
         System.factory().creatable < ::ansios::process           >(System. type_info < ::process::process        >(), 10);
         System.factory().creatable < ::ansios::pipe              >(System. type_info < ::process::pipe           >(), 10);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace aura


} // namespace android


extern "C"
void __node_aura_factory_exchange(sp(::aura::application) papp)
{

   ::android::aura::factory_exchange factoryexchange(papp);

}







