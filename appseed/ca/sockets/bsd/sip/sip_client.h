#pragma once

namespace bsd
{

namespace sockets
{

   class CLASS_DECL_ca sip_client :
      virtual public ::radix::object
   {
   public:

      sip_base_client_socket *   m_psocket;

      void invite(const char * pszTo, const char * pszFrom);

   };

} // namespace sockets

} // namespace bsd