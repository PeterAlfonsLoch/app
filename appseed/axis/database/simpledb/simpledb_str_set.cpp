//#include "framework.h"
//#include "axis/net/net_sockets.h"
//#include "db_str_set.h"
#include "sqlite3.h"

class CLASS_DECL_AXIS db_str_set_item
{
public:


   uint32_t          m_dwTimeout;
   string            m_str;


};


class CLASS_DECL_AXIS db_str_set_queue_item :
   virtual public object
{
public:

   string            m_strKey;
   uint32_t          m_dwTimeout;
   string            m_str;


   db_str_set_queue_item() {}
   db_str_set_queue_item(const db_str_set_queue_item & item) { operator =(item); }
   virtual ~db_str_set_queue_item() {  }


   db_str_set_queue_item & operator = (const db_str_set_queue_item & item)
   {
      if (this != &item)
      {
         m_strKey = item.m_strKey;
         m_dwTimeout = item.m_dwTimeout;
         m_str = item.m_str;
      }
      return *this;
   }



};


class CLASS_DECL_AXIS db_str_set_core :
   virtual public ::db_set
{
public:


   sockets::socket_handler                      m_handler;
   sp(sockets::http_session)                    m_phttpsession;
   string_map < db_str_set_item >               m_map;
   bool                                         m_bIndexed;
   ::simpledb::database *                          m_psimpledbUser;
   string                                       m_strUser;

   sp(class db_str_sync_queue)                    m_pqueue;
   sqlite3_stmt *                               m_pstmtSelect;
   sqlite3_stmt *                               m_pstmtUpdate;





   db_str_set_core(db_server * pserver) :
      ::object(pserver->get_app()),
      db_set(pserver, "stringtable"),
      m_handler(get_app()),
      m_phttpsession(NULL),
      m_pqueue(NULL),
      m_psimpledbUser(pserver->m_psimpledbUser),
      m_strUser(pserver->m_strUser)
   {
      m_pstmtSelect = NULL;
      m_pstmtUpdate = NULL;
      m_ptopthis = this;
      defer_create_mutex();

   }

   ~db_str_set_core()
   {
      if (m_pstmtSelect != NULL)
      {

         sqlite3_finalize(m_pstmtSelect);
         m_pstmtSelect = NULL;
      }
      if (m_pstmtUpdate != NULL)
      {

         sqlite3_finalize(m_pstmtUpdate);
         m_pstmtUpdate = NULL;
      }
   }


};


class CLASS_DECL_AXIS db_str_sync_queue :
   public simple_thread
{
public:

   mutex                                              m_mutex;
   db_str_set *                                       m_pset;
   sockets::socket_handler                            m_handler;
   sp(sockets::http_session)                          m_phttpsession;

   smart_pointer_array < db_str_set_queue_item >      m_itema;


   db_str_sync_queue(::aura::application * papp) :
      ::object(papp),
      thread(papp),
      simple_thread(papp),
      m_handler(papp),
      m_mutex(papp),
      m_phttpsession(NULL)
   { }

   virtual ~db_str_sync_queue() {}


   virtual int32_t run();

   void queue(const char * pszKey, const char * psz);

};






int32_t db_str_sync_queue::run()
{

   single_lock sl(&m_mutex, false);

   try
   {

      while (get_run_thread())
      {

         if (&ApplicationUser == NULL)
         {

            Sleep(5000);

            continue;

         }

         sl.lock();

         if (m_itema.is_empty())
         {

            sl.unlock();

            Sleep(100);

            continue;

         }

         for (int32_t i = 1; i < m_itema.get_size(); i++)
         {

            if (m_itema[i]->m_strKey == m_itema[0]->m_strKey)
            {

               m_itema.remove_at(0);

               sl.unlock();

               continue;

            }

         }

         sp(db_str_set_queue_item) pitem = m_itema[0];

         m_itema.remove_at(0);

         sl.unlock();

         try
         {

            property_set set(get_app());

            string strUrl;

            set["interactive_user"] = true;

            strUrl = "https://" + System.dir().get_api_cc() + "/account/str_set_save?key=";

            strUrl += System.url().url_encode(pitem->m_strKey);

            strUrl += "&value=";

            strUrl += System.url().url_encode(pitem->m_str);

            set["user"] = &ApplicationUser;

            {

               single_lock slDatabase(m_pset->m_pcore->db()->get_database()->m_pmutex, true);

               Application.http().get(strUrl, set);

            }

            if (::http::status_failed(set["get_status"]))
            {

               Sleep(500);

               System.dir().m_strApiCc = "";

            }

         }
         catch (...)
         {

         }

      }

   }
   catch (...)
   {

   }
   
   ((db_str_set_core *)(m_pset->m_pcore->m_ptopthis))->m_pqueue = NULL;

   return 0;

}


