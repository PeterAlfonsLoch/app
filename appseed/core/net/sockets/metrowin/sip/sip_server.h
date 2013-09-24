#pragma once


namespace sockets
{


   class CLASS_DECL_ca2 sip_server :
      public ::thread,
      public sip_base
   {
   public:


      string   m_strIp;
      int      m_iPort;


      sip_server(base_application * papp);


      virtual int run();


   };


} // namespace sockets


