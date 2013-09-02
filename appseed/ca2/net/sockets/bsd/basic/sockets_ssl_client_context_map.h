#pragma once



   namespace sockets
   {


      class CLASS_DECL_ca2 ssl_client_context_map :
         virtual public string_map < sp(ssl_client_context) >
      {
      public:


         ssl_client_context_map();
         virtual ~ssl_client_context_map();


      };



   } // namespace sockets