void db_str_sync_queue::queue(const char * pszKey, const char * psz)
{

   single_lock sl(&m_mutex, true);

   sp(db_str_set_queue_item) item(canew(db_str_set_queue_item));

   item->m_strKey = pszKey;
   item->m_str = psz;

   m_itema.add(item);

}


db_str_set::db_str_set(db_server * pserver) :
   ::object(pserver->get_app())
{

   defer_create_mutex();
   m_pcore = canew(db_str_set_core(pserver));

}

db_str_set::~db_str_set()
{

}




// true if deleted
bool db_str_set::remove(const string & strKey)
{

   UNREFERENCED_PARAMETER(strKey);

   return false;

}


bool db_str_set::load(const string & strKey, string & strValue)
{

   synch_lock sl(m_pmutex);

   db_str_set_core * pcore = (db_str_set_core *)m_pcore->m_ptopthis;

   if (m_pcore->m_pdataserver == NULL)
   {

      return false;

   }

   if (m_pcore->m_pdataserver->m_bRemote && strKey.find(".local://") < 0)
   {

      // Remote

      sl.unlock();

      Application.assert_user_logged_in();

      sl.lock();

      auto it = pcore->m_map.find_first(strKey);

      if (it != pcore->m_map.end() && it->m_element2.m_dwTimeout > get_tick_count())
      {

         strValue = it->m_element2.m_str;

         return true;

      }

      sl.unlock();

      //single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex,true);

      //string xxx;
      //
      //if (&Session != NULL)
      //{
      //   
      //   if (Session.fontopus())
      //   {

      //      if (Session.fontopus()->m_puser != NULL)
      //      {

      //         xxx = Session.fontopus()->m_puser->m_strFontopusServerSessId;

      //      }

      //   }

      //}

      {

         property_set set(get_app());

         set["interactive_user"] = true;

         string strUrl;

         strUrl = "https://" + System.dir().get_api_cc() + "/account/str_set_load?key=";

         strUrl += System.url().url_encode(strKey);

         set["user"] = &ApplicationUser;

         {

            //single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex, true);

            strValue = Application.http().get(strUrl, set);

         }

         if (strValue.is_empty() || ::http::status_failed(set["get_status"]))
         {

            return false;

         }

      }

      {

         db_str_set_item stritem;

         stritem.m_dwTimeout = get_tick_count() + 23 * (5000);
         stritem.m_str = strValue;

         sl.lock();

         pcore->m_map.set_at(strKey, stritem);

      }


   }
#ifndef METROWIN
   else if (pcore->m_psimpledbUser != NULL)
   {

      try
      {

         strValue = pcore->m_psimpledbUser->query_item("SELECT `value` FROM fun_user_str_set WHERE user = '" + pcore->m_strUser + "' AND `key` = '" + pcore->m_psimpledbUser->real_escape_string(strKey) + "'");

         return true;

      }
      catch (...)
      {
      }

      return false;

   }
#endif
   else
   {

      // LOCAL (sqlite)

      sp(::sqlite::base) pdb = m_pcore->db()->get_database();

      //      ::sqlite::base * pdatabase = pdb->get_database();

      mutex * pmutex = pdb->m_pmutex;

      sl.unlock();

      synch_lock slDatabase(pmutex);

      if (pcore->m_pstmtSelect == NULL)
      {


         if (pdb->setErr(sqlite3_prepare_v2(
            (sqlite3 *)pdb->getHandle(),
            "select value FROM stringtable WHERE id = :id;",
            -1,
            &pcore->m_pstmtSelect, NULL)) != SQLITE_OK)
         {

            return false;

         }

      }
      else
      {

         sqlite3_reset(pcore->m_pstmtSelect);

      }


      int index = sqlite3_bind_parameter_index(pcore->m_pstmtSelect, ":id");
      if (index == 0)
         return false;

      int res = sqlite3_bind_text(pcore->m_pstmtSelect, index, strKey, strKey.get_length(), SQLITE_TRANSIENT);
      if (res != SQLITE_OK)
         return false;

      res = sqlite3_step(pcore->m_pstmtSelect);


      if (res != SQLITE_ROW)
      {

         return false;

      }

      const char * psz = (const char *)sqlite3_column_text(pcore->m_pstmtSelect, 0);

      strsize iLen = sqlite3_column_bytes(pcore->m_pstmtSelect, 0);

      strValue = string(psz, iLen);
      //TRACE("value=%s\n", strValue);
      //slDatabase.lock();
      //try
      //{
      //   m_pcore->m_pdataset->query(strSql);
      //}
      //catch(...)
      //{
      //   return false;
      //}

      //if(m_pcore->m_pdataset->num_rows() <= 0)
      //   return false;

      //strValue = m_pcore->m_pdataset->fv("value");

   }

   return true;
}


