#pragma once


namespace sockets
{


   class CLASS_DECL_ca sip_server :
      public ::ca::thread,
      public sip_base
   {
   public:
      
      
      string   m_strIp;
      int      m_iPort;


      sip_server(::ca::application * papp);
   

      virtual int run();


   };


} // namespace sockets


