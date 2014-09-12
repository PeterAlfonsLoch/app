#include "framework.h" // from "base/net/net_sockets.h"
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/err.h>



namespace sockets
{


   ssl_server_context::ssl_server_context(sp(::aura::application) papp) :
      element(papp),
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

   void ssl_server_context::InitializeContext(const string & context,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {
      
      const SSL_METHOD *meth = meth_in != NULL ? meth_in : SSLv3_method();

      m_pcontext = SSL_CTX_new(meth);
      SSL_CTX_set_mode(m_pcontext,SSL_MODE_AUTO_RETRY);
      // session id
      if(context.get_length())
         SSL_CTX_set_session_id_context(m_pcontext,(const uchar *)(const  char *)context,(uint32_t)context.get_length());
      else
         SSL_CTX_set_session_id_context(m_pcontext,(const uchar *)"--is_empty--",9);

      if(!SSL_CTX_use_certificate_chain_file(m_pcontext,keyfile))
      {
         /* Load our keys and certificates*/
         if(!(SSL_CTX_use_certificate_file(m_pcontext,keyfile,SSL_FILETYPE_PEM)))
         {
            TRACE(string("tcp_socket InitializeContext,0,Couldn't read certificate file ") + keyfile + "::aura::log::level_fatal");
         }
      }

      m_password = password;
      SSL_CTX_set_default_passwd_cb(m_pcontext,tcp_socket_SSL_password_cb);
      SSL_CTX_set_default_passwd_cb_userdata(m_pcontext,this);
      if(!(SSL_CTX_use_PrivateKey_file(m_pcontext,keyfile,SSL_FILETYPE_PEM)))
      {
         TRACE(string("tcp_socket InitializeContext,0,Couldn't read private key file ") + keyfile + "::aura::log::level_fatal");
      }

   }


   void ssl_server_context::InitializeContext(const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {

      /* create our context*/
         const SSL_METHOD *meth = meth_in != NULL ? meth_in : SSLv3_method();
         m_pcontext = SSL_CTX_new(meth);
         SSL_CTX_set_mode(m_pcontext,SSL_MODE_AUTO_RETRY);
         // session id
         if(context.get_length())
            SSL_CTX_set_session_id_context(m_pcontext,(const uchar *)(const  char *)context,(uint32_t)context.get_length());
         else
            SSL_CTX_set_session_id_context(m_pcontext,(const uchar *)"--is_empty--",9);

      /* Load our keys and certificates*/
         if(!(SSL_CTX_use_certificate_file(m_pcontext,certfile,SSL_FILETYPE_PEM)))
      {
         TRACE(string("tcp_socket InitializeContext(2),0,Couldn't read certificate file ") + keyfile + string("::aura::log::level_fatal"));
      }

      m_password = password;
      SSL_CTX_set_default_passwd_cb(m_pcontext,tcp_socket_SSL_password_cb);
      SSL_CTX_set_default_passwd_cb_userdata(m_pcontext,this);
      if(!(SSL_CTX_use_PrivateKey_file(m_pcontext,keyfile,SSL_FILETYPE_PEM)))
      {
         TRACE(string("tcp_socket InitializeContext(2),0,Couldn't read private key file ") + keyfile + string("::aura::log::level_fatal"));
      }

   }


} // namespace sockets

