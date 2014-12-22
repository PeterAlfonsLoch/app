#include "base/net/sockets/bsd/sockets.h"


namespace sockets
{


   ssl_client_context_map::ssl_client_context_map(::aura::application * papp) :
      element(papp),
      m_mutex(papp)
   {
   }

   ssl_client_context_map::~ssl_client_context_map()
   {
   }



} // namespace sockets

