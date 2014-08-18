#pragma once


namespace sockets
{


   class http_socket;


   class CLASS_DECL_AXIS http_listener :
      virtual public object
   {
   public:


      void on_http_complete(http_socket * psocket, ::http::e_status estatus);


   };

} // namespace sockets





