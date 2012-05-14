#include "framework.h"


namespace ca4
{


   email::email()
   {
   }

   bool email::utf8_mail(class ::email & email)
   {
      ::sockets::socket_handler handler(get_app());
      ::sockets::smtp_socket socket(handler);
      if(!socket.open("ca2.cc", 25))
         return false;

      socket.m_estate = ::sockets::smtp_socket::state_initial;
      socket.m_email = email;

      DWORD dwEnd = ::GetTickCount() + 1000 * 120;
      handler.add(&socket);
      while (true)
      {
         handler.Select(8,0);
         if(::GetTickCount() > dwEnd)
            break;
         if(socket.m_estate == ::sockets::smtp_socket::state_end)
            break;
      }
      return socket.m_estate == ::sockets::smtp_socket::state_sent
         || socket.m_estate == ::sockets::smtp_socket::state_quit
         || socket.m_estate == ::sockets::smtp_socket::state_end;
   }

   bool email::syntax_is_valid(const char * pszCandidate)
   {
      string strCandidate(pszCandidate);
      strCandidate.trim();
      index iFind = strCandidate.find("@");
      if(iFind <= 0)
         return false;
      count iLen = strCandidate.get_length();
      if(iFind == iLen - 1)
         return false;
      return true;
   }




} // namespace ca4