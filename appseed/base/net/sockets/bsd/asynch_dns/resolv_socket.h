#pragma once


namespace sockets
{


   /** Async DNS resolver socket. 
   \ingroup async */
   class resolv_socket : public tcp_socket
   {
   public:


      /* type, host, result */
      typedef string_map < ::string_to_string > cache_t;

      /* type, host, time */
      typedef string_map < string_map < time_t > > timeout_t; 


      string m_query;
      string m_data;
      bool m_bServer;
      base_socket *m_parent;
      int32_t m_resolv_id;
      string m_resolv_host;
      port_t m_resolv_port;
      in_addr m_resolv_address;
      bool m_resolve_ipv6;
      in6_addr m_resolv_address6;
      bool m_cached;


      resolv_socket(base_socket_handler&);
      resolv_socket(base_socket_handler&, base_socket *parent, const string & host, port_t port, bool ipv6 = false);
      resolv_socket(base_socket_handler&, base_socket *parent, in_addr);
      resolv_socket(base_socket_handler&, base_socket *parent, in6_addr&);
      ~resolv_socket();

      void OnAccept() { m_bServer = true; }
      void OnLine(const string & line);
      void OnDetached();
      void OnDelete();

      void SetId(int32_t x) { m_resolv_id = x; }
      int32_t GetId() { return m_resolv_id; }

      void OnConnect();

      void SetResolveIpv6(bool x = true) { m_resolve_ipv6 = x; }

   };


} // namespace sockets





