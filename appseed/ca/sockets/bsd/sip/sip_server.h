#pragma once


namespace sockets
{


   class CLASS_DECL_ca sip_server :
      public ::gen::thread,
      public sip_base
   {
   public:
      
      
      string   m_strIp;
      int32_t      m_iPort;


      sip_server(::ca::application * papp);
   

      virtual int32_t run();


   };


} // namespace sockets