bool db_str_set::save(const string & strKey, const string & strValue)
{

   db_str_set_core * pcore = (db_str_set_core *)m_pcore->m_ptopthis;

   if (m_pcore->m_pdataserver == NULL)
   {

      return false;

   }

   if (!m_pcore->m_pdataserver->m_bRemote || strKey.find(".local://") >= 0)
   {

      if (m_pcore->db() == NULL)
      {

         return false;

      }

      sp(::sqlite::base) pdb = m_pcore->db()->get_database();

      string strSql;

      string str;

      string_map < db_str_set_item >::pair * pitem = NULL;

      {

         synch_lock sl(m_pmutex);

         pcore->m_map.find_first(strKey);

      }

      string strLoad;

      if (pitem != NULL || load(strKey, strLoad))
      {

         synch_lock sl(m_pmutex);

         if (pitem != NULL)
         {

            if (pitem->m_element2.m_str == strValue)
            {

               return true;

            }

         }
         else
         {

            if (strLoad == strValue)
            {

               return true;

            }

         }

         {

            single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex);

            if (pcore->m_pstmtUpdate == NULL)
            {

               if (pdb->setErr(
                  sqlite3_prepare_v2(
                  (sqlite3 *)pdb->getHandle(),
                     "UPDATE stringtable SET value = :val WHERE id = :id;",
                     -1,
                     &pcore->m_pstmtUpdate,
                     NULL)) != SQLITE_OK)
               {

                  return false;

               }

            }
            else
            {



               sqlite3_reset(pcore->m_pstmtUpdate);

            }

            int index = sqlite3_bind_parameter_index(pcore->m_pstmtUpdate, ":val");

            if (index == 0)
               return false;

            int res = sqlite3_bind_text(pcore->m_pstmtUpdate, index, strValue, strValue.get_length(), SQLITE_TRANSIENT);
            if (res != SQLITE_OK)
               return false;

            index = sqlite3_bind_parameter_index(pcore->m_pstmtUpdate, ":id");
            if (index == 0)
               return false;

            res = sqlite3_bind_text(pcore->m_pstmtUpdate, index, strKey, strKey.get_length(), SQLITE_TRANSIENT);
            if (res != SQLITE_OK)
               return false;

            res = sqlite3_step(pcore->m_pstmtUpdate);

            if (res != SQLITE_OK && res != SQLITE_DONE)
            {

               return false;

            }

         }

         if (pitem == NULL)
         {

            db_str_set_item stritem;

            stritem.m_dwTimeout = get_tick_count() + 23 * (5000);
            stritem.m_str = strValue;

            synch_lock sl(m_pmutex);

            pcore->m_map.set_at(strKey, stritem);

         }
         else
         {

            pitem->m_element2.m_dwTimeout = get_tick_count() + 23 * (5000);

         }


      }
      else
      {

         single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex);

         strSql.Format(
            "INSERT INTO stringtable (id, value) values ('%s', '%s');",
            strKey,
            strValue);

         if (!m_pcore->m_pdataset->exec(strSql))
         {

            return false;

         }

      }

      return true;

   }
#ifdef HAVE_MYSQL
   else if (pcore->m_psimpledbUser != NULL)
   {

      string strSql = "REPLACE INTO fun_user_str_set VALUE('" + pcore->m_strUser + "', '" + pcore->m_psimpledbUser->real_escape_string(strKey) + "', '" + pcore->m_psimpledbUser->real_escape_string(strKey) + "')";

      TRACE(strSql);

      return pcore->m_psimpledbUser->query(strSql) != NULL;

   }
#endif
   else
   {

      if (pcore->m_pqueue == NULL)
      {

         pcore->m_pqueue = canew(db_str_sync_queue(get_app()));

         pcore->m_pqueue->m_pset = this;

         pcore->m_pqueue->begin();

      }

      pcore->m_pqueue->queue(strKey, strValue);

      db_str_set_item stritem;

      stritem.m_dwTimeout = get_tick_count() + 23 * (5000);

      stritem.m_str = strValue;

      synch_lock sl(m_pmutex);

      pcore->m_map.set_at(strKey, stritem);

      return true;

   }

}

