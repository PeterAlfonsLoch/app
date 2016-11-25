#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "axis/net/net_sockets.h"


#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/err.h>


namespace sockets
{


   ssl_server_context::ssl_server_context(::aura::application * papp) :
      ::object(papp),
      m_mutex(papp)
   {

      m_pcontext = NULL;

   }


   ssl_server_context::~ssl_server_context()
   {

      if(m_pcontext != NULL)
      {

         SSL_CTX_free(m_pcontext);

      }

   }


   SSL_CTX * ssl_server_context::InitializeContext(const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {
      
   }


   void ssl_server_context::InitializeContext(const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {


   }


} // namespace sockets

