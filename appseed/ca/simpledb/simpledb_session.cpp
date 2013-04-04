#include "framework.h"


namespace simpledb
{

   session::session(::ca::application * papp) :
      ::ca::ca(papp)
   {
      m_pserver = ::null();
   }

   session::~session()
   {
   }

   bool session::open(const char * pszDatabase)
   {
      if(m_pserver != ::null())
         close();
      server * pserver = new server(get_app());
      if(pserver == ::null())
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
      if(m_pserver == ::null())
         return true;
      delete m_pserver;
      m_pserver = ::null();
      return true;
   }

   bool session::query(const char * pszQuery, var & var)
   {
      stringa stra;
      ::ca::property_set set(get_app());
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


