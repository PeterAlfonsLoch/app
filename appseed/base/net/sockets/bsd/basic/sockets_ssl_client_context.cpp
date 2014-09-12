#include "framework.h" // from "base/net/net_sockets.h"
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/err.h>



namespace sockets
{


   ssl_client_context::ssl_client_context(sp(::aura::application) papp, const SSL_METHOD * pmethod) :
      element(papp),
      m_mutex(papp)
   {
      m_psession = NULL;
      if(pmethod == NULL)
         pmethod = SSLv23_method();
      InitializeContext(pmethod);
      m_iRetry = 0;
   }

   ssl_client_context::~ssl_client_context()
   {
      if(m_psession != NULL)
      {
         SSL_SESSION_free(m_psession);
      }
      if(m_pcontext != NULL)
      {
         SSL_CTX_free(m_pcontext);
      }
   }

   void ssl_client_context::set_context(const char * pszContext)
   {
      UNREFERENCED_PARAMETER(pszContext);
   }

   void ssl_client_context::set_context(const char * pszFontopus, const char * pszSessId)
   {
      UNREFERENCED_PARAMETER(pszFontopus);
      UNREFERENCED_PARAMETER(pszSessId);
   }

   void ssl_client_context::InitializeContext(const SSL_METHOD *meth_in)
   {
      ERR_load_ERR_strings();
      const SSL_METHOD *meth = meth_in != NULL ? meth_in : SSLv3_method();
      m_pcontext = SSL_CTX_new(meth);
      char buf[255];
      unsigned long err = ERR_get_error();
//         UINT uiReason = ERR_GET_REASON(err);
      ERR_error_string(err, buf);
//         const char * pszReason = ERR_reason_error_string(err);
      SSL_CTX_set_mode(m_pcontext, SSL_MODE_AUTO_RETRY);
   }


} // namespace sockets

