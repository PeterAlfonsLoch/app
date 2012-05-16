#pragma once


class simple_app
{
public:


   HINSTANCE                  m_hinstance;
   int                        __argc;
   TCHAR **                   __targv;

   MSG                        m_msg;
   int                        m_iReturn;


   simple_app();
   virtual ~simple_app();

   virtual void main();

   virtual bool initialize();
   virtual int run();
   virtual bool finalize();

};


#ifdef WINDOWS


#define IMPLEMENT_SIMPLE_APP_BODY(appclass) \
   \
   initialize_primitive_heap(); \
    \
   if(!os_initialize()) \
      return -1; \
       \
   if(!main_initialize()) \
      return -1; \
       \
   class appclass app; \
    \
   app.main(); \
    \
   main_finalize(); \
    \
   os_finalize(); \
    \
   finalize_primitive_heap(); \


#endif