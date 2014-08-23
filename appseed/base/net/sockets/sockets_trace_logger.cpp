#include "framework.h"


namespace sockets
{


   void trace_logger::log(base_socket_handler * phandler, base_socket * sock, const string & strUser, int32_t iError, const string & strSystem, ::axis::log::e_level elevel)
   {

      string strLevel = ::log_level_name(elevel);

      if (sock)
      {
         Sys(phandler->m_pauraapp).log().trace("fd %d :: %s: %d %s (%s)\n", sock->GetSocket(), strUser.c_str(), iError, strSystem.c_str(), strLevel.c_str());
      }
      else
      {
         Sys(phandler->m_pauraapp).log().trace("%s: %d %s (%s)\n", strUser.c_str(), iError, strSystem.c_str(), strLevel.c_str());
      }

   }


} // namespace sockets



