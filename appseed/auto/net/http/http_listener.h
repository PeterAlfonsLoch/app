#pragma once


namespace http
{


   //class http_socket;


   class CLASS_DECL_BASE listener:
      virtual public object
   {
   public:


      void on_http_complete(::sockets::http_socket * psocket,::http::e_status estatus);


   };

} // namespace sockets





