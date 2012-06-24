#pragma once


class CLASS_DECL_c simple_app
{
public:


   HINSTANCE                  m_hinstance;
   int                        __argc;
   TCHAR **                   __targv;

   MSG                        m_msg;
   int                        m_iError;


   simple_app();
   virtual ~simple_app();

   virtual int main();

   virtual void body();

   virtual bool initialize();
   virtual int run();
   virtual bool finalize();

   template < class APP >
   static int s_main()
   {
      APP app;
      return app.main();
   }

};


