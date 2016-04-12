#pragma once



class CLASS_DECL_CORE db_long_set :
   virtual public ::object
{
public:


   class db_long_set_core *            m_pcore;


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

