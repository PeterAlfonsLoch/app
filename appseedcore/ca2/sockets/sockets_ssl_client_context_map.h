#pragma once


namespace sockets
{


   class CLASS_DECL_ca ssl_client_context_map :
      virtual public ::collection::string_map < sp(ssl_client_context) >
   {
   public:


      ssl_client_context_map();
      virtual ~ssl_client_context_map();


   };



} // namespace sockets

