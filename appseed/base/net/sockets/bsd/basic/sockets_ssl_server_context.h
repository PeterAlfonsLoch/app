#pragma once


typedef struct ssl_st SSL;
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_session_st SSL_SESSION;




   namespace sockets
   {


      class CLASS_DECL_BASE ssl_server_context :
         virtual public ::object
      {
      public:

         mutex m_mutex;
         SSL_CTX *         m_pcontext;
         string m_password;
         //SSL_SESSION *     m_psession;
         //int32_t               m_iRetry;


         ssl_server_context(sp(::aura::application) papp);
         virtual ~ssl_server_context();


         //void set_context(const char * pszContext);
         //void set_context(const char * pszFontopus, const char * pszSessId);

         void InitializeContext(const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in);
         void InitializeContext(const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in);


      };



   } // namespace sockets



