#pragma once


namespace sockets
{


   class CLASS_DECL_ca2 sip_server :
      public ::ca2::thread,
      public sip_base
   {
   public:
      
      
      string   m_strIp;
      int32_t      m_iPort;


      sip_server(sp(base_application) papp);
   

      virtual int32_t run();


   };


} // namespace sockets


