#include "framework.h"
#include "ace/node/ansios/ansios.h"
#include "linux.h"



namespace linux
{

   namespace ace
   {


      factory_exchange::factory_exchange(sp(::ace::application) papp) :
         ::object(papp)
      {

         System.factory().cloneable_large <stdio_file             >  (System. type_info < ::file::text_buffer        > ());
         System.factory().cloneable_large < file                  >  (System. type_info < ::file::binary_buffer      > (), true);
         System.factory().cloneable_large < file                  >  (System. type_info < ::file::stream_buffer      > (), true);
         //System.factory().cloneable < application                 >  (System. type_info < ::ace::application        > (), 1);
         System.factory().creatable_large < ::thread              >  (System. type_info < ::thread                   > ());
         System.factory().creatable < os                          >  (System. type_info < ::ace::os                 > (), 1);
         System.factory().creatable < ::ansios::process           >  (System. type_info < ::process::process         > (), 1);
         System.factory().creatable < ::ansios::pipe              >  (System. type_info < ::process::pipe            > (), 1);
         System.factory().creatable < console                     >  (System. type_info < ::console::window          > (), 1);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace ace


} // namespace win


void __node_ace_factory_exchange(::ace::application * papp)
{

   ::linux::ace::factory_exchange factoryexchange(papp);

}




