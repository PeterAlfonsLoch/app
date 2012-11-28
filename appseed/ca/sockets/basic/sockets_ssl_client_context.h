#pragma once


typedef struct ssl_st SSL;
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_session_st SSL_SESSION;


namespace sockets
{


   class CLASS_DECL_ca ssl_client_context :
      virtual public ::radix::object
   {
   public:


      SSL_CTX *         m_pcontext;
      SSL_SESSION *     m_psession;
      int               m_iRetry;


      ssl_client_context(::ca::application * papp, const SSL_METHOD * pmethod = NULL);
      virtual ~ssl_client_context();


      void set_context(const char * pszContext);
      void set_context(const char * pszFontopus, const char * pszSessId);


      void InitializeContext(const SSL_METHOD *meth_in);


   };



} // namespace sockets

