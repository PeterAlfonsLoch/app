#pragma once


namespace gen
{


   class signal_object;
   class signal;


} // namespace gen


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


   class cube;


}

namespace plane
{


   class application;
   class system;


}


namespace fontopus
{


   class user;


} // namespace fontopus


namespace cube
{

   class application;

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


   // Carlos Gustavo Cecyn Lundgren
   class CLASS_DECL_ca application :
      virtual public ::ca::live_object
   {
   public:


      gen::signal                 * m_psignal;

      bool                          m_bInitializeProDevianMode;
      main_init_data *              m_pinitmaindata;
      bool                          m_bService;
      ::plane::application *        m_pappThis;
      ::cube::application *         m_pappCube;
      bool                          m_bZipIsDir;
      ::plane::system *             m_psystem;
      ::plane::session *            m_psession;


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

      virtual int32_t exit();

      virtual bool finalize();

      virtual int32_t exit_instance();

      virtual int32_t main();

      virtual application * get_app() const;

      virtual bool is_system();
      virtual bool is_session();

      virtual bool is_cube();
      virtual bool is_bergedge();

      virtual bool is_installing();
      virtual bool is_uninstalling();

      virtual bool is_serviceable();

      virtual bool app_map_lookup(const char * psz, void * &) = 0;
      virtual void app_map_set(const char * psz, void *) = 0;


      virtual void pre_translate_message(::gen::signal_object * pobj) = 0;


      virtual ::fontopus::user * get_safe_user();


      template < class APP >
      APP & cast_app()
      {
         if(this == NULL)
            return (*(APP *) NULL);
         void * papp;
         #ifdef WINDOWS
         if(!app_map_lookup(typeid(APP).name(), papp))
         #else
         if(!app_map_lookup(typeid(APP).name(), papp))
         #endif
         {
            papp = dynamic_cast < APP * > (this);
            #ifdef WINDOWS
            app_map_set(typeid(APP).name(), papp);
            #else
            app_map_set(typeid(APP).name(), papp);
            #endif
         }
         return (*(APP *) papp);
      }

   };


   inline application & get(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }



} // namespace ca

