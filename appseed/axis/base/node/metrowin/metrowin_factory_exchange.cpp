#include "framework.h"


namespace metrowin
{


   factory_exchange::factory_exchange(::base::application * papp) :
      element(papp)
   {

      System.factory().cloneable_large < stdio_file            >  (System.template type_info < ::file::text_buffer         > ()     );
      System.factory().cloneable_large < file                  >  (System.template type_info < ::file::stream_buffer       > ()     );
      System.factory().creatable_small < file_set              >  (System.template type_info < ::file::set                 > ()     );
      System.factory().cloneable       < file_system           >  (System.template type_info < ::file::system              > ()  , 1);
      System.factory().cloneable       < application           >  (System.template type_info < ::base::application         > ()  , 1);
      System.factory().cloneable       < dir                   >  (System.template type_info < ::file::dir::system         > ()  , 1);
      System.factory().cloneable_small < folder_watch          >  (System.template type_info < ::file::folder_watch        > ()     );
      System.factory().creatable       < window_draw           >  (System.template type_info < ::user::window_draw         > ()  , 1);
      System.factory().creatable_large < thread                >  (System.template type_info < ::thread                    > ()     );
      System.factory().creatable_large < window                >  (System.template type_info < ::user::interaction_impl    > ()     );
      System.factory().creatable       < os                    >  (System.template type_info < ::base::os                  > ()  , 1);
      System.factory().creatable       < port_forward          >  (System.template type_info < ::net::port_forward         > ()  , 1);
      System.factory().creatable_small < copydesk              >  (System.template type_info < ::base::copydesk            > ()  , 1);
      System.factory().creatable_small < crypto                >  (System.template type_info < ::crypto::crypto            > ()  , 1);
      System.factory().creatable_small < ip_enum               >  (System.template type_info < ::net::ip_enum              > ()     );
      System.factory().creatable       < printer               >  (System.template type_info < ::user::printer             > ()  , 1);
      

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace metrowin



void ca2_factory_exchange(::base::application * papp)
{
   metrowin::factory_exchange factoryexchange(papp);
}



