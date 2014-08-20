#include "framework.h"


namespace simpledb
{

   session::session(sp(::axis::application) papp) :
      element(papp)
   {
      m_pserver = NULL;
   }

   session::~Session
   {
   }

   bool session::open(const char * pszDatabase)
   {
      if(m_pserver != NULL)
         close();
      server * pserver = new server(get_app());
      if(pserver == NULL)
         return false;
      if(!pserver->open(pszDatabase))
      {
         delete pserver;
         return false;
      }
      m_pserver = pserver;
      return true;
   }

   bool session::close()
   {
      if(m_pserver == NULL)
         return true;
      delete m_pserver;
      m_pserver = NULL;
      return true;
   }

   bool session::query(const char * pszQuery, var & var)
   {
      stringa stra;
      property_set set(get_app());
      set.parse_url_query(pszQuery);
      if(set["command"] == "open")
      {
         var = open(set["database"]);
      }
      else if(set["command"] == "sql")
      {
         if(!m_pserver->sql(pszQuery, var))
            var = false;
      }
      else if(set["command"] == "close")
      {
         var = close();
      }
      return true;
   }


} // namespace simpledb


