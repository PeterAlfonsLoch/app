#include "framework.h" // from "base/net/net_sockets.h"


namespace sockets
{


   ssl_server_context_map::ssl_server_context_map(sp(::aura::application) papp) :
      element(papp),
      m_mutex(papp)
   {
   }

   ssl_server_context_map::~ssl_server_context_map()
   {
   }

   SSL_CTX * ssl_server_context_map::InitializeContext(mutex ** ppmutex,const string & context,const string & certfile,const string & keyfile,const string & password,const SSL_METHOD *meth_in)
   {
      synch_lock sl(&m_mutex);
      /* create our context*/
      sp(ssl_server_context) servercontext = operator[](context);
      if(servercontext.is_null())
      {
         servercontext = new ssl_server_context(get_app());
         servercontext->InitializeContext(context,certfile,keyfile,password,meth_in);
         set_at(context, servercontext);
      }
      if(servercontext.is_set())
      {
         *ppmutex =  &servercontext->m_mutex;
         return servercontext->m_pcontext;
      }
      return NULL;
   }

} // namespace sockets

