#pragma once


namespace sockets
{


   class CLASS_DECL_BASE sip_server :
      public thread,
      public sip_base
   {
   public:
      
      
      string   m_strIp;
      int32_t      m_iPort;


      sip_server(sp(::axis::application) papp);
   

      virtual int32_t run();


   };


} // namespace sockets


