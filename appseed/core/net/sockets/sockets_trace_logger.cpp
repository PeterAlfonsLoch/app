#include "framework.h"


namespace sockets
{


   void trace_logger::error(base_socket_handler * phandler, base_socket * sock, const string & strCall, int32_t iError, const string & strSystemError, ::core::log::e_level elevel)
   {

      string strLevel = ::log_level_name(elevel);

      if (sock)
      {
         Sys(phandler->m_pbaseapp).log().trace("fd %d :: %s: %d %s (%s)\n", sock->GetSocket(), strCall.c_str(), iError, strSystemError.c_str(), strLevel.c_str());
      }
      else
      {
         Sys(phandler->m_pbaseapp).log().trace("%s: %d %s (%s)\n", strCall.c_str(), iError, strSystemError.c_str(), strLevel.c_str());
      }

   }


} // namespace sockets



