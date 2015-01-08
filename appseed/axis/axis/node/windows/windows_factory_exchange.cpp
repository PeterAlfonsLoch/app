//#include "framework.h"
//#include "framework.h" // from "axis/net/net_sockets.h"
//#include "windows_axis_dir.h"
//#include "windows_factory_exchange.h"
//#include "windows_port_forward.h"
//#include "windows_dir.h"
//#include "windows_axisfile_system.h"
//#include "windows_file_set.h"
//#include "windows_crypto.h"
//#include "windows_ip_enum.h"

namespace windows
{


   factory_exchange::factory_exchange(::aura::application * papp) :
      element(papp)
   {

      System.factory().creatable_large    < file_set                       > (System.type_info < ::file::set                 >()       );
      System.factory().creatable_small    < ::windows::axis::file_system   > (System.type_info < ::file::system              >()  ,    1);
      System.factory().creatable_small    < ::windows::axis::dir           > (System.type_info < ::file::dir::system         >()  ,    1);
      System.factory().creatable          < port_forward                   > (System.type_info < ::net::port_forward         >()  ,    1);
      System.factory().creatable_small    < crypto                         > (System.type_info < ::crypto::crypto            >()  ,    1);
      System.factory().creatable_small    < ip_enum                        > (System.type_info < ::net::ip_enum              >()       );

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace windows


void __node_axis_factory_exchange(::aura::application * papp)
{

   windows::factory_exchange factoryexchange(papp);

}




