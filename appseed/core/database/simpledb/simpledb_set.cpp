#include "framework.h"


db_set::db_set(db_server * pserver, const char * pszTable)
{
   m_pdataserver = pserver;
   sp(::sqlite::base) pdb   = db()->GetImplDatabase();
   if(pdb != NULL) {
   m_pdataset = (sp(::sqlite::set)) pdb->CreateDataset();
   m_strTable = pszTable;}
   
   //create Integer Table if necessary
   /*try
   {
      pdb->start_transaction();
      m_pdataset->query("select * from sqlite_master where type like 'table' and name like '" + m_strTable + "'");
      if (m_pdataset->num_rows()==0)
      {
         m_pdataset->exec("create table integertable (id text primary key, value integer)");
      }
      pdb->commit_transaction();
   }
   catch (...)
   {
      pdb->rollback_transaction();
      return;
   }*/
}

db_set::~db_set()
{

}

db_server * db_set::db()
{
   return dynamic_cast < db_server * > (m_pdataserver);
}



simpledb_set::simpledb_set(db_server * pserver, const char * pszTable)
{
   m_pdataserver = pserver;
   ::simpledb::base * pdb   = db()->m_pbase;
   m_pdataset = (::simpledb::set *) pdb->CreateDataset();
   m_strTable = pszTable;
   
   //create Integer Table if necessary
   /*try
   {
      pdb->start_transaction();
      m_pdataset->query("select * from sqlite_master where type like 'table' and name like '" + m_strTable + "'");
      if (m_pdataset->num_rows()==0)
      {
         m_pdataset->exec("create table integertable (id text primary key, value integer)");
      }
      pdb->commit_transaction();
   }
   catch (...)
   {
      pdb->rollback_transaction();
      return;
   }*/
}

simpledb_set::~simpledb_set()
{

}

db_server * simpledb_set::db()
{
   return dynamic_cast < db_server * > (m_pdataserver);
}
