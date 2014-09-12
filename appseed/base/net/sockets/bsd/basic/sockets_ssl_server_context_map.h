#pragma once



   namespace sockets
   {


      class CLASS_DECL_BASE ssl_server_context_map :
         virtual public string_map < sp(ssl_server_context) >
      {
      public:

         mutex m_mutex;

         ssl_server_context_map(sp(::aura::application) papp);
         virtual ~ssl_server_context_map();

         SSL_CTX * InitializeContext(mutex ** ppmutex,const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in);
         SSL_CTX * InitializeContext(mutex ** ppmutex,const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in);

      };



   } // namespace sockets


