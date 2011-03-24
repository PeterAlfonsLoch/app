#pragma once

class netnodeScript;
class netnodeScriptInstance;

typedef   netnodeScriptInstance * (*NET_NODE_CREATE_INSTANCE_PROC)(netnodeScript * pscript);



class CLASS_DECL_CA2_CUBE netnodeScript :
   virtual public ::radix::object
{
public:
   netnodeScript(::ca::application * papp);
   ~netnodeScript(void);

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


   NET_NODE_CREATE_INSTANCE_PROC m_lpfnCreateInstance;

   virtual void run(netnodeScriptInstance * pinstance);

   virtual void on_start_build();

   bool DoesMatchVersion();
   bool ShouldBuild();
   bool HasCompileOrLinkError();
   bool HasTempError(bool bLock = true);
   bool CalcHasTempError(bool bLock = true);
   bool HasTimedOutLastBuild();
   void Load(bool bLock);
   void Unload(bool bLock);


   netnodeScriptManager * m_pmanager;
   DWORD m_dwLastBuildTime;
   bool m_bShouldBuild;
   bool m_bCalcHasTempError;
   bool m_bHasTempError;


   ::ca::application * get_app() const;

   netnodeScriptInstance * create_instance();

   
};
