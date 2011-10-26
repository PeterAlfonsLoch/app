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
      script(::ca::application * papp);
      ~script(void);

      http::memory_file m_memfileError;
      string m_strName;
      string m_strSourcePath;
      string m_strCppPath;
      string m_strScriptPath;
      string m_strBuildBat;
      HMODULE m_hmodule;
      FILETIME m_ftCreation;
      FILETIME m_ftAccess;
      FILETIME m_ftModified;
      mutex m_mutex;
      manual_reset_event m_evCreationEnabled;

      comparable_array < script_instance * > m_scriptinstanceptra;


      NET_NODE_CREATE_INSTANCE_PROC m_lpfnCreateInstance;

      virtual void run(script_instance * pinstance);

      virtual void on_start_build();

      bool DoesMatchVersion();
      bool ShouldBuild();
      bool HasCompileOrLinkError();
      bool HasTempError(bool bLock = true);
      bool CalcHasTempError(bool bLock = true);
      bool HasTimedOutLastBuild();
      void Load(bool bLock);
      void Unload(bool bLock);


      script_manager * m_pmanager;
      DWORD m_dwLastBuildTime;
      bool m_bShouldBuild;
      bool m_bCalcHasTempError;
      bool m_bHasTempError;


      ::ca::application * get_app() const;

      script_instance * create_instance();


   };


} // namespace dynamic_source


