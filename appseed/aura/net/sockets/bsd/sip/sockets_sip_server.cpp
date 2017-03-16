#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{

   sip_server::sip_server(::aura::application * papp) :
      ::object(papp),
      thread(papp)
   {
   }

   int32_t sip_server::run()
   {
      return 0;
   }

} // namespace sockets