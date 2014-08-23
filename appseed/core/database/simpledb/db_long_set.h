#pragma once


class db_server;


namespace mysql
{
   class database;
}


class CLASS_DECL_CORE db_long_set :
   public db_set
{
public:


   class CLASS_DECL_CORE item
   {
   public:

      uint32_t          m_dwTimeout;
      int64_t        m_l;

   };

   class CLASS_DECL_CORE queue_item :
      virtual public element
   {
   public:

      string         m_strKey;
      uint32_t          m_dwTimeout;
      int64_t        m_l;

      queue_item();
      queue_item(const queue_item & item);
      ~queue_item();


      queue_item & operator = (const queue_item & item);


   };

   class CLASS_DECL_CORE sync_queue :
      public simple_thread
   {
   public:

      mutex                                        m_mutex;
      db_long_set *                                m_pset;
      sockets::socket_handler                      m_handler;
      sockets::http_session *                      m_phttpsession;

      smart_pointer_array < queue_item >                     m_itema;




      
      sync_queue(sp(::aura::application) papp);
      virtual ~sync_queue();


      virtual int32_t run();


      void queue(const char * pszKey, int64_t l);

   };


   mutex                                        m_mutex;
   sockets::socket_handler                      m_handler;
   sockets::http_session *                      m_phttpsession;


   string_map < item >            m_map;
   bool                                         m_bIndexed;

   sync_queue *                                 m_pqueue;
   

   ::mysql::database *                          m_pmysqldbUser;
   string                                       m_strUser;


   db_long_set(db_server * pdatacentral);
   ~db_long_set();



   // load Functions
   template < typename T >
   inline bool load(const char * lpKey, T & rvalue)
   {
      
      int64_t i;

      if(!load(lpKey, &i))
         return false;

      rvalue = (T &) i;

      return true;

   }

   bool load(const char * lpKey, int64_t * lValue);
   bool load(const char * lpKey, LPRECT lpRect);
#ifdef WINDOWSEX
   bool load(const char * lpKey, WINDOWPLACEMENT & wp);
#endif
   bool load(const char * lpKey, LPPOINT lpPoint);

   // save Functions
   template < typename T >
   inline bool save(const char * lpKey, T value)
   {
      
      return save(lpKey, (int64_t) value);

   }

   bool save(const char * lpKey, int64_t lValue);
   bool save(const char * lpKey, LPCRECT lpRect);
#ifdef WINDOWSEX
   bool save(const char * lpKey, WINDOWPLACEMENT & wp);
#endif
   bool save(const char * lpKey, LPPOINT lpPoint);

   // Search Functions
   bool find(const char * lpKey);


   bool MoveWindow_(const char * lpKey, ::window_sp pwindow);
   bool SaveWindowRect_(const char * lpKey, ::window_sp pwindow);
   bool SetWindowPlacement(const char * lpKey, ::window_sp pwindow);
   bool SaveWindowPlacement(const char * lpKey, ::window_sp pwindow);

};

