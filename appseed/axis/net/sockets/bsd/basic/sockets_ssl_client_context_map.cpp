#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "axis/net/net_sockets.h"


namespace sockets
{


   ssl_client_context_map::ssl_client_context_map(::aura::application * papp) :
      ::object(papp),
      m_mutex(papp)
   {
   }

   ssl_client_context_map::~ssl_client_context_map()
   {
   }



} // namespace sockets

