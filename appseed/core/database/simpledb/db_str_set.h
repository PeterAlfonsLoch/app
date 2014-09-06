#pragma once


class db_str_sync_queue;

class CLASS_DECL_CORE db_str_set :
   public db_set
{
public:

   class CLASS_DECL_CORE item
   {
   public:

      uint32_t          m_dwTimeout;
      string         m_str;

   };

   class CLASS_DECL_CORE queue_item :
      virtual public element
   {
   public:

      string         m_strKey;
      uint32_t          m_dwTimeout;
      string         m_str;


      queue_item();
      queue_item(const queue_item & item);
      ~queue_item();


      queue_item & operator = (const queue_item & item);


   };




   //mutex                                        m_mutex;
   //sockets::socket_handler                      m_handler;
   //sockets::http_session *                      m_phttpsession;
   string_map < item >            m_map;
   bool                                         m_bIndexed;

   db_str_sync_queue *                                 m_pqueue;

   ::mysql::database *                          m_pmysqldbUser;
   string                                       m_strUser;


   db_str_set(db_server * pserver);
   virtual ~db_str_set();


   bool load(const char * lpKey, string &strValue);
   bool save(const char * lpKey, const char * lpcsz);

   bool remove(const char * lpKey);


};


