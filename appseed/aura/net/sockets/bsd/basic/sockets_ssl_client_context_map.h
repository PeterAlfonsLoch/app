#pragma once



   namespace sockets
   {


      class CLASS_DECL_AURA ssl_client_context_map :
         virtual public string_map < spa(ssl_client_context) >
      {
      public:

         ssl_client_context_map(::aura::application * papp);
         virtual ~ssl_client_context_map();

      };



   } // namespace sockets


