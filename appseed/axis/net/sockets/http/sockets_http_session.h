#pragma once


   namespace sockets
   {



      class CLASS_DECL_AXIS http_session :
         virtual public http_get_socket,
         virtual public http_post_socket,
         virtual public http_put_socket
      {
      public:


         string                              m_strProtocol;
         bool                                m_bRequestComplete;
         
         


         http_session(::sockets::base_socket_handler & phandler, const string & protocol, const string & host);
         ~http_session();



         virtual int64_t add_ref()
         {

            return ::object::add_ref();

         }


         virtual int64_t dec_ref()
         {

            return ::object::dec_ref();

         }



         using http_client_socket::request;
         
         virtual void request(const string & strMethod, const string & pszRequest);
         virtual void request(e_http_method emethod, const string & pszRequest);

         virtual void step();

         virtual void OnHeaderComplete();
         virtual void OnDataComplete();


      };




   } // namespace sockets


