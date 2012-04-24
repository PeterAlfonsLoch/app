#pragma once


namespace dynamic_source
{

   class script;
   class script_instance;
   class script_manager;

   typedef   script_instance * (*NET_NODE_CREATE_INSTANCE_PROC)(script * pscript);


   class CLASS_DECL_ca script :
      virtual public ::radix::object
   {
   public:


      script_manager *        m_pmanager;
      string                  m_strName;
      mutex                   m_mutex;
      http::memory_file       m_memfileError;

      comparable_array < script_instance * > m_scriptinstanceptra;


      script(::ca::application * papp);
      virtual ~script();


      virtual script_instance * create_instance() = 0;

      virtual void run(script_instance * pinstance);

   };


   class CLASS_DECL_ca ds_script :
      virtual public script
   {
   public:


      ::ca::library           m_library;
      __time_t                m_ftCreation;
      __time_t                m_ftAccess;
      __time_t                m_ftModified;

      
      
      string                  m_strSourcePath;
      string                  m_strSourceDir;
      string                  m_strCppPath;
      string                  m_strScriptPath;
      string                  m_strBuildBat;
      manual_reset_event      m_evCreationEnabled;
      DWORD                   m_dwLastBuildTime;
      bool                    m_bShouldBuild;
      bool                    m_bCalcHasTempError;
      bool                    m_bHasTempError;

      



      ds_script(::ca::application * papp);
      ~ds_script(void);



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




      ::ca::application * get_app() const;

      script_instance * create_instance();


   };

   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script(::ca::application * papp) : 
         ca(papp),
         script(papp)
      {
      };


      virtual script_instance * create_instance()
      {
         return new T(this);
      }

   };


} // namespace dynamic_source


