//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"
//#include "windows.h"


namespace base
{


   namespace windows
   {


      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {



      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace windows


} // namespace base


void __node_base_factory_exchange(::aura::application * papp)
{

   ::base::windows::factory_exchange factoryexchange(papp);

}




