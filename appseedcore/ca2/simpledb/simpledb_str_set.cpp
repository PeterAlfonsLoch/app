#include "StdAfx.h"
#include "db_str_set.h"

db_str_set::db_str_set(db_server * pserver) : 
   ca(pserver->get_app()),
   db_set(pserver, "stringtable")
{
   //::simpledb::base * pdb = db()->m_pbase;
   //::simpledb::set *  pds = (::simpledb::set *) pdb->create_dataset();
   ::sqlite::base * pdb = db()->GetImplDatabase();
   ::sqlite::set *  pds = (::sqlite::set *) pdb->CreateDataset();
   
   //create string Table if necessary
   try
   {
      pdb->start_transaction();
      pds->query("select * from sqlite_master where type like 'table' and name like 'stringtable'");
      if (pds->num_rows()==0)
      {
         pds->exec("create table stringtable (id text primary key, value text)");
      }
      pdb->commit_transaction();
   }
   catch (...)
   {
      pdb->rollback_transaction();
      return;
   }

   m_pdataset = pds;

}

db_str_set::~db_str_set()
{

}


// true if deleted
bool db_str_set::remove(const char * lpKey)
{
   UNREFERENCED_PARAMETER(lpKey);
   return false;
}

bool db_str_set::load(const char * lpKey, string & strValue)
{
   if(m_pdataserver == NULL)
      return false;

   single_lock slDatabase(db()->GetImplCriticalSection());

   string strKey;
   strKey = lpKey;
   strKey.replace("'", "''");
   
   string strSql;
   strSql.Format(
      "select value FROM stringtable WHERE id = '%s';",
      strKey);

   
   slDatabase.lock();
   try
   {
      m_pdataset->query(strSql);
   }
   catch(...)
   {
      return false;
   }

   if(m_pdataset->num_rows() <= 0)
      return false;

   strValue = m_pdataset->fv("value");

   return true;
}

bool db_str_set::save(const char * lpKey, const char * lpcsz)
{
   if(db() == NULL)
      return false;
   single_lock slDatabase(db()->GetImplCriticalSection());

   string strKey;
   strKey = lpKey;
   strKey.replace("'", "''");

   string strValue(lpcsz);
   strValue.replace("'", "''");
   
   ::sqlite::base * pdb   = db()->GetImplDatabase();
   string strSql;
   string str;
   slDatabase.lock();
   if(load(lpKey, str))
   {
      strSql.Format(
         "UPDATE stringtable SET value = '%s' WHERE id = '%s';",
         strValue,
         strKey);

      pdb->start_transaction();
      if(!m_pdataset->exec(strSql))
      {
         pdb->rollback_transaction();
         return false;
      }
      pdb->commit_transaction();
   }
   else
   {
   
      strSql.Format(
         "INSERT INTO stringtable (id, value) values ('%s', '%s');",
         strKey,
         strValue);
      
      pdb->start_transaction();
      if(!m_pdataset->exec(strSql))
      {
         pdb->rollback_transaction();
         return false;
      }
      pdb->commit_transaction();
   }
   return true;
}
