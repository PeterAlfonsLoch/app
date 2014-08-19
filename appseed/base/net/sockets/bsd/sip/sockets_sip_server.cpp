#include "framework.h"

namespace sockets
{

   sip_server::sip_server(sp(::axis::application) papp) :
      element(papp),
      thread(papp)
   {
   }

   int32_t sip_server::run()
   {
/*      socket_handler handler(get_app());
      handler.EnablePool();
      listen_socket < sip_socket > listensocket(handler);
      listensocket.m_bDetach = true;
      while(get_run())
      {
         if (listensocket.Bind(m_strIp, (port_t) m_iPort))
         {
            string strMessage;
            strMessage.Format("could not bind to address %s %d", m_strIp, m_iPort);
            System.simple_message_box(strMessage);
            return -1;
         }
         handler.add(&listensocket);
         while(get_run())
         {
            handler.Select(8,0);
         }
      }*/
      return 0;
   }

} // namespace sockets