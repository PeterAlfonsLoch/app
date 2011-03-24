#pragma once

namespace ca84
{

   class CLASS_DECL_ca application :
      virtual public ca77::application,
      virtual public audWaveCentralContainer,
      virtual public mus::midi_central_container,
      virtual public PlaylistCentralContainer,
      virtual public musctrl::PlayerDocContainer,
      virtual public musctrl::MusicalPlayerCentralContainer,
      virtual public mediamanager::mediamanager_container,
      virtual public ::ca::interface_application < kar::application_interface >,
      virtual public ::ca::interface_application < mixeruserbase::application_interface >
   {
   public:

            bool m_bClientOnly;


      stringa m_straAppInterest;
      ::collection::map < string, string, HWND, HWND > m_mapAppInterest;

      static BOOL CALLBACK GetAppsEnumWindowsProc(      
         HWND hwnd,
         LPARAM lParam);

      void update_app_interest();
      void ensure_app_interest();


      virtual HWND get_ca2_app_wnd(const char * psz);

      application();
      virtual ~application();

      virtual bool initialize();

      virtual bool initialize_instance();

      virtual bool pre_process_command_line();

      virtual bool on_install();
      virtual bool on_uninstall();

      virtual void request(var & varFile, var & varQuery);

      virtual void on_exclusive_instance_local_conflict();

      virtual int send_simple_command(const char * psz, void * osdataSender);
      virtual int send_simple_command(void * osdata, const char * psz, void * osdataSender);
   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca