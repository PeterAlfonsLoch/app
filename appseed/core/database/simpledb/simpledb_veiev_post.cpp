#include "framework.h"

veiev_post::veiev_post(db_server * pserver) :
   db_set(pserver, "veiev_post")
{
   sp(::sqlite::base) pdb = db()->get_database();
   sp(::sqlite::set)  pds = (sp(::sqlite::set)) pdb->CreateDataset();

   //create string Table if necessary
   pdb->start_transaction();
   pds->query("select * from sqlite_master where type like 'table' and name like 'veiev_post'");
   if (pds->num_rows()==0)
   {
      if(!pds->exec("create table veiev_post (sender text, recipient text, sent integer, datetime text, `index` integer, message text, PRIMARY KEY (sender, datetime, `index`))"))
      {
         pdb->rollback_transaction();
         return;
      }
      pdb->commit_transaction();
   }

   m_pdataset = pds;

}

veiev_post::~veiev_post()
{
}

bool veiev_post::write(var rec)
{

   sp(::sqlite::base) pdb = db()->get_database();

   single_lock slDatabase(pdb->m_pmutex);

   string strMessage;

   strMessage = rec["message"];

   strMessage.replace("'", "''");

   string strSql;

   strSql.Format(
      "insert into veiev_post (`sender`, `recipient`, `sent`, `datetime`, `index`, `message`) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');",
      rec["sender"].get_string(),
      rec["recipient"].get_string(),
      rec["sent"].get_string(),
      rec["datetime"].get_string(),
      rec["index"].get_string(),
      strMessage);

   slDatabase.lock();

   pdb->start_transaction();

   if(!m_pdataset->exec(strSql))
   {

      pdb->rollback_transaction();

      return false;

   }

   pdb->commit_transaction();

   return true;

}


var veiev_post::last()
{

   if(m_pdataserver == NULL)
      return false;

   sp(::sqlite::base) pdb = db()->get_database();

   single_lock slDatabase(pdb->m_pmutex);

   string strSql;

   strSql = "select * FROM veiev_post ORDER BY `datetime`DESC, `index` DESC LIMIT 1";

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

   m_pdataset->first();

   return current();

}


var veiev_post::current()
{

   var ret;

   ret.set_type(var::type_propset);
   ret["sender"]     = m_pdataset->fv("sender");
   ret["recipient"]  = m_pdataset->fv("recipient");
   ret["sent"]       = m_pdataset->fv("sent");
   ret["datetime"]   = m_pdataset->fv("datetime");
   ret["index"]      = m_pdataset->fv("index");
   ret["message"]    = m_pdataset->fv("message");

   return ret;

}


var veiev_post::get_page(::index iPage, ::index iMessageCountPerPage)
{

   if(m_pdataserver == NULL)
      return false;

   sp(::sqlite::base) pdb = db()->get_database();

   single_lock slDatabase(pdb->m_pmutex);

   class var var;

   string strSql;

   strSql.Format(
      "select * FROM veiev_post ORDER BY datetime DESC, `index` DESC LIMIT %d, %d",
      iPage * iMessageCountPerPage,
      iMessageCountPerPage);

   slDatabase.lock();

   try
   {

      m_pdataset->query(strSql);

   }
   catch(...)
   {

      return false;

   }

   ::count iNumRows = m_pdataset->num_rows();

   if(iNumRows <= 0)
      return false;

   while(!m_pdataset->eof())
   {

      var.vara().add(current());

      m_pdataset->next();

   }

   return var;

}


int64_t veiev_post::get_count()
{

   if(m_pdataserver == NULL)
      return 0;

   sp(::sqlite::base) pdb = db()->get_database();

   single_lock slDatabase(pdb->m_pmutex);

   class var var;

   string strSql;

   strSql = "select COUNT(*) as ::count FROM veiev_post";

   slDatabase.lock();

   try
   {

      m_pdataset->query(strSql);

   }
   catch(...)
   {

      return 0;

   }

   if(m_pdataset->num_rows() <= 0)
      return 0;

   m_pdataset->first();

   return m_pdataset->fv("count");

}








































