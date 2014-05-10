#include "framework.h"


namespace simpledb
{

   server::server(sp(::base::application) papp) :
      element(papp)
   {
      m_pbase = NULL;
   }

   server::~server()
   {
   }

   bool server::open(const char * pszDatabase)
   {
      if(m_pbase != NULL)
         close();
      class base * pbase = new class base(get_app());
      if(pbase == NULL)
         return false;
      pbase->setDatabase(pszDatabase);
      if(pbase->connect())
      {
         delete pbase;
         return false;
      }
      m_pbase = pbase;
      return true;
   }

   bool server::close()
   {
      if(m_pbase == NULL)
         return true;
      m_pbase->disconnect();
      delete m_pbase;
      m_pbase = NULL;
      return true;
   }

   bool server::sql(const char * pszQuery, var & var)
   {
      if(m_pbase == NULL)
         return false;
      class ::simpledb::set * pset     = m_pbase->create_dataset();
      pset->exec(pszQuery);
      var.propset()["::database::result_set"] = &pset->m_resultset;
      return true;
   }


} // namespace simpledb


