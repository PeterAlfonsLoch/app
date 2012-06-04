#pragma once


class db_server;


class CLASS_DECL_ca db_long_set :
   public db_set
{
public:


   class CLASS_DECL_ca long_item
   {
   public:

      DWORD          m_dwTimeout;
      int64_t        m_l;

   };


   ::collection::string_map < long_item >       m_map;
   bool                                         m_bIndexed;

   sockets::socket_handler                      m_handler;
   sockets::http_session *                      m_phttpsession;

   

   


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
   bool load(const char * lpKey, WINDOWPLACEMENT & wp);
   bool load(const char * lpKey, LPPOINT lpPoint);

   // save Functions
   template < typename T >
   inline bool save(const char * lpKey, T value)
   {
      
      return save(lpKey, (int64_t) value);

   }

   bool save(const char * lpKey, int64_t lValue);
   bool save(const char * lpKey, LPCRECT lpRect);
   bool save(const char * lpKey, WINDOWPLACEMENT & wp);
   bool save(const char * lpKey, LPPOINT lpPoint);

   // Search Functions
   bool find(const char * lpKey);


   bool MoveWindow_(const char * lpKey, ::ca::window *pWnd);
   bool SaveWindowRect_(const char * lpKey, ::ca::window *pWnd);
   bool SetWindowPlacement(const char * lpKey, ::ca::window *pWnd);
   bool SaveWindowPlacement(const char * lpKey, ::ca::window *pWnd);

};

