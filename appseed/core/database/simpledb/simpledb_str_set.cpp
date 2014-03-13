#include "framework.h"
#include "db_str_set.h"

db_str_set::db_str_set(db_server * pserver) :
   element(pserver->get_app()),
   db_set(pserver, "stringtable"),
   m_handler(pserver->get_app()),
   m_mutex(pserver->get_app())
{

   m_pqueue       = NULL;

   m_phttpsession = NULL;

   m_pmysqldbUser = pserver->m_pmysqldbUser;
   m_strUser      = pserver->m_strUser;

//   if((!m_pdataserver->m_bRemote && m_pmysqldbUser == NULL) || Application.fontopus().m_puser)
  // {
      sp(::sqlite::base) pdb = db()->GetImplDatabase();
      //create string Table if necessary
      try
      {
         pdb->start_transaction();
         m_pdataset->query("select * from sqlite_master where type like 'table' and name like 'stringtable'");
         if (m_pdataset->num_rows()==0)
         {
            m_pdataset->exec("create table stringtable (id text primary key, value text)");
         }
         pdb->commit_transaction();
      }
      catch (...)
      {
         pdb->rollback_transaction();
         return;
      }

   //}


}

db_str_set::~db_str_set()
{

}


db_str_set::queue_item::queue_item()
{
}

db_str_set::queue_item::queue_item(const queue_item & item)
{
   operator =(item);
}
db_str_set::queue_item::~queue_item()
{
}


db_str_set::queue_item & db_str_set::queue_item::operator = (const queue_item & item)
{
   if(this != &item)
   {
      m_strKey = item.m_strKey;
      m_dwTimeout = item.m_dwTimeout;
      m_str = item.m_str;
   }
   return *this;
}


db_str_set::sync_queue::sync_queue(sp(base_application) papp) :
   element(papp),
   thread(papp),
   simple_thread(papp),
   m_handler(papp),
   m_mutex(papp)
{
   m_phttpsession = NULL;

   if (papp->m_pbasesession == NULL)
   {
      throw simple_exception(papp, "dbstr_set should have session because it needs a user to indicate the user database");
   }


}

db_str_set::sync_queue::~sync_queue()
{
}



int32_t db_str_set::sync_queue::run()
{

   string strApiServer;

   single_lock sl(&m_mutex, false);

   m_bRun = true;

   try
   {

      while(get_run())
      {

repeat:;

      if(!get_run())
         break;
       {

          sl.lock();

          if(m_itema.get_size() <= 0)
          {
             sl.unlock();
             Sleep(1984);
             goto repeat;
          }

          if(Session.fontopus()->m_puser == NULL)
          {
             sl.unlock();
             Sleep(1984 + 1977);
             goto repeat;
          }

          for(int32_t i = 1; i < m_itema.get_size(); i++)
          {
             if(m_itema[i].m_strKey == m_itema[0].m_strKey)
             {
                m_itema.remove_at(0);
                sl.unlock();
                goto repeat;
             }
          }

          try
          {


             property_set set(get_app());

             string strUrl;

             set["interactive_user"] = true;


             if(strApiServer.is_empty())
             {

                strApiServer = ApplicationUser.get_ca2_server("api");


             }



             strUrl = "https://" + strApiServer +"/account/str_set_save?key=";
             strUrl += System.url().url_encode(m_itema[0].m_strKey);
             strUrl += "&value=";
             strUrl += System.url().url_encode(m_itema[0].m_str);

             m_itema.remove_at(0);

             sl.unlock();

             set["user"] = &ApplicationUser;

             m_phttpsession = System.http().request(m_handler, m_phttpsession, strUrl, set);

             if(m_phttpsession == NULL || ::http::status_failed(set["get_status"]))
             {
                Sleep(1984);
                strApiServer = "";
                goto repeat;
             }

          }
          catch(...)
          {
          }

          sl.unlock();

       }


      }
   }
   catch(...)
   {
   }
   m_pset->m_pqueue = NULL;
   return 0;
}


void db_str_set::sync_queue::queue(const char * pszKey, const char * psz)
{

   single_lock sl(&m_mutex, true);

   sp(queue_item) item(new queue_item);

   item->m_strKey = pszKey;
   item->m_str = psz;

   m_itema.add(item);

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

   if(m_pdataserver->m_bRemote && Application.fontopus()->m_puser != NULL)
   {

      item stritem;

      if(m_map.Lookup(lpKey, stritem) && stritem.m_dwTimeout > get_tick_count())
      {
         strValue = stritem.m_str;
         return true;
      }

      single_lock slDatabase(db()->GetImplCriticalSection(), true);


      property_set set(get_app());

      set["interactive_user"] = true;

      string strUrl;

      strUrl = "https://api.ca2.cc/account/str_set_load?key=";
      strUrl += System.url().url_encode(lpKey);

      set["user"] = &ApplicationUser;

      set["get_response"].m_var = &strValue;

      m_phttpsession = System.http().request(m_handler, m_phttpsession, strUrl, set);

      if(m_phttpsession == NULL || ::http::status_failed(set["get_status"]))
      {
         return false;
      }

      stritem.m_dwTimeout = get_tick_count() + 23 * (1984 + 1977);
      stritem.m_str = strValue;

      m_map.set_at(lpKey, stritem);


   }
#ifndef METROWIN
   else if(m_pmysqldbUser != NULL)
   {

      try
      {

         strValue = m_pmysqldbUser->query_item("SELECT `value` FROM fun_user_str_set WHERE user = '" + m_strUser + "' AND `key` = '" + m_pmysqldbUser->real_escape_string(lpKey) + "'");

         return true;

      }
      catch(...)
      {
      }

      return false;

   }
#endif
   else
   {
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

   }

   return true;
}

bool db_str_set::save(const char * lpKey, const char * lpcsz)
{

   if(m_pdataserver == NULL)
      return false;

   if(!m_pdataserver->m_bRemote)
   {
      if(db() == NULL)
         return false;
      single_lock slDatabase(db()->GetImplCriticalSection());

      string strKey;
      strKey = lpKey;
      strKey.replace("'", "''");

      string strValue(lpcsz);
      strValue.replace("'", "''");

      sp(::sqlite::base) pdb   = db()->GetImplDatabase();
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
#ifdef HAVE_MYSQL
   else if(m_pmysqldbUser != NULL)
   {

      string strSql = "REPLACE INTO fun_user_str_set VALUE('" + m_strUser + "', '" + m_pmysqldbUser->real_escape_string(lpKey) + "', '" + m_pmysqldbUser->real_escape_string(lpcsz) + "')";

      TRACE(strSql);

      return m_pmysqldbUser->query(strSql) != NULL;

   }
#endif
   else
   {


      if(m_pqueue == NULL)
      {

         m_pqueue = new sync_queue(get_app());
         m_pqueue->m_pset = this;
         m_pqueue->begin();

      }


      m_pqueue->queue(lpKey, lpcsz);

      item stritem;

      stritem.m_dwTimeout = get_tick_count() + 23 * (1984 + 1977);
      stritem.m_str = lpcsz;

      m_map.set_at(lpKey, stritem);


      return true;

   }

}
