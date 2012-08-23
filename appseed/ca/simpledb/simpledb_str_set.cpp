#include "framework.h"
#include "db_str_set.h"

db_str_set::db_str_set(db_server * pserver) : 
   ca(pserver->get_app()),
   db_set(pserver, "stringtable"),
   m_handler(pserver->get_app())
{
   m_pqueue = NULL;
   //::simpledb::base * pdb = db()->m_pbase;
   //::simpledb::set *  pds = (::simpledb::set *) pdb->create_dataset();
   ::sqlite::base * pdb = db()->GetImplDatabase();
   ::sqlite::set *  pds = (::sqlite::set *) pdb->CreateDataset();
   
   m_phttpsession = NULL;

   if(!m_pdataserver->m_bRemote)
   {

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

   }

   m_pdataset = pds;

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


db_str_set::sync_queue::sync_queue(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp),
   m_handler(papp)
{
   m_phttpsession = NULL;


}

db_str_set::sync_queue::~sync_queue()
{
}



int db_str_set::sync_queue::run()
{

   string strApiServer;

   try
   {

      while(true)
      {

   repeat:;

         {

            single_lock sl(&m_mutex, true);

            if(m_itema.get_size() <= 0)
            {
               Sleep(1984);
               goto repeat;
            }

            if(&ApplicationUser == NULL)
            {
               Sleep(1984 + 1977);
               goto repeat;
            }

            for(int i = 1; i < m_itema.get_size(); i++)
            {
               if(m_itema[i].m_strKey == m_itema[0].m_strKey)
               {
                  m_itema.remove_at(0);
                  goto repeat;
               }
            }

            try
            {

               gen::property_set post(get_app());
               gen::property_set headers(get_app());
               gen::property_set set(get_app());

               ca4::http::e_status estatus;

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


               m_phttpsession = System.http().request(m_handler, m_phttpsession, strUrl, post, headers, set, NULL, &ApplicationUser, NULL, &estatus);

               if(m_phttpsession == NULL || estatus != ca4::http::status_ok)
               {
                  Sleep(1984);
                  strApiServer = "";
                  goto repeat;
               }

            }
            catch(...)
            {
            }


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

   queue_item item;

   item.m_strKey = pszKey;
   item.m_str = psz;

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

   if(m_pdataserver->m_bRemote)
   {
   
      item stritem;

      if(m_map.Lookup(lpKey, stritem) && stritem.m_dwTimeout > GetTickCount())
      {
         strValue = stritem.m_str;
         return true;
      }
   

      gen::property_set post(get_app());
      gen::property_set headers(get_app());
      gen::property_set set(get_app());

      ca4::http::e_status estatus;

      set["interactive_user"] = true;

      string strUrl;

      strUrl = "https://api.ca2.cc/account/str_set_load?key=";
      strUrl += System.url().url_encode(lpKey);

      m_phttpsession = System.http().request(m_handler, m_phttpsession, strUrl, post, headers, set, NULL, &ApplicationUser, NULL, &estatus);

      if(m_phttpsession == NULL || estatus != ca4::http::status_ok)
      {
         return false;
      }

      strValue = string((const char *) m_phttpsession->m_memoryfile.get_memory()->get_data(),
                        m_phttpsession->m_memoryfile.get_memory()->get_size());


      stritem.m_dwTimeout = GetTickCount() + 23 * (1984 + 1977);
      stritem.m_str = strValue;

      m_map.set_at(lpKey, stritem);


   }
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
   else
   {


      if(m_pqueue == NULL)
      {
         
         m_pqueue = new sync_queue(get_app());
         m_pqueue->m_pset = this;
         m_pqueue->Begin();

      }


      m_pqueue->queue(lpKey, lpcsz);

      item stritem;

      stritem.m_dwTimeout = GetTickCount() + 23 * (1984 + 1977);
      stritem.m_str = lpcsz;

      m_map.set_at(lpKey, stritem);


      return true;

   }

}
