#pragma once


class db_server;


class CLASS_DECL_ca db_long_set :
   public db_set
{
protected:


   bool                    m_bIndexed;


public:


   db_long_set(db_server * pdatacentral);
   ~db_long_set();



   // load Functions
   bool load(const char * lpKey, long *lValue);
   bool load(const char * lpKey, int &lValue);
   bool load(const char * lpKey, LPRECT lpRect);
   bool load(const char * lpKey, WINDOWPLACEMENT & wp);
   bool load(const char * lpKey, LPPOINT lpPoint);

   // save Functions
   bool save(const char * lpKey, long lValue);
   bool save(const char * lpKey, int lValue);
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

