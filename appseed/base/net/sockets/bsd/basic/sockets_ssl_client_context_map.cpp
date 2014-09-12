#include "framework.h" // from "base/net/net_sockets.h"


namespace sockets
{


   ssl_client_context_map::ssl_client_context_map(sp(::aura::application) papp) :
      element(papp),
      m_mutex(papp)
   {
   }

   ssl_client_context_map::~ssl_client_context_map()
   {
   }



} // namespace sockets

