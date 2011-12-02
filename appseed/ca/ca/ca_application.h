#pragma once


namespace user
{
   class interaction;
}


namespace bergedge
{
   class bergedge;
}

namespace cube
{
   class system;
}

namespace plane
{
   class system;
}

namespace ca
{


   class type_info;
   class system;
   class window_draw;

   enum e_application_signal
   {
      application_signal_initialize1, // cgcl // first initialization
      application_signal_initialize2, // cst  // second initialization
      application_signal_initialize3, // third initialization and so on...
      application_signal_initialize, // last initialization
      application_signal_start,
      application_signal_process_initialize,
      application_signal_finalize,
      application_signal_exit_instance,
      application_signal_init_application,
      application_signal_none,
   };


   template < class T >
   type_info & get_type_info();


   // Carlos Gustavo Cecyn Lundgren
   class CLASS_DECL_ca application :
      virtual public ::ca::live_object
   {
   public:


      bool                          m_bInitializeProDevianMode;
      main_init_data *              m_pinitmaindata;
      bool                          m_bService;


      application();
      virtual ~application();


      virtual bool init_main_data(main_init_data * pdata);
      virtual bool set_main_init_data(main_init_data * pdata);

      virtual void construct(const char * pszId);

      virtual bool process_initialize();

      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();

      virtual int exit();

      virtual bool finalize();

      virtual int exit_instance();

      virtual int main();

      virtual application * get_app() const;

      virtual bool is_system();
      virtual bool is_bergedge();


      virtual bool app_map_lookup(const char * psz, void * &) = 0;
      virtual void app_map_set(const char * psz, void *) = 0;


      template < class APP >
      APP & cast_app()
      {
         if(this == NULL)
            return (*(APP *) NULL);
         void * papp;
         if(!app_map_lookup(::ca::get_type_info < APP > ().raw_name(), papp))
         {
            papp = dynamic_cast < APP * > (this);
            app_map_set(::ca::get_type_info < APP > ().raw_name(), papp);
         }
         return (*(APP *) papp);
      }

   };


   inline application & get(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }



} // namespace ca

