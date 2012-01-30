#pragma once


namespace cube2
{


   class CLASS_DECL_ca2 application :
      virtual public ::cube1::application
   {
   public:


      stringa m_straAppInterest;
      ::collection::string_map < HWND, HWND > m_mapAppInterest;


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);

      void update_app_interest();
      void ensure_app_interest();


      virtual HWND get_ca2_app_wnd(const char * psz);

      application();
      virtual ~application();

      virtual bool initialize();

      virtual bool initialize_instance();

      using cube1::application::request;
      virtual void request(::ca::create_context * pcreatecontext);

      virtual void on_exclusive_instance_local_conflict();

      virtual int send_simple_command(const char * psz, void * osdataSender);
      virtual int send_simple_command(void * osdata, const char * psz, void * osdataSender);




   };



} // namespace ca



