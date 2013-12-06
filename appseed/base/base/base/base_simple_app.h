#pragma once


class CLASS_DECL_BASE simple_app :
   virtual public base_system
{
public:


   //HINSTANCE                  m_hinstance;
   int32_t                        __argc;
   TCHAR **                   __targv;

   MESSAGE                    m_msg;
   int32_t                        m_iError;


   simple_app();
   virtual ~simple_app();

   virtual int32_t main();

   virtual void body();

   virtual bool initialize();
   virtual int32_t run();
   virtual bool finalize();

   template < class APP >
   static int32_t s_main()
   {
      APP app;
      return app.main();
   }

};


