#include "framework.h"
#include "windows.h"


namespace aura
{


   namespace windows
   {


      factory_exchange::factory_exchange(sp(::aura::application) papp):
         element(papp)
      {

         System.factory().cloneable_large    < ::windows::stdio_file         >(System.type_info < ::file::text_buffer         >());
         System.factory().cloneable_large    < ::windows::file               >(System.type_info < ::file::binary_buffer       >(),true);
         System.factory().creatable          < ::windows::application        >(System.type_info < ::aura::application         >(),1);
         System.factory().cloneable_small    < ::windows::folder_watch       >(System.type_info < ::file::folder_watch        >());
         System.factory().creatable_large    < ::windows::thread             >(System.type_info < ::thread_impl               >());
         System.factory().creatable          < ::windows::os                 >(System.type_info < ::aura::os                  >(),1);
         System.factory().creatable          < ::windows::pipe               >(System.type_info < ::process::pipe             >(),32);
         System.factory().creatable          < ::windows::process            >(System.type_info < ::process::process          >(),32);

         ::windows::shell::theWindowsShell.Initialize();

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace windows


} // namespace aura


void __node_aura_factory_exchange(sp(::aura::application) papp)
{

   ::aura::windows::factory_exchange factoryexchange(papp);

}




