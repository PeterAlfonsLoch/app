#pragma once


namespace sockets
{


   class CLASS_DECL_BASE sip_server :
      public ::thread,
      public sip_base
   {
   public:


      string   m_strIp;
      int      m_iPort;


      sip_server(::base::application * papp);


      virtual int run();


   };


} // namespace sockets


