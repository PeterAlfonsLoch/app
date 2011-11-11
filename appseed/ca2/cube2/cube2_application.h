#pragma once


namespace cube2
{


   class CLASS_DECL_ca application :
      virtual public cube1::application,
      virtual public audWaveCentralContainer,
      virtual public mus::midi_central_container,
      virtual public mediaplaylist::central_container,
      virtual public musctrl::PlayerDocContainer,
      virtual public musctrl::MusicalPlayerCentralContainer,
      virtual public mediamanager::mediamanager_container,
      virtual public ::ca::interface_application < kar::application_interface >,
      virtual public ::ca::interface_application < mixeruserbase::application_interface >      
   {
   public:


      stringa m_straAppInterest;
      ::collection::map < string, string, HWND, HWND > m_mapAppInterest;


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);

      void update_app_interest();
      void ensure_app_interest();


      virtual HWND get_ca2_app_wnd(const char * psz);

      application();
      virtual ~application();

      virtual bool initialize();

      virtual bool initialize_instance();

      virtual bool on_install();
      virtual bool on_uninstall();

      using cube1::application::request;
      virtual void request(::ca::create_context * pcreatecontext);

      virtual void on_exclusive_instance_local_conflict();

      virtual int send_simple_command(const char * psz, void * osdataSender);
      virtual int send_simple_command(void * osdata, const char * psz, void * osdataSender);
   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace ca

