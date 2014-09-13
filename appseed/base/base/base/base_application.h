#pragma once


namespace base
{


   class CLASS_DECL_BASE application :
      virtual public :: axis ::application
   {
   public:


      bool                                            m_bBaseProcessInitialize;
      bool                                            m_bBaseProcessInitializeResult;

      bool                                            m_bBaseInitializeInstance;
      bool                                            m_bBaseInitializeInstanceResult;

      bool                                            m_bBaseInitialize1;
      bool                                            m_bBaseInitialize1Result;

      bool                                            m_bBaseInitialize;
      bool                                            m_bBaseInitializeResult;


      ::http::application                             m_http;
      ::file::dir::application                        m_dir;
      ::file::application                             m_file;



      application();
      virtual ~application();




      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner,const char * pszMessage,UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);
      int32_t simple_message_box(const char * pszMessage,UINT fuStyle);
      virtual string message_box(const string & pszMatter,property_set & propertyset);


      virtual string load_string(id id);
      virtual bool load_string(string & str,id id);
      virtual void load_string_table();
      //   virtual string load_string(id id);
      // virtual bool load_string(string & str, id id);
      bool load_cached_string(string & str,id id,bool bLoadStringTable);
      bool load_cached_string_by_id(string & str,id id,const string & pszFallbackValue,bool bLoadStringTable);
      void load_string_table(const string & pszApp,const string & pszId);



      virtual bool is_system();
      virtual bool is_session();
      virtual bool is_serviceable();


      virtual ::user::user * create_user();


      inline class ::http::application &        http()         { return m_http; }
      inline class ::file::dir::application &   dir()          { return m_dir; }
      inline class ::file::application &        file()         { return m_file; }



      virtual bool do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog,sp(::user::impact_system) ptemplate,sp(::user::document) pdocument);



      //virtual bool open_link(const string & strLink,const string & pszTarget = "");









      //// Wall-eeeeee aliases
      //sp(::command_thread) command_central();
      //sp(::command_thread) command_thread();
      //sp(::command_thread) guideline();
      //sp(::command_thread) command();
      //sp(::command_thread) directrix();
      //sp(::command_thread) axiom();
      //sp(::command_thread) creation();





      //virtual void on_allocation_error(const sp(type) info);
      //virtual sp(element) on_alloc(const sp(type) info);

      virtual bool verb();



      //virtual bool app_map_lookup(const char * psz,void * &);
      //virtual void app_map_set(const char * psz,void *);

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();


