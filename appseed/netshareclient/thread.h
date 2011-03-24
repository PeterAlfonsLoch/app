#pragma once

namespace netshareclient
{

   class application;
   class view;


   class CLASS_DECL_CA2_NETSHARECLIENT thread :
      public ::radix::thread
   {
   public:
	   thread(::ca::application * papp);
	   virtual ~thread();

      ::sockets::socket_handler m_h;
      tunnel m_tunnel;

      virtual int run();

   };


} // namespace netshareclient
