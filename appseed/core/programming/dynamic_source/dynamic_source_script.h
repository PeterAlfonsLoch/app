#pragma once


namespace dynamic_source
{

   class script;
   class script_instance;
   class script_manager;

   typedef   script_instance * (*NET_NODE_CREATE_INSTANCE_PROC)(script * pscript);


   class CLASS_DECL_CORE script :
      virtual public ::object
   {
   public:


      sp(script_manager)                        m_pmanager;
      string                                    m_strName;
      mutex                                     m_mutex;
      file::plain_text_stream_memory_buffer     m_memfileError;

      spa(script_instance)                      m_scriptinstanceptra;


      script(sp(::axis::application) papp);
      virtual ~script();


      virtual script_instance * create_instance() = 0;

      virtual void run(script_instance * pinstance);

   };


   class CLASS_DECL_CORE ds_script :
      virtual public script
   {
   public:


      ::axis::library                  m_library;


#ifdef WINDOWS
      FILETIME                         m_ftCreation;
      FILETIME                         m_ftModified;
#else
      __time_t                         m_ftCreation;
      __time_t                         m_ftAccess;
      __time_t                         m_ftModified;
#endif
      
      bool                             m_bLastVersionCheck;
      uint32_t                         m_dwLastVersionCheck;
      string                           m_strSourcePath;
      string                           m_strSourceDir;
      string                           m_strCppPath;
      string                           m_strScriptPath;
      string                           m_strBuildBat;
      manual_reset_event               m_evCreationEnabled;
      uint32_t                         m_dwLastBuildTime;
      bool                             m_bShouldBuild;
      bool                             m_bCalcHasTempError;
      bool                             m_bHasTempError;
      bool                             m_bHasTempOsError;



      ds_script(sp(::axis::application) papp);
      ~ds_script();



      NET_NODE_CREATE_INSTANCE_PROC m_lpfnCreateInstance;

      

      virtual void on_start_build();

      bool DoesMatchVersion();
      bool ShouldBuild();
      bool HasCompileOrLinkError();
      bool HasTempError(bool bLock = true);
      bool CalcHasTempError(bool bLock = true);
      bool HasTimedOutLastBuild();
      void Load(bool bLock);
      void Unload(bool bLock);

      string get_stage_path();


      sp(::axis::application) get_app() const;

      script_instance * create_instance();


   };

   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script(sp(::axis::application) papp) : 
         element(papp),
         script(papp)
      {
      };


      virtual script_instance * create_instance()
      {
         return new T(this);
      }

   };


} // namespace dynamic_source


