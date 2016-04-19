#include "framework.h"
#include "axis/net/net_sockets.h"
#include "net_email_department.h"


namespace net
{


   email_department::email_department(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {

   }


   bool email_department::utf8_mail(class ::net::email & email)
   {

      ::sockets::socket_handler handler(get_app());

      ::sockets::smtp_socket socket(handler);

      if(!socket.open((const string &) Application.file().as_string("X:\\sensitive\\sensitive\\seed\\default_sendmail_host.txt"), (port_t) 25))
         return false;

      socket.m_estate = ::sockets::smtp_socket::state_initial;

      socket.m_email = email;

      uint32_t dwEnd = ::get_tick_count() + 1000 * 120;

      handler.add(&socket);

      while (true)
      {

         handler.select(8,0);

         if(::get_tick_count() > dwEnd)
            break;

         if(socket.m_estate == ::sockets::smtp_socket::state_end)
            break;

      }

      return socket.m_estate == ::sockets::smtp_socket::state_sent || socket.m_estate == ::sockets::smtp_socket::state_quit || socket.m_estate == ::sockets::smtp_socket::state_end;
   }


   bool email_department::syntax_is_valid(const char * pszCandidate)
   {

      string strCandidate(pszCandidate);

      strCandidate.trim();

      index iFind = strCandidate.find("@");

      if(iFind <= 0)
         return false;

      ::count iLen = strCandidate.get_length();

      if(iFind == iLen - 1)
         return false;

      return true;

   }


} // namespace core