//      template < class APP >
//      APP & cast_app()
//      {
//         if(this == NULL)
//            return (*(APP *)NULL);
//         void * papp;
//#ifdef WINDOWS
//         if(!app_map_lookup(typeid(APP).name(),papp))
//#else
//         if(!app_map_lookup(typeid(APP).name(), papp))
//#endif
//         {
//            papp = dynamic_cast <APP *> (this);
//#ifdef WINDOWS
//            app_map_set(typeid(APP).name(),papp);
//#else
//            app_map_set(typeid(APP).name(), papp);
//#endif
//         }
//         return (*(APP *)papp);
//      }

      //virtual void _001CloseApplication();


      virtual string get_license_id();


      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();


      //virtual sp(::user::interaction) window_from_os_data(void * pdata);


      virtual void construct(const char * pszAppId);


      virtual bool process_initialize();

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool initialize();
      virtual bool finalize();


      virtual bool is_installing();
      virtual bool is_uninstalling();


      virtual int32_t run();

      virtual bool pre_run();
      virtual int32_t main();
      virtual int32_t on_run();
      virtual int32_t application_pre_run();
      virtual bool initial_check_directrix();
      virtual bool os_native_bergedge_start();

      virtual bool InitApplication();

      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool system_add_app_install(const char * pszId);



      virtual bool update_appmatter(::sockets::http_session * & psession,const char * pszRoot,const char * pszRelative);
      virtual bool update_appmatter(::sockets::http_session * & psession,const char * pszRoot,const char * pszRelative,const char * pszLocale,const char * pszStyle);


      //virtual void TermThread(HINSTANCE hInstTerm);



      //virtual sp(::user::interaction) FindWindow(const char * lpszClassName,const char * lpszWindowName);
      //virtual sp(::user::interaction) FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow);

      //virtual string get_version();

      virtual void SetCurrentHandles();

      //virtual void set_env_var(const string & var,const string & value);
      //virtual uint32_t get_thread_id();


      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::user::document * _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew(signal_details * pobj);

      //virtual sp(::user::printer) get_printer(const char * pszDeviceName);


      //virtual bool update_module_paths();

      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();

      virtual string get_cred(const RECT & rect, string & strUsername,string & strPassword, string strToken, string strTitle, bool bInteractive);

      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);

      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);





      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      //virtual ::visual::icon * set_icon(object * pobject,::visual::icon * picon,bool bBigIcon);
      //virtual ::visual::icon * get_icon(object * pobject,bool bBigIcon) const;

      virtual bool final_handle_exception(::exception::exception & e);



      //service_base * get_service();
      //virtual service_base * allocate_new_service();
      //virtual bool create_new_service();

      //virtual bool create_service();
      //virtual bool remove_service();

      //virtual bool start_service();
      //virtual bool stop_service();


      //virtual void on_service_request(sp(::create_context) pcreatecontext);

      virtual sp(::aura::application) assert_running(const char * pszAppId);

      virtual bool is_running();

      //virtual string get_mutex_name_gen();

      //virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      //virtual void on_exclusive_instance_local_conflict();

      //virtual string get_local_mutex_id();
      //virtual string get_global_mutex_id();

      //virtual ::mutex * get_local_mutex();
      //virtual ::mutex * get_global_mutex();

      //virtual string get_local_mutex_name(const char * pszAppName);
      //virtual string get_local_id_mutex_name(const char * pszAppName,const char * pszId);
      //virtual string get_global_mutex_name(const char * pszAppName);
      //virtual string get_global_id_mutex_name(const char * pszAppName,const char * pszId);

      //virtual string get_local_mutex_name();
      //virtual string get_local_id_mutex_name();
      //virtual string get_global_mutex_name();
      //virtual string get_global_id_mutex_name();

      //virtual bool check_exclusive();
      //virtual bool release_exclusive();

      //virtual void draw2d_factory_exchange();


      //virtual void on_set_scalar(e_scalar escalar,int64_t iValue);
      //virtual void get_scalar_minimum(e_scalar escalar,int64_t & i);
      //virtual void get_scalar(e_scalar escalar,int64_t & i);
      //virtual void get_scalar_maximum(e_scalar escalar,int64_t & i);



      //bool safe_is_running();


      virtual void on_request(sp(::create_context) pcreatecontext);

      //virtual bool defer_initialize_twf();

      // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      // get/set serializables to user directory
      //bool gudo_get(const string & strKey,::file::serializable & obj);
      //bool gudo_set(const string & strKey,::file::serializable & obj);


      virtual bool assert_user_logged_in();

      //virtual bool init_main_data(::aura::main_init_data * pdata);

      //virtual bool set_main_init_data(::aura::main_init_data * pdata);


      virtual void dir_matter_ls_file(const string & str,stringa & stra);
      virtual string matter_as_string(const char * pszMatter,const char * pszMatter2 = NULL);
      virtual string file_as_string(var varFile);
      virtual string file_as_string(var varFile,var & varQuery);
      virtual string dir_matter(const char * pszMatter,const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual bool file_exists(const char * pszPath);
      virtual bool file_is_equal_path(const char * pszPath1,const char * pszPath2);
      virtual bool dir_is(const char * psz);
      virtual bool file_del(const char * psz);
      virtual string file_extension(const char * pszPath);
      virtual string dir_path(const char * psz1,const char * psz2,const char * psz3 = NULL);
      virtual string dir_ca2module(const char * psz = NULL);
      virtual string dir_element(const char * psz = NULL);
      virtual string dir_name(const char * psz);
      virtual void  dir_ls_dir(const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL);
      virtual void  dir_rls(const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,stringa * pstraRelative = NULL);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);
      virtual string file_time_square();
      virtual string dir_userappdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
      virtual string dir_appdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
      virtual string dir_simple_path(const string & str1,const string & str2);

#ifdef APPLEOS

      virtual string dir_pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

#endif


      virtual ::file::buffer_sp file_get_file(var varFile,uint32_t uiFlags);

      virtual string http_get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);


   };








} // namespace base









